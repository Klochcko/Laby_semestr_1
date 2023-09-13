#include <iostream>
#include <locale>

// Функція для перетворення одновимірного масиву у двовимірний
void convertToSymmetricMatrix(int* arr, int** matrix, int n) {
    // Заповнення всього двовимірного масиву нулями
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    // Копіювання значень з одновимірного масиву в двовимірний
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            matrix[i][j] = arr[j - i];
        }
    }
}

// Функція для відображення елементів, розташованих вище головної діагоналі
void displayUpperSymmetric(int** matrix, int n) {
    std::cout << "Елементи, розташовані вище головної діагоналі, симетрично відносно головної діагоналі:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j >= i) {
                std::cout << matrix[i][j] << " ";
            }
            else {
                std::cout << matrix[j][i] << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {

    std::locale::global(std::locale("ru_RU"));
    int n; // Розмір одновимірного масиву
    std::cout << "Введіть розмір одновимірного масиву: ";
    std::cin >> n;

    // Оголошення одновимірного масиву
    int* arr = new int[n];

    // Зчитування значень в одновимірний масив
    std::cout << "Введіть елементи одновимірного масиву:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    // Оголошення та ініціалізація двовимірного масиву
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }

    // Виклик функції для перетворення одновимірного масиву у двовимірний
    convertToSymmetricMatrix(arr, matrix, n);

    // Виклик функції для відображення елементів, розташованих вище головної діагоналі
    displayUpperSymmetric(matrix, n);

    // Звільнення виділеної пам'яті
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] arr;

    return 0;
}
