#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> uniqueNumbers;
    std::cout << "Введіть послідовність цілих чисел (введіть -1, щоб завершити ввід):" << std::endl;

    int num;
    while (true) {
        std::cin >> num;
        if (num == -1) {
            break; // Виходимо з циклу, якщо користувач ввів -1
        }

        // Перевіряємо, чи число вже зустрічалось раніше, і додаємо його до вектору, якщо це нове число
        if (std::find(uniqueNumbers.begin(), uniqueNumbers.end(), num) == uniqueNumbers.end()) {
            uniqueNumbers.push_back(num);
        }
    }

    // Сортуємо вектор у порядку спадання
    std::sort(uniqueNumbers.begin(), uniqueNumbers.end(), std::greater<int>());

    std::cout << "Унікальні числа у порядку зменшення:" << std::endl;
    for (int num : uniqueNumbers) {
        std::cout << num << " "; // Виводимо унікальні числа у порядку спадання
    }
    std::cout << std::endl;

    return 0;
}
