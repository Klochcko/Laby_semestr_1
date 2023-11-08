#include <iostream>
#include <string>

class Machine {
public:
    int inventoryNumber;
    std::string name;
    std::string type;
    double downtime;
    double workTime;

    Machine(int inventoryNumber, const std::string& name, const std::string& type, double downtime, double workTime)
        : inventoryNumber(inventoryNumber), name(name), type(type), downtime(downtime), workTime(workTime) {
    }
};

class BTree {
    struct BNode {
        int* keys;
        BNode** children;
        int keyCount;
        bool isLeaf;
    };

    BNode* root;
    int t;

public:
    BTree(int degree) : root(nullptr), t(degree) {
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
            std::cout << "Key " << key << " not found in the B-tree." << std::endl;
        }
    }

    void DisplayStructure() {
        DisplayStructure(root, "", true);
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

        for (int i = t - 1; i >= 0; i--) {
            newNode->keys[i] = rightNode->keys[i + t];
        }

        if (!rightNode->isLeaf) {
            for (int i = t; i >= 0; i--) {
                newNode->children[i] = rightNode->children[i + t];
            }
        }

        for (int i = parentNode->keyCount; i > childIndex; i--) {
            parentNode->keys[i] = parentNode->keys[i - 1];
        }

        parentNode->keys[childIndex] = rightNode->keys[t - 1];
        parentNode->keyCount++;

        for (int i = parentNode->keyCount; i > childIndex; i--) {
            parentNode->children[i] = parentNode->children[i - 1];
        }

        parentNode->children[childIndex + 1] = newNode;
        parentNode->children[childIndex] = rightNode;

        rightNode->keyCount = t - 1;

        for (int i = childIndex; i < parentNode->keyCount; i++) {
            parentNode->keys[i] = parentNode->keys[i + 1];
        }

        parentNode->keyCount--;
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
                prefix = prefix.substr(0, prefix.length() - 4) + "    ";
            }
            else {
                std::cout << "├── ";
                prefix += "│   ";
            }

            if (!node->isLeaf) {
                for (int i = 0; i < node->keyCount; i++) {
                    std::cout << node->keys[i] << std::endl;
                    DisplayStructure(node->children[i], prefix, false);
                }
                DisplayStructure(node->children[node->keyCount], prefix, true);
            }
            else {
                for (int i = 0; i < node->keyCount; i++) {
                    std::cout << node->keys[i] << std::endl;
                }
            }
        }
    }


};

int main() {
    BTree machineBTree(2);

    Machine machine1(1, "Machine A", "Type 1", 10.0, 200.0);
    Machine machine2(2, "Machine B", "Type 2", 5.0, 180.0);
    Machine machine3(3, "Machine C", "Type 1", 15.0, 220.0);

    machineBTree.Insert(machine1.inventoryNumber, &machine1);
    machineBTree.Insert(machine2.inventoryNumber, &machine2);
    machineBTree.Insert(machine3.inventoryNumber, &machine3);

    int searchKey = 2;
    if (machineBTree.Search(searchKey)) {
        std::cout << "Key " << searchKey << " found in the B-tree." << std::endl;
        machineBTree.Remove(searchKey);
    }
    else {
        std::cout << "Key " << searchKey << " not found in the B-tree." << std::endl;
    }

    machineBTree.DisplayStructure();

    return 0;
}
