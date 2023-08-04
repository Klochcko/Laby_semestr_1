#include <iostream>

// Функція для знаходження суми цифр числа без використання рядків
int sum_of_digits(int num) {
    int sum_digits = 0;
    while (num > 0) {
        sum_digits += num % 10;
        num /= 10;
    }
    return sum_digits;
}

int main() {
    int size;
    std::cout << "Enter size arry: ";
    std::cin >> size;

    int* numbers = new int[size];

    std::cout << "Enter the numbers: ";
    for (int i = 0; i < size; ++i) {
        std::cin >> numbers[i];
    }

    bool found = false;
    for (int i = 0; i < size; ++i) {
        int num = numbers[i];

        for (int j = 0; j < size; ++j) {
            if (i != j && sum_of_digits(numbers[j]) == num) {
                std::cout << numbers[j] << " has a sum of digits equal to " << num << std::endl;
                found = true;
                break;
            }
        }
    }

    if (!found) {
        std::cout << "There are no numbers in the array with sums of digits that match other numbers in the array." << std::endl;
    }

    // Звільнення пам'яті після використання
    delete[] numbers;

    return 0;
}

