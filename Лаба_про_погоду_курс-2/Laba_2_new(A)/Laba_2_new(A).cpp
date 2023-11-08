#include <iostream>
#include <map>
#include <string>
#include <algorithm>

class BTree {
    struct BNode {
        int* keys;  // Ключі, які зберігаються в вузлі
        BNode** children;  // Вказівники на дочірні вузли
        int keyCount;  // Кількість ключів в вузлі
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
        root->keys = new int[2 * t - 1];
        root->children = new BNode * [2 * t];
        root->keyCount = 0;
    }

    void Insert(int key, Machine* machine) {
        if (root->keyCount == (2 * t - 1)) {
            BNode* newRoot = new BNode();
            newRoot->children[0] = root;
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
            std::cout << "Ключ " << key << " не знайдено у B-дереві." << std::endl;
        }
    }

private:
    bool SearchKey(BNode* node, int key) {
        int i = 0;
        while (i < node->keyCount && key > node->keys[i]) {
            i++;
        }
        if (i < node->keyCount && key == node->keys[i]) {
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
        while (index < node->keyCount && key > node->keys[index]) {
            index++;
        }

        if (index < node->keyCount && key == node->keys[index]) {
            RemoveKeyFromNode(node, key, index);
        }
        else {
            RemoveKeyFromChild(node, key, index);
        }
    }

    void RemoveKeyFromNode(BNode* node, int key, int index) {
        for (int i = index + 1; i < node->keyCount; i++) {
            node->keys[i - 1] = node->keys[i];
        }
        node->keyCount--;
    }

    void RemoveKeyFromChild(BNode* node, int key, int index) {
        if (index < node->keyCount) {
            RemoveKey(node->children[index], key);
        }
    }

    void InsertNonFull(BNode* node, int key, Machine* machine) {
        int index = node->keyCount - 1;
        if (node->isLeaf) {
            while (index >= 0 && key < node->keys[index]) {
                node->keys[index + 1] = node->keys[index];
                index--;
            }
            node->keys[index + 1] = key;
            node->keyCount++;
        }
        else {
            while (index >= 0 && key < node->keys[index]) {
                index--;
            }
            index++;
            if (node->children[index]->keyCount == (2 * t - 1)) {
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
        parentNode->children[parentNode->keyCount + 1] = nullptr;
        for (int i = parentNode->keyCount; i >= childIndex + 1; i--) {
            parentNode->children[i + 1] = parentNode->children[i];
        }
        parentNode->children[childIndex + 1] = newNode;
        for (int i = parentNode->keyCount - 1; i >= childIndex; i--) {
            parentNode->keys[i + 1] = parentNode->keys[i];
        }
        parentNode->keys[childIndex] = rightNode->keys[t - 1];
        parentNode->keyCount++;

        newNode->isLeaf = rightNode->isLeaf;
        newNode->keyCount = t - 1;
        for (int i = 0; i < t - 1; i++) {
            newNode->keys[i] = rightNode->keys[i + t];
        }
        if (!rightNode->isLeaf) {
            for (int i = 0; i < t; i++) {
                newNode->children[i] = rightNode->children[i + t];
                rightNode->children[i + t] = nullptr;
            }
        }
        rightNode->keyCount = t - 1;
    }

    void DestroyTree(BNode* node) {
        if (node != nullptr) {
            for (int i = 0; i <= node->keyCount; i++) {
                DestroyTree(node->children[i]);
            }
            delete[] node->keys;
            delete[] node->children;
            delete node;
        }
    }

    void DisplayStructure(BNode* node, std::string prefix, bool isTail) {
        if (node != nullptr) {
            std::cout << prefix;
            if (isTail) {
                std::cout << "└── ";
                prefix += "    ";
            }
            else {
                std::cout << "├── ";
                prefix += "│   ";
            }

            for (int i = 0; i < node->keyCount; i++) {
                std::cout << node->keys[i] << std::endl;
                DisplayStructure(node->children[i], prefix, false);
            }
            DisplayStructure(node->children[node->keyCount], prefix, true);
        }
    }
};

int main() {
    // Створення масиву для зберігання даних про верстати
    BTree::Machine machines[3];

    // Додавання даних про верстати
    machines[0] = { 1, "Machine A", "Type 1", 10.0, 200.0 };
    machines[1] = { 2, "Machine B", "Type 2", 5.0, 180.0 };
    machines[2] = { 3, "Machine C", "Type 1", 15.0, 220.0 };

    // Визначення типу верстатів, який використовується найбільше
    std::map<std::string, int> typeCount;
    std::string mostUsedType;

    for (int i = 0; i < 3; i++) {
        typeCount[machines[i].type]++;
        if (typeCount[machines[i].type] > typeCount[mostUsedType]) {
            mostUsedType = machines[i].type;
        }
    }

    std::cout << "Тип верстатів, який використовується найбільше: " << mostUsedType << std::endl;

    return 0;
}
