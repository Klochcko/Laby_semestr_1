#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

const int ORDER = 5;

struct Machine {
    int inventoryNumber;
    string name;
    string type;
    float downtime;
    float workingTime;
};

class BTreeNode {
public:
    Machine machines[ORDER - 1];
    BTreeNode* children[ORDER];
    int numKeys;
    bool isLeaf;

    BTreeNode(bool leaf) {
        numKeys = 0;
        isLeaf = leaf;
        for (int i = 0; i < ORDER; ++i)
            children[i] = nullptr;
    }
};

class BTree {
private:
    BTreeNode* root;

    void insertNonFull(BTreeNode* node, Machine machine) {
        int i = node->numKeys - 1;
        if (node->isLeaf) {
            while (i >= 0 && machine.inventoryNumber < node->machines[i].inventoryNumber) {
                node->machines[i + 1] = node->machines[i];
                --i;
            }
            node->machines[i + 1] = machine;
            ++node->numKeys;
        }
        else {
            while (i >= 0 && machine.inventoryNumber < node->machines[i].inventoryNumber)
                --i;
            if (node->children[i + 1]->numKeys == ORDER - 1) {
                splitChild(node, i + 1, node->children[i + 1]);
                if (machine.inventoryNumber > node->machines[i + 1].inventoryNumber)
                    ++i;
            }
            insertNonFull(node->children[i + 1], machine);
        }
    }

    void splitChild(BTreeNode* parentNode, int index, BTreeNode* childNode) {
        BTreeNode* newNode = new BTreeNode(childNode->isLeaf);
        newNode->numKeys = ORDER / 2 - 1;

        for (int i = 0; i < ORDER / 2 - 1; ++i)
            newNode->machines[i] = childNode->machines[i + ORDER / 2];
        if (!childNode->isLeaf) {
            for (int i = 0; i < ORDER / 2; ++i)
                newNode->children[i] = childNode->children[i + ORDER / 2];
        }
        childNode->numKeys = ORDER / 2 - 1;

        for (int i = parentNode->numKeys; i >= index + 1; --i)
            parentNode->children[i + 1] = parentNode->children[i];
        parentNode->children[index + 1] = newNode;

        for (int i = parentNode->numKeys - 1; i >= index; --i)
            parentNode->machines[i + 1] = parentNode->machines[i];

        parentNode->machines[index] = childNode->machines[ORDER / 2 - 1];
        ++parentNode->numKeys;
    }

    void traverse(BTreeNode* node) {
        int i;
        for (i = 0; i < node->numKeys; ++i) {
            if (!node->isLeaf)
                traverse(node->children[i]);
            cout << "Inventory Number: " << node->machines[i].inventoryNumber << endl;
            cout << "Name: " << node->machines[i].name << endl;
            cout << "Type: " << node->machines[i].type << endl;
            cout << "Downtime: " << node->machines[i].downtime << endl;
            cout << "Working Time: " << node->machines[i].workingTime << endl;
            cout << "----------------------" << endl;
        }
        if (!node->isLeaf)
            traverse(node->children[i]);
    }

    Machine* search(BTreeNode* node, int inventoryNumber) {
        int i = 0;
        while (i < node->numKeys && inventoryNumber > node->machines[i].inventoryNumber)
            ++i;
        if (i < node->numKeys && inventoryNumber == node->machines[i].inventoryNumber)
            return &(node->machines[i]);
        if (node->isLeaf)
            return nullptr;
        return search(node->children[i], inventoryNumber);
    }

    void calculateDowntimePercentage(BTreeNode* node, unordered_map<string, float>& typeDowntimeMap, float& totalWorkingTime) {
        for (int i = 0; i < node->numKeys; ++i) {
            totalWorkingTime += node->machines[i].workingTime;
            typeDowntimeMap[node->machines[i].type] += node->machines[i].downtime;
        }
        if (!node->isLeaf) {
            for (int i = 0; i <= node->numKeys; ++i)
                calculateDowntimePercentage(node->children[i], typeDowntimeMap, totalWorkingTime);
        }
    }

public:
    BTree() {
        root = nullptr;
    }

    void insert(Machine machine) {
        if (root == nullptr) {
            root = new BTreeNode(true);
            root->machines[0] = machine;
            root->numKeys = 1;
        }
        else {
            if (root->numKeys == ORDER - 1) {
                BTreeNode* newNode = new BTreeNode(false);
                newNode->children[0] = root;
                splitChild(newNode, 0, root);
                int i = 0;
                if (newNode->machines[0].inventoryNumber < machine.inventoryNumber)
                    ++i;
                insertNonFull(newNode->children[i], machine);
                root = newNode;
            }
            else {
                insertNonFull(root, machine);
            }
        }
    }

    Machine* search(int inventoryNumber) {
        return (root == nullptr) ? nullptr : search(root, inventoryNumber);
    }

    void traverse() {
        if (root != nullptr)
            traverse(root);
    }

    void calculateAndPrintDowntimePercentage() {
        unordered_map<string, float> typeDowntimeMap;
        float totalWorkingTime = 0.0f;
        calculateDowntimePercentage(root, typeDowntimeMap, totalWorkingTime);

        cout << "Downtime percentage for each type:" << endl;
        for (auto& pair : typeDowntimeMap) {
            float percentage = (pair.second / totalWorkingTime) * 100;
            cout << pair.first << ": " << percentage << "%" << endl;
        }
    }
};

int main() {
    BTree tree;

    // Додайте верстати до дерева
    tree.insert({ 1, "Machine1", "Type1", 10.5, 120 });
    tree.insert({ 2, "Machine2", "Type2", 8.2, 150 });
    tree.insert({ 3, "Machine3", "Type1", 5.3, 100 });

    // Пошук інформації за інвентарним номером
    int searchInventoryNumber = 2;
    Machine* searchedMachine = tree.search(searchInventoryNumber);
    if (searchedMachine != nullptr) {
        cout << "Machine found:" << endl;
        cout << "Inventory Number: " << searchedMachine->inventoryNumber << endl;
        cout << "Name: " << searchedMachine->name << endl;
        cout << "Type: " << searchedMachine->type << endl;
        cout << "Downtime: " << searchedMachine->downtime << endl;
        cout << "Working Time: " << searchedMachine->workingTime << endl;
    }
    else {
        cout << "Machine with inventory number " << searchInventoryNumber << " not found." << endl;
    }

    // Визначення відсотку перестою за останній місяць
    tree.calculateAndPrintDowntimePercentage();

    return 0;
}

