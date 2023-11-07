#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <locale>

// Структура для представлення даних про верстат
struct Machine {
    int inventoryNumber;
    std::string name;
    std::string type;
    double downtime; // час перестою в годинах
    double workTime;  // час роботи в годинах за місяць
};

int main() {

    std::locale::global(std::locale("uk_UA"));

    // Створення вектору для зберігання даних про верстати
    std::vector<Machine> machines;

    // Додавання даних про верстати
    machines.push_back({ 1, "Machine A", "Type 1", 10.0, 200.0 });
    machines.push_back({ 2, "Machine B", "Type 2", 5.0, 180.0 });
    machines.push_back({ 3, "Machine C", "Type 1", 15.0, 220.0 });

    // Створення дерева даних, де ключ - інвентарний номер, значення - вказівник на верстат
    std::map<int, Machine*> machineTree;
    for (auto& machine : machines) {
        machineTree[machine.inventoryNumber] = &machine;
    }

    // Пошук інформації за інвентарним номером та обчислення відсотку перестою
    int searchInventoryNumber = 2;  // Змініть на інвентарний номер, який вас цікавить
    if (machineTree.find(searchInventoryNumber) != machineTree.end()) {
        Machine* searchedMachine = machineTree[searchInventoryNumber];
        double downtimePercentage = (searchedMachine->downtime / searchedMachine->workTime) * 100.0;
        std::cout << "Інвентарний номер: " << searchedMachine->inventoryNumber << std::endl;
        std::cout << "Відсоток перестою: " << downtimePercentage << "%" << std::endl;
    }
    else {
        std::cout << "Верстат з інвентарним номером " << searchInventoryNumber << " не знайдено." << std::endl;
    }

    // Визначення типу верстатів, який використовується найбільше
    std::map<std::string, int> typeCount;
    std::string mostUsedType;

    for (auto& machine : machines) {
        typeCount[machine.type]++;
        if (typeCount[machine.type] > typeCount[mostUsedType]) {
            mostUsedType = machine.type;
        }
    }

    std::cout << "Тип верстатів, який використовується найбільше: " << mostUsedType << std::endl;

    return 0;
}
