#include <iostream>
#include <vector>
#include <locale>

// Функция для вычисления суммы цифр числа
int sum_of_digits(int num) {
    int sum_digits = 0;
    while (num > 0) {
        sum_digits += num % 10;
        num /= 10;
    }
    return sum_digits;
}

// Функция для поиска чисел, сумма цифр которых равна заданному числу a
int find_number_with_equal_digit_sum(const std::vector<int>& numbers, int a) {
    for (int i = 0; i < numbers.size(); ++i) {
        bool found = false;

        for (int j = 0; j < numbers.size(); ++j) {
            if (i != j && a == sum_of_digits(numbers[j])) {
                found = true;
                break;
            }
        }

        if (found) {
            return a;
        }
    }

    return -1; // Возвращаем -1, если подходящего числа не найдено
}

// Функция для поиска чисел, сумма цифр которых равна сумме цифр других чисел
std::vector<int> find_numbers_with_equal_digit_sums(const std::vector<int>& numbers) {
    std::vector<int> result;
    int size = numbers.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i != j && numbers[i] == sum_of_digits(numbers[j])) {
                result.push_back(numbers[i]);
                break;  // Прерываем цикл, так как нашли подходящее число
            }
        }
    }

    return result;
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

    std::vector<int> filtered_numbers = find_numbers_with_equal_digit_sums(numbers);

    if (!filtered_numbers.empty()) {
        std::cout << "Числа, сумма цифр которых равна сумме цифр других чисел: ";
        for (int i = 0; i < filtered_numbers.size(); ++i) {
            std::cout << filtered_numbers[i];
            if (i != filtered_numbers.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Нет чисел, сумма цифр которых равна сумме цифр других чисел." << std::endl;
    }

    for (int i = 0; i < size; ++i) {
        int number = find_number_with_equal_digit_sum(numbers, numbers[i]);
        if (number != -1) {
            std::cout << "Число " << number << " имеет сумму цифр, равную сумме цифр других чисел в массиве." << std::endl;
        }
    }

    return 0;
}
