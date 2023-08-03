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
    std::cout << "Enter array size: ";
    std::cin >> size;

    int* numbers = new int[size];

    std::cout << "Enter numbers: ";
    for (int i = 0; i < size; ++i) {
        std::cin >> numbers[i];
    }

    for (int i = 0; i < size; ++i) {
        int num = numbers[i];
        int sum_digits_num = sum_of_digits(num);

        for (int j = 0; j < size; ++j) {
            if (i != j && sum_of_digits(numbers[j]) == sum_digits_num) {
                std::cout << num << " has the same sum of digits as " << numbers[j] << std::endl;
                break;
            }
        }
    }

    // Звільнення пам'яті після використання
    delete[] numbers;

    return 0;
}

