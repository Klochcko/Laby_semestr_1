#include <iostream>
#include <vector>

// Функція для знаходження суми цифр числа без використання рядків
int sum_of_digits(int num) {
    int sum_digits = 0;
    while (num > 0) {
        sum_digits += num % 10;
        num /= 10;
    }
    return sum_digits;
}

// Функція, що знаходить числа, сума цифр яких дорівнює сумі цифр інших чисел з набору,
// а також числа, які дорівнюють сумі своїх цифр
std::vector<int> find_numbers_with_sum_of_digits_equal_to_sum(const std::vector<int>& numbers) {
    std::vector<int> result_same_sum_of_digits;
    std::vector<int> result_sum_of_digits_of_others;

    for (int num : numbers) {
        if (sum_of_digits(num) == num) {
            result_same_sum_of_digits.push_back(num);
        }

        bool found = false;
        for (int other_num : numbers) {
            if (num != other_num && sum_of_digits(other_num) == sum_of_digits(num)) {
                found = true;
                break;
            }
        }
        if (found) {
            result_sum_of_digits_of_others.push_back(num);
        }
    }

    // Об'єднаємо результати в один вектор
    std::vector<int> result = result_same_sum_of_digits;
    result.insert(result.end(), result_sum_of_digits_of_others.begin(), result_sum_of_digits_of_others.end());

    return result;
}

// Функція, що перевіряє, чи дорівнює одне число сумі цифр іншого
bool has_same_sum_of_digits(int num1, int num2) {
    return sum_of_digits(num1) == num2;
}

int main() {
    std::vector<int> numbers = {123, 44, 56, 789, 7890, 102};
    std::vector<int> numbers_with_sum_of_digits_equal_to_sum = find_numbers_with_sum_of_digits_equal_to_sum(numbers);

    std::cout << "Numbers with the sum of digits equal to the sum of digits of other numbers in the set, ";
    std::cout << "and numbers that are equal to the sum of their digits: ";
    for (int num : numbers_with_sum_of_digits_equal_to_sum) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    int num1 = 123;
    int num2 = sum_of_digits(num1); // Сума цифр числа 123
    std::cout << "Does " << num1 << " have the same sum of digits as " << num2 << "? ";
    std::cout << std::boolalpha << has_same_sum_of_digits(num1, num2) << std::endl;

    return 0;
}

