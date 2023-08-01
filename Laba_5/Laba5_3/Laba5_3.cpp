#include <iostream>

// Шаблон з варіадичними шаблонами для визначення довжини масивів
template <typename T>
constexpr size_t length(const T& arr) {
    return sizeof(arr) / sizeof(arr[0]);
}

// Функція перетворення одномірного масиву у симетричний двомірний масив
// Вхідні параметри: arr - одномірний масив, size - розмірність масиву
// Повертає: двовимірний масив, симетричний відносно головної діагоналі
int** convertToSymmetricMatrix(int* arr, size_t size) {
    int** symmetricMatrix = new int* [size];
    for (size_t i = 0; i < size; i++) {
        symmetricMatrix[i] = new int[size];
        for (size_t j = 0; j < size; j++) {
            if (i >= j)
                symmetricMatrix[i][j] = arr[i + j];
            else
                symmetricMatrix[i][j] = arr[j + i];
        }
    }
    return symmetricMatrix;
}

// Функція відображення симетричного масиву
// Вхідні параметри: symmetricMatrix - симетричний двомірний масив, size - розмірність масиву
void displaySymmetricMatrix(int** symmetricMatrix, size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            std::cout << symmetricMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Функція відображення симетричного масиву відносно головної діагоналі
// Вхідні параметри: symmetricMatrix - симетричний двомірний масив, size - розмірність масиву
void reflectSymmetricMatrix(int** symmetricMatrix, size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            symmetricMatrix[j][i] = symmetricMatrix[i][j];
        }
    }
}

// Функція звільнення пам'яті, зайнятої двомірним масивом
void deleteSymmetricMatrix(int** symmetricMatrix, size_t size) {
    for (size_t i = 0; i < size; i++) {
        delete[] symmetricMatrix[i];
    }
    delete[] symmetricMatrix;
}

int main() {
    // Приклад вхідного одномірного масиву
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

    // Перетворення одномірного масиву у симетричний двомірний масив
    int** symmetricMatrix = convertToSymmetricMatrix(arr, length(arr));

    // Відображення симетричного двомірного масиву до відображення
    std::cout << "До відображення:" << std::endl;
    displaySymmetricMatrix(symmetricMatrix, length(arr));

    // Відображення симетричного двомірного масиву після відображення
    std::cout << "Після відображення:" << std::endl;
    reflectSymmetricMatrix(symmetricMatrix, length(arr));
    displaySymmetricMatrix(symmetricMatrix, length(arr));

    // Звільнення пам'яті, зайнятої двомірним масивом
    deleteSymmetricMatrix(symmetricMatrix, length(arr));

    return 0;
}
