#include <iostream>
#include <algorithm>
#include <ctime>

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

// Алгоритм сортування обміном для будь-якого масиву
template<typename T>
void bubbleSort(T arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Алгоритм сортування Шелла для будь-якого масиву
template<typename T>
void shellSort(T arr[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            T temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Функція для вимірювання часу сортування та виведення результату на екран
template<typename T>
void measureAndPrintSortingTime(const char* algorithmName, T arr[], int size) {
    std::clock_t start_time = std::clock();
    bubbleSort(arr, size); // Виберіть тут потрібний алгоритм сортування (bubbleSort чи shellSort)
    std::clock_t end_time = std::clock();
    double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Sorting with " << algorithmName << " took: " << elapsed_time << " seconds" << std::endl;
}

int main() {
    const int dataSizeSmall = 10;
    const int dataSizeLarge = 1000000;

    // Масиви для зберігання тестових даних
    char charArraySmall[dataSizeSmall];
    char charArrayLarge[dataSizeLarge];
    float floatArraySmall[dataSizeSmall];
    float floatArrayLarge[dataSizeLarge];

    // Генеруємо нові випадкові дані для масивів
    generateRandomData(charArraySmall, dataSizeSmall);
    generateRandomData(charArrayLarge, dataSizeLarge);
    generateRandomData(floatArraySmall, dataSizeSmall);
    generateRandomData(floatArrayLarge, dataSizeLarge);

    // Вимірюємо та виводимо час сортування для кожного алгоритму та типу даних
    std::cout << "Small Data Size" << std::endl;
    measureAndPrintSortingTime("Bubble Sort (char)", charArraySmall, dataSizeSmall);
    measureAndPrintSortingTime("Shell Sort (float)", floatArraySmall, dataSizeSmall);

    std::cout << "\nLarge Data Size" << std::endl;
    measureAndPrintSortingTime("Bubble Sort (char)", charArrayLarge, dataSizeLarge);
    measureAndPrintSortingTime("Shell Sort (float)", floatArrayLarge, dataSizeLarge);

    return 0;
}

