#include <iostream>
#include <vector>
#include <locale>

// ������� ��� ���������� ���� ���� �����
int sum_of_digits(int num) {
    int sum_digits = 0;
    while (num > 0) {
        sum_digits += num % 10;
        num /= 10;
    }
    return sum_digits;
}

// ������� ��� ������ �����, ���� ���� ���� ���� ��� ���� ����� ����� 1,2
std::vector<int> find_numbers_with_equal_digit_sums(const std::vector<int>& numbers) {
    std::vector<int> result;
    int size = numbers.size();

    for (int i = 0; i < size; ++i) {
        bool found = false;

        for (int j = 0; j < size; ++j) {
            if (i != j && sum_of_digits(numbers[i]) == sum_of_digits(numbers[j])) {
                found = true;
                break;
            }
        }

        if (found) {
            result.push_back(numbers[i]);
        }
    }

    return result;
}

int main() {
    std::locale::global(std::locale("ru_RU"));

    int size;
    std::cout << "������� ������ �������: ";
    std::cin >> size;

    std::vector<int> numbers(size);

    std::cout << "������� �����: ";
    for (int i = 0; i < size; ++i) {
        std::cin >> numbers[i];
    }

    std::vector<int> filtered_numbers = find_numbers_with_equal_digit_sums(numbers);

    if (!filtered_numbers.empty()) {
        std::cout << "�����, ����� ���� ������� ����� ������ ������ � �������: ";
        for (int i = 0; i < filtered_numbers.size(); ++i) {
            std::cout << filtered_numbers[i];
            if (i != filtered_numbers.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "��� �����, ����� ���� ������� ����� ������ ������ � �������." << std::endl;
    }

    return 0;
}
