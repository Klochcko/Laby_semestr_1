#include <iostream>
#include <string>

using namespace std;

// Структура для представлення даних про товар
struct Product {
    string name;
    int quantity;
    double unitCost;
    string manufacturer;
    string date;
};

int main() {
    const int MAX_PRODUCTS = 100; // Максимальна кількість товарів в магазині
    Product products[MAX_PRODUCTS];

    int numProducts; // Кількість товарів в магазині
    cout << "Введіть кількість товарів: ";
    cin >> numProducts;

    // Введення даних про товари
    for (int i = 0; i < numProducts; ++i) {
        cout << "Товар " << i + 1 << ":" << endl;
        cout << "Найменування: ";
        cin >> products[i].name;
        cout << "Кількість: ";
        cin >> products[i].quantity;
        cout << "Вартість одиниці: ";
        cin >> products[i].unitCost;
        cout << "Виробник: ";
        cin >> products[i].manufacturer;
        cout << "Дата випуску: ";
        cin >> products[i].date;
    }

    // Знаходження виробника з найнижчою середньою вартістю
    string lowestManufacturer;
    double lowestAverageCost = numeric_limits<double>::max();

    for (int i = 0; i < numProducts; ++i) {
        string currentManufacturer = products[i].manufacturer;
        double totalCost = 0.0;
        int numProductsByManufacturer = 0;

        for (int j = 0; j < numProducts; ++j) {
            if (products[j].manufacturer == currentManufacturer) {
                totalCost += products[j].unitCost;
                numProductsByManufacturer++;
            }
        }

        double averageCost = totalCost / numProductsByManufacturer;
        if (averageCost < lowestAverageCost) {
            lowestAverageCost = averageCost;
            lowestManufacturer = currentManufacturer;
        }
    }

    cout << "Виробник з найнижчою середньою вартістю товару: " << lowestManufacturer << endl;

    // Знаходження загальної суми товару за його найменуванням
    string desiredProduct;
    cout << "Введіть найменування товару для знаходження загальної суми: ";
    cin >> desiredProduct;

    double totalAmount = 0.0;
    for (int i = 0; i < numProducts; ++i) {
        if (products[i].name == desiredProduct) {
            totalAmount += products[i].quantity * products[i].unitCost;
        }
    }

    cout << "Загальна сума товару " << desiredProduct << ": " << totalAmount << endl;

    return 0;
}
