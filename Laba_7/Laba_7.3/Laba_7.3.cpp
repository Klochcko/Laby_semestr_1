#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>

// Функція для генерації випадкових елементів у масиві char
void generateRandomData(char arr[], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = 'A' + rand() % 26; // Генеруємо випадкову велику літеру
}

// Функція для генерації випадкових елементів у масиві float
void generateRandomData(float arr[], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // Генеруємо випадкове дійсне число [0, 1)
}

// Алгоритм сортування обміном для масиву char
void bubbleSort(char arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Алгоритм сортування Шелла для масиву float
void shellSort(float arr[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            float temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Функція для запису результатів у файл CSV
void writeResultsToCSV(const std::string& filename, const std::vector<std::vector<std::string>>& results) {
    std::ofstream outFile(filename);

    for (const auto& row : results) {
        for (std::size_t col = 0; col < row.size(); col++) {
            outFile << row[col];
            if (col < row.size() - 1) {
                outFile << ",";
            }
        }
        outFile << std::endl;
    }

    outFile.close();
}

int main() {
    const int dataSizeSmall = 10;
    const int dataSizeLarge = 1000000;

    // Масиви для зберігання тестових даних
    char charArraySmall[dataSizeSmall];
    char charArrayLarge[dataSizeLarge];
    float floatArraySmall[dataSizeSmall];
    float floatArrayLarge[dataSizeLarge];

    // Вектор для зберігання результатів
    std::vector<std::vector<std::string>> results;

    // Заголовок таблиці
    results.push_back(std::vector<std::string>{"Iteration", "Bubble Sort (char) - Small Data Size", "Shell Sort (float) - Large Data Size"});

    // Повторимо дії 5 разів
    for (int iteration = 0; iteration < 5; iteration++) {
        // Генеруємо нові випадкові дані для масивів
        generateRandomData(charArraySmall, dataSizeSmall);
        generateRandomData(charArrayLarge, dataSizeLarge);
        generateRandomData(floatArraySmall, dataSizeSmall);
        generateRandomData(floatArrayLarge, dataSizeLarge);

        // Сортування масивів char та float
        std::clock_t start_time = std::clock();
        bubbleSort(charArraySmall, dataSizeSmall);
        shellSort(floatArrayLarge, dataSizeLarge);
        std::clock_t end_time = std::clock();
        double elapsed_time_bubble = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

        start_time = std::clock();
        shellSort(floatArraySmall, dataSizeSmall);
        bubbleSort(charArrayLarge, dataSizeLarge);
        end_time = std::clock();
        double elapsed_time_shell = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

        // Записуємо результати в таблицю
        results.push_back({ std::to_string(iteration + 1), std::to_string(elapsed_time_bubble), std::to_string(elapsed_time_shell) });
    }

    // Збережемо результати у файл CSV
    writeResultsToCSV("results.csv", results);

    return 0;
}
