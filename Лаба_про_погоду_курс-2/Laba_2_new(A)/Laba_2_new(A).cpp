#include <iostream>
#include <map>
#include <string>
#include <iomanip>

class Machine {
public:
    int inventoryNumber;
    std::string name;
    std::string type;
    double downtime; // час перестою в годинах
    double workTime;  // час роботи в годинах за місяць

    Machine(int inventoryNumber, const std::string& name, const std::string& type, double downtime, double workTime)
        : inventoryNumber(inventoryNumber), name(name), type(type), downtime(downtime), workTime(workTime) {
    }
};

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
            newRoot->children = new BNode * [2 * t];  // Додайте цей рядок
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

    void SearchByInventoryNumber(int key) {
        Machine* machine = SearchByInventoryNumber(root, key);
        if (machine != nullptr) {
            std::cout << "Information about the machine with inventory number " << key << ":" << std::endl;
            std::cout << "Name: " << machine->name << std::endl;
            std::cout << "Type: " << machine->type << std::endl;
            double percentDowntime = (machine->downtime / machine->workTime) * 100;
            std::cout << "The percentage of downtime for the last month: " << std::fixed << std::setprecision(2) << percentDowntime << "%" << std::endl;
        }
        else {
            std::cout << "Machine with inventory number " << key << " not found." << std::endl;
        }
    }

    std::string MostUsedMachineType() {
        std::map<std::string, int> typeCount;
        CountMachineTypes(root, typeCount);
        return FindMostUsedType(typeCount);
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

            for (int i = 0; i < node->keyCount; i++) {
                // Добавляем проверку на нулевой указатель
                if (node->children[i] != nullptr) {
                    Machine* machine = GetMachineDetails(node, i);
                    std::cout << "Key: " << node->keys[i] << ", Name: " << machine->name << ", Type: " << machine->type << std::endl;
                    DisplayStructure(node->children[i], prefix, false);
                }
            }
            // Добавляем проверку на нулевой указатель перед рекурсивным вызовом
            if (node->keyCount > 0 && node->children[node->keyCount] != nullptr) {
                Machine* lastMachine = GetMachineDetails(node, node->keyCount - 1);
                std::cout << "Key: " << node->keys[node->keyCount - 1] << ", Name: " << lastMachine->name << ", Type: " << lastMachine->type << std::endl;
                DisplayStructure(node->children[node->keyCount], prefix, true);
            }
        }
    }

    Machine* SearchByInventoryNumber(BNode* node, int key) {
        int i = 0;
        while (i < node->keyCount && key > node->keys[i]) {
            i++;
        }
        if (i < node->keyCount && key == node->keys[i]) {
            return GetMachineDetails(node, i);
        }
        else if (node->isLeaf) {
            return nullptr;
        }
        else {
            return SearchByInventoryNumber(node->children[i], key);
        }
    }

    Machine* GetMachineDetails(BNode* node, int index) {
        if (node == nullptr || index < 0 || index >= node->keyCount) {
            // Возвращаем nullptr, если у нас нет доступной информации о верстате
            return nullptr;
        }

        if (node->isLeaf) {
            // Если узел - лист, возвращаем информацию о верстате
            if (index < node->keyCount) {
                return GetMachineDetails(node->children[index], 0);
            }
        }
        else {
            // Если узел не является листом, рекурсивно вызываем для дочернего узла
            if (index < node->keyCount) {
                return GetMachineDetails(node->children[index], 0);
            }
        }

        // Повертаємо nullptr як захист від непередбачуваного стану
        return nullptr;
    }

    void CountMachineTypes(BNode* node, std::map<std::string, int>& typeCount) {
        // Реалізація підрахунку кількості використань кожного типу верстата
        for (int i = 0; i < node->keyCount; i++) {
            Machine* machine = GetMachineDetails(node, i);
            std::string type = machine->type;
            typeCount[type]++;
        }
    }

    std::string FindMostUsedType(const std::map<std::string, int>& typeCount) {
        // Реалізація визначення типу верстата, який використовується найбільше
        std::string mostUsedType;
        int maxCount = 0;
        for (const auto& pair : typeCount) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                mostUsedType = pair.first;
            }
        }
        return mostUsedType;
    }

};

int main() {
    // Створення B-дерева з параметром ступеня 2
    BTree machineBTree(2);

    // Додавання даних про верстати
    Machine machine1(1, "Machine A", "Type 1", 10.0, 200.0);
    Machine machine2(2, "Machine B", "Type 2", 5.0, 180.0);
    Machine machine3(3, "Machine C", "Type 1", 15.0, 220.0);

    machineBTree.Insert(machine1.inventoryNumber, &machine1);
    machineBTree.Insert(machine2.inventoryNumber, &machine2);
    machineBTree.Insert(machine3.inventoryNumber, &machine3);

    // Пошук та видалення з використанням B-дерева
    int searchKey = 2;  // Змініть на ключ, який вас цікавить
    if (machineBTree.Search(searchKey)) {
        std::cout << "Key " << searchKey << " found in the B-tree." << std::endl;
        machineBTree.Remove(searchKey);
    }
    else {
        std::cout << "Key " << searchKey << " not found in the B-tree." << std::endl;
    }

    // Відображення структури B-дерева
    machineBTree.DisplayStructure();

    // Пошук інформації про верстат за інвентарним номером
    int searchInventoryNumber = 1;  // Змініть на інвентарний номер, який вас цікавить
    machineBTree.SearchByInventoryNumber(searchInventoryNumber);

    // Визначення типу верстатів, який використовується найбільше


    std::string mostUsedType = machineBTree.MostUsedMachineType();
    std::cout << "The type of machine that is used the most: " << mostUsedType << std::endl;

    return 0;
}
