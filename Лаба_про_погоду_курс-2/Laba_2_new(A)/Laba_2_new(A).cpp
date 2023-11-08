#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

class BTree {
    struct BNode {
        std::vector<int> keys;  // Ключі, які зберігаються в вузлі
        std::vector<BNode*> children;  // Вказівники на дочірні вузли
        bool isLeaf;  // Чи є вузол листком
    };

    BNode* root;  // Корінь дерева
    int t;  // Мінімальна кількість ключів у вузлі (degree)

public:
    struct Machine {
        int inventoryNumber;
        std::string name;
        std::string type;
        double downtime; // час перестою в годинах
        double workTime;  // час роботи в годинах за місяць
    };

    BTree(int degree) : root(nullptr), t(degree) {
        // Ініціалізація конструктора B-дерева
        root = new BNode();
        root->isLeaf = true;
    }

    void Insert(int key, Machine* machine) {
        if (root->keys.size() == (2 * t - 1)) {
            BNode* newRoot = new BNode();
            newRoot->children.push_back(root);
            SplitChild(newRoot, 0, root);
            root = newRoot;
        }

        InsertNonFull(root, key, machine);
    }

    bool Search(int key) {
        return SearchKey(root, key);
    }

    void Remove(int key) {
        if (Search(key)) {
            RemoveKey(root, key);
        }
        else {
            std::cout << "Key " << key << " not found in the B-tree." << std::endl;
        }
    }

private:
    bool SearchKey(BNode* node, int key) {
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i]) {
            i++;
        }
        if (i < node->keys.size() && key == node->keys[i]) {
            return true;
        }
        else if (node->isLeaf) {
            return false;
        }
        else {
            return SearchKey(node->children[i], key);
        }
    }

    void RemoveKey(BNode* node, int key) {
        if (node == nullptr) {
            return;
        }

        int index = 0;
        while (index < node->keys.size() && key > node->keys[index]) {
            index++;
        }

        if (index < node->keys.size() && key == node->keys[index]) {
            RemoveKeyFromNode(node, key, index);
        }
        else {
            RemoveKeyFromChild(node, key, index);
        }
    }

    void RemoveKeyFromNode(BNode* node, int key, int index) {
        node->keys.erase(node->keys.begin() + index);
    }

    void RemoveKeyFromChild(BNode* node, int key, int index) {
        if (index < node->children.size()) {
            RemoveKey(node->children[index], key);
        }
    }

    void InsertNonFull(BNode* node, int key, Machine* machine) {
        int index = node->keys.size() - 1;
        if (node->isLeaf) {
            node->keys.push_back(key);
            node->children.push_back(nullptr);
            while (index >= 0 && key < node->keys[index]) {
                node->keys[index + 1] = node->keys[index];
                index--;
            }
            node->keys[index + 1] = key;
        }
        else {
            while (index >= 0 && key < node->keys[index]) {
                index--;
            }
            index++;
            if (node->children[index]->keys.size() == (2 * t - 1)) {
                SplitChild(node, index, node->children[index]);
                if (key > node->keys[index]) {
                    index++;
                }
            }
            InsertNonFull(node->children[index], key, machine);
        }
    }

    void SplitChild(BNode* parentNode, int childIndex, BNode* childNode) {
        BNode* newNode = new BNode();
        BNode* rightNode = childNode;
        parentNode->keys.insert(parentNode->keys.begin() + childIndex, rightNode->keys[t - 1]);
        parentNode->children.insert(parentNode->children.begin() + childIndex + 1, newNode);
        newNode->isLeaf = rightNode->isLeaf;
        for (int i = 0; i < (t - 1); i++) {
            newNode->keys.push_back(rightNode->keys[i + t]);
        }
        rightNode->keys.resize(t - 1);
        if (!rightNode->isLeaf) {
            for (int i = 0; i < t; i++) {
                newNode->children.push_back(rightNode->children[i + t]);
            }
            rightNode->children.resize(t);
        }
    }
};

int main() {
    // Створення вектору для зберігання даних про верстати
    std::vector<BTree::Machine> machines;

    // Додавання даних про верстати
    machines.push_back({ 1, "Machine A", "Type 1", 10.0, 200.0 });
    machines.push_back({ 2, "Machine B", "Type 2", 5.0, 180.0 });
    machines.push_back({ 3, "Machine C", "Type 1", 15.0, 220.0 });

    // Визначення типу верстатів, який використовується найбільше
    std::map<std::string, int> typeCount;
    std::string mostUsedType;

    for (auto& machine : machines) {
        typeCount[machine.type]++;
        if (typeCount[machine.type] > typeCount[mostUsedType]) {
            mostUsedType = machine.type;
        }
    }

    std::cout << "The type of machines that is used the most: " << mostUsedType << std::endl;

    return 0;
}
