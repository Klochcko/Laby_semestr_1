#include <iostream>
#include <vector>
#include <locale>

// Функция для обчислення суми цифр числа
int sum_of_digits(int num) {
    int sum_digits = 0;
    while (num > 0) {
        sum_digits += num % 10;
        num /= 10;
    }
    return sum_digits;
}

// Функция для пошуку чисел, сума цифр яких рівна сумі цифр інших чисел в масиві
std::vector<int> find_numbers_with_equal_digit_sums(const std::vector<int>& numbers) {
    std::vector<int> result;
    int size = numbers.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i != j && numbers[i] == sum_of_digits(numbers[j])) {
                result.push_back(numbers[i]);
                break;  // Прериваємо цикл, так як знайшли підходяще число
            }
        }
    }

    return result;
}

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

    return -1; // Повертаємо -1, якщо підходящого числа не знайдено
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

    int number_to_find;
    std::cout << "Введите число для поиска: ";
    std::cin >> number_to_find;

    int found_number = find_number_with_equal_digit_sum(numbers, number_to_find);

    if (found_number != -1) {
        std::cout << "Число " << found_number << " равно сумме цифр другого числа в массиве." << std::endl;
    }
    else {
        std::cout << "Нет числа, которое равно сумме цифр " << number_to_find << " другого числа в массиве." << std::endl;
    }

    return 0;
}
