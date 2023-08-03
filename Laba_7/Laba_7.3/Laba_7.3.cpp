#include <iostream>
#include <ctime>
#include <cstdlib>

void bubbleSort(float arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

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

int main() {
    const int SIZE_SMALL = 10;
    const int SIZE_LARGE = 1000000;
    char arr_small_char[SIZE_SMALL];
    char arr_large_char[SIZE_LARGE];
    float* arr_small_float = new float[SIZE_SMALL];
    float* arr_large_float = new float[SIZE_LARGE];

    srand(time(0));
    for (int i = 0; i < SIZE_SMALL; i++) {
        arr_small_char[i] = rand() % 256;
    }
    for (int i = 0; i < SIZE_LARGE; i++) {
        arr_large_char[i] = rand() % 256;
    }

    for (int i = 0; i < SIZE_SMALL; i++) {
        arr_small_float[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
    for (int i = 0; i < SIZE_LARGE; i++) {
        arr_large_float[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }

    // Сортировка и измерение времени для маленького массива (float) с помощью Bubble Sort
    clock_t startTime, endTime;
    int iterations = 5;

    std::cout << "Bubble Sort for arrays of float..." << std::endl;

    startTime = clock();
    for (int i = 0; i < iterations; i++) {
        bubbleSort(arr_small_float, SIZE_SMALL);
    }
    endTime = clock();
    double timeSmallFloat_bubble = double(endTime - startTime) / CLOCKS_PER_SEC / iterations;
    std::cout << "Time taken for sorting array of size " << SIZE_SMALL << " (float) using Bubble Sort: " << timeSmallFloat_bubble << " seconds" << std::endl;

    // Сортировка и измерение времени для большого массива (float) с помощью Bubble Sort
    startTime = clock();
    for (int i = 0; i < iterations; i++) {
        bubbleSort(arr_large_float, SIZE_LARGE);
    }
    endTime = clock();
    double timeLargeFloat_bubble = double(endTime - startTime) / CLOCKS_PER_SEC / iterations;
    std::cout << "Time taken for sorting array of size " << SIZE_LARGE << " (float) using Bubble Sort: " << timeLargeFloat_bubble << " seconds" << std::endl;

    std::cout << "Shell Sort for arrays of float..." << std::endl;

    // Сортировка и измерение времени для маленького массива (float) с помощью Shell Sort
    startTime = clock();
    for (int i = 0; i < iterations; i++) {
        shellSort(arr_small_float, SIZE_SMALL);
    }
    endTime = clock();
    double timeSmallFloat_shell = double(endTime - startTime) / CLOCKS_PER_SEC / iterations;
    std::cout << "Time taken for sorting array of size " << SIZE_SMALL << " (float) using Shell Sort: " << timeSmallFloat_shell << " seconds" << std::endl;

    // Сортировка и измерение времени для большого массива (float) с помощью Shell Sort
    startTime = clock();
    for (int i = 0; i < iterations; i++) {
        shellSort(arr_large_float, SIZE_LARGE);
    }
    endTime = clock();
    double timeLargeFloat_shell = double(endTime - startTime) / CLOCKS_PER_SEC / iterations;
    std::cout << "Time taken for sorting array of size " << SIZE_LARGE << " (float) using Shell Sort: " << timeLargeFloat_shell << " seconds" << std::endl;

    // Освобождение памяти выделенной для динамических массивов
    delete[] arr_small_float;
    delete[] arr_large_float;

    return 0;
}
