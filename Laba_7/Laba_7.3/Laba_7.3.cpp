#include <iostream>
#include <algorithm>
#include <ctime>

// ������� ��� ��������� ���������� �������� � ����� char
void generateRandomData(char arr[], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = 'A' + rand() % 26; // �������� ��������� ������ �����
}

// ������� ��� ��������� ���������� �������� � ����� float
void generateRandomData(float arr[], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // �������� ��������� ����� ����� [0, 1)
}

// �������� ���������� ������ ��� ����-����� ������
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

// �������� ���������� ����� ��� ����-����� ������
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

// ������� ��� ���������� ���� ���������� �� ��������� ���������� �� �����
template<typename T>
void measureAndPrintSortingTime(const char* algorithmName, T arr[], int size) {
    std::clock_t start_time = std::clock();
    bubbleSort(arr, size); // ������� ��� �������� �������� ���������� (bubbleSort �� shellSort)
    std::clock_t end_time = std::clock();
    double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Sorting with " << algorithmName << " took: " << elapsed_time << " seconds" << std::endl;
}

int main() {
    const int dataSizeSmall = 10;
    const int dataSizeLarge = 1000000;

    // ������ ��� ��������� �������� �����
    char charArraySmall[dataSizeSmall];
    char charArrayLarge[dataSizeLarge];
    float floatArraySmall[dataSizeSmall];
    float floatArrayLarge[dataSizeLarge];

    // �������� ��� �������� ��� ��� ������
    generateRandomData(charArraySmall, dataSizeSmall);
    generateRandomData(charArrayLarge, dataSizeLarge);
    generateRandomData(floatArraySmall, dataSizeSmall);
    generateRandomData(floatArrayLarge, dataSizeLarge);

    // �������� �� �������� ��� ���������� ��� ������� ��������� �� ���� �����
    std::cout << "Small Data Size" << std::endl;
    measureAndPrintSortingTime("Bubble Sort (char)", charArraySmall, dataSizeSmall);
    measureAndPrintSortingTime("Shell Sort (float)", floatArraySmall, dataSizeSmall);

    std::cout << "\nLarge Data Size" << std::endl;
    measureAndPrintSortingTime("Bubble Sort (char)", charArrayLarge, dataSizeLarge);
    measureAndPrintSortingTime("Shell Sort (float)", floatArrayLarge, dataSizeLarge);

    return 0;
}

