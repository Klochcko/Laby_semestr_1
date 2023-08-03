#include <iostream>
#include <ctime>

void swap(char &a, char &b) {
    char temp = a;
    a = b;
    b = temp;
}

void swap(float &a, float &b) {
    float temp = a;
    a = b;
    b = temp;
}

// ��������� ��������� ���������� ������ (bubble sort) ��� ������ ���� char
void bubbleSort(char arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ��������� ��������� ���������� ������ (bubble sort) ��� ������ ���� float
void bubbleSort(float arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ��������� ��������� ���������� ����� ��� ������ ���� char
void shellSort(char arr[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            char temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// ��������� ��������� ���������� ����� ��� ������ ���� float
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
    float arr_small_float[SIZE_SMALL];
    float arr_large_float[SIZE_LARGE];

    // ���������� ������ ����������� ���������� (��� char)
    srand(time(0));
    for (int i = 0; i < SIZE_SMALL; i++) {
        arr_small_char[i] = rand() % 256; // �������� �������� �� 0 �� 255 (char - 1 ����)
    }
    for (int i = 0; i < SIZE_LARGE; i++) {
        arr_large_char[i] = rand() % 256;
    }

    // ���������� ������ ����������� ���������� (��� float)
    for (int i = 0; i < SIZE_SMALL; i++) {
        arr_small_float[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // �������� �������� �� 0 �� 1
    }
    for (int i = 0; i < SIZE_LARGE; i++) {
        arr_large_float[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }

    // ���������� ������ �� ���������� ���� ��������� (��� char)
    clock_t startTime, endTime;
    int iterations = 5;

    std::cout << "Bubble Sort for arrays of char..." << std::endl;

    // ���������� �� ���������� ���� ��� ������ ������� 10 (char)
    startTime = clock();
    for (int i = 0; i < iterations; i++) {
        bubbleSort(arr_small_char, SIZE_SMALL);
    }
    endTime = clock();
    double timeSmallChar_bubble = double(endTime - startTime) / CLOCKS_PER_SEC / iterations;
    std::cout << "Time taken for sorting array of size " << SIZE_SMALL << " (char) using Bubble Sort: " << timeSmallChar_bubble << " seconds" << std::endl;

    // ���������� �� ���������� ���� ��� ������ ������� 1000000 (char)
    startTime = clock();
    for (int i = 0; i < iterations; i++) {
        bubbleSort(arr_large_char, SIZE_LARGE);
    }
    endTime = clock();
    double timeLargeChar_bubble = double(endTime - startTime) / CLOCKS_PER_SEC / iterations;
    std::cout << "Time taken for sorting array of size " << SIZE_LARGE << " (char) using Bubble Sort: " << timeLargeChar_bubble << " seconds" << std::endl;

    std::cout << "Shell Sort for arrays of char..." << std::endl;

    // ���������� �� ���������� ���� ��� ������ ������� 10 (char)
    startTime = clock();
    for (int i = 0; i < iterations; i++) {
        shellSort(arr_small_char, SIZE_SMALL);
    }
    endTime = clock();
    double timeSmallChar_shell = double(endTime - startTime) / CLOCKS_PER_SEC / iterations;
    std::cout << "Time taken for sorting array of size " << SIZE_SMALL << " (char) using Shell Sort: " << timeSmallChar_shell << " seconds" << std::endl;

    // ���������� �� ���������� ���� ��� ������ ������� 1000000 (char)
    startTime = clock();
    for (int i = 0; i < iterations; i++) {
        shellSort(arr_large_char, SIZE_LARGE);
    }
    endTime = clock();
    double timeLargeChar_shell = double(endTime - startTime) / CLOCKS_PER_SEC / iterations;
    std::cout << "Time taken for sorting array of size " << SIZE_LARGE << " (char) using Shell Sort: " << timeLargeChar_shell << " seconds" << std::endl;

    std::cout << "Bubble Sort for arrays of float..." << std::endl;

    // ���������� �� ���������� ���� ��� ������ ������� 10 (float)
    startTime = clock();
    for (int i = 0; i < iterations; i++) {
        bubbleSort(arr_small_float, SIZE_SMALL);
    }
    endTime = clock();
    double timeSmallFloat_bubble = double(endTime - startTime) / CLOCKS_PER_SEC / iterations;
    std::cout << "Time taken for sorting array of size " << SIZE_SMALL << " (float) using Bubble Sort: " << timeSmallFloat_bubble << " seconds" << std::endl;

    // ���������� �� ���������� ���� ��� ������ ������� 1000000 (float)
    startTime = clock();
    for (int i = 0; i < iterations; i++) {
        bubbleSort(arr_large_float, SIZE_LARGE);
    }
    endTime = clock();
    double timeLargeFloat_bubble = double(endTime - startTime) / CLOCKS_PER_SEC / iterations;
    std::cout << "Time taken for sorting array of size " << SIZE_LARGE << " (float) using Bubble Sort: " << timeLargeFloat_bubble << " seconds" << std::endl;

    std::cout << "Shell Sort for arrays of float..." << std::endl;

    // ���������� �� ���������� ���� ��� ������ ������� 10 (float)
    startTime = clock();
    for (int i = 0; i < iterations; i++) {
        shellSort(arr_small_float, SIZE_SMALL);
    }
    endTime = clock();
    double timeSmallFloat_shell = double(endTime - startTime) / CLOCKS_PER_SEC / iterations;
    std::cout << "Time taken for sorting array of size " << SIZE_SMALL << " (float) using Shell Sort: " << timeSmallFloat_shell << " seconds" << std::endl;

    // ���������� �� ���������� ���� ��� ������ ������� 1000000 (float)
    startTime = clock();
    for (int i = 0; i < iterations; i++) {
        shellSort(arr_large_float, SIZE_LARGE);
    }
    endTime = clock();
    double timeLargeFloat_shell = double(endTime - startTime) / CLOCKS_PER_SEC / iterations;
    std::cout << "Time taken for sorting array of size " << SIZE_LARGE << " (float) using Shell Sort: " << timeLargeFloat_shell << " seconds" << std::endl;

    return 0;
}

