#include <iostream>
#include <locale>
#include <vector>

int sum_of_digits(int num) {
    int sum_digits = 0;
    while (num > 0) {
        sum_digits += num % 10;
        num /= 10;
    }
    return sum_digits;
}

int main() {
    std::locale::global(std::locale("ru_RU"));

    int size;
    std::cout << "Введите размер массива: ";
    std::cin >> size;

    std::vector<int> numbers(size);

    std::cout << "Введите числа: ";
    for (int i = 0; i < size; ++i) {
        std::cin >> numbers[i];
    }

    std::vector<int> filtered_numbers;

    for (int i = 0; i < size; ++i) {
        int current_sum = sum_of_digits(numbers[i]);
        bool found = false;

        for (int j = 0; j < size; ++j) {
            if (i != j && current_sum == numbers[j]) {
                found = true;
                break;
            }
        }

        if (found) {
            filtered_numbers.push_back(numbers[i]);
        }
    }

    if (!filtered_numbers.empty()) {
        std::cout << "Числа, сумма цифр которых равна другим числам в массиве: ";
        for (int i = 0; i < filtered_numbers.size(); ++i) {
            std::cout << filtered_numbers[i];
            if (i != filtered_numbers.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Нет чисел, сумма цифр которых равна другим числам в массиве." << std::endl;
    }

    return 0;
}
