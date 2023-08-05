#include <iostream>

int sum_of_digits(int num) {
    int sum_digits = 0;
    while (num > 0) {
        sum_digits += num % 10;
        num /= 10;
    }
    return sum_digits;
}

bool is_sum_of_digits_equal(int a, int b) {
    return sum_of_digits(a) == b;
}

void filter_numbers(const int* input_numbers, int size, int target_sum, int* filtered_numbers, int& filtered_size) {
    filtered_size = 0;
    for (int i = 0; i < size; ++i) {
        if (is_sum_of_digits_equal(input_numbers[i], target_sum)) {
            filtered_numbers[filtered_size] = input_numbers[i];
            ++filtered_size;
        }
    }
}

int main() {
    int size;
    std::cout << "Enter size of the array: ";
    std::cin >> size;

    int* numbers = new int[size];

    std::cout << "Enter the numbers: ";
    for (int i = 0; i < size; ++i) {
        std::cin >> numbers[i];
    }

    int target_sum;
    std::cout << "Enter a target sum: ";
    std::cin >> target_sum;

    int* filtered_numbers = new int[size]; // Assuming the filtered array won't be larger than the original array
    int filtered_size;

    filter_numbers(numbers, size, target_sum, filtered_numbers, filtered_size);

    if (filtered_size > 0) {
        std::cout << "Numbers with a sum of digits equal to " << target_sum << ": ";
        for (int i = 0; i < filtered_size; ++i) {
            std::cout << filtered_numbers[i];
            if (i != filtered_size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    } else {
        std::cout << "No numbers with a sum of digits equal to " << target_sum << std::endl;
    }

    delete[] numbers;
    delete[] filtered_numbers;

    return 0;
}

