#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Product {
    string name;
    int quantity;
    double unitCost;
    string manufacturer;
    string date;
};

int main() {
    const int MAX_PRODUCTS = 100;
    Product products[MAX_PRODUCTS];

    int numProducts;
    cout << "Enter the number of products: ";
    cin >> numProducts;

    for (int i = 0; i < numProducts; ++i) {
        cout << "Product " << i + 1 << ":" << endl;
        cout << "Name: ";
        cin >> products[i].name;
        cout << "Quantity: ";
        cin >> products[i].quantity;
        cout << "Unit Cost: ";
        cin >> products[i].unitCost;
        cout << "Manufacturer: ";
        cin >> products[i].manufacturer;
        cout << "Date: ";
        cin >> products[i].date;
    }

    vector<int> popularProducts; // Масив ідентифікаторів популярних продуктів

    // Користувач вводить ідентифікатори популярних продуктів
    cout << "Enter IDs of popular products (0-based indexing), -1 to end: ";
    int productId;
    while (true) {
        cin >> productId;
        if (productId == -1)
            break;
        popularProducts.push_back(productId);
    }

    // Виведення інформації про популярні продукти
    cout << "Popular products:" << endl;
    for (int id : popularProducts) {
        if (id >= 0 && id < numProducts) {
            cout << "Name: " << products[id].name << ", Quantity: " << products[id].quantity << ", Unit Cost: " << products[id].unitCost << endl;
        }
        else {
            cout << "Invalid product ID: " << id << endl;
        }
    }

    return 0;
}
