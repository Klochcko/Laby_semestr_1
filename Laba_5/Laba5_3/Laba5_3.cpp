#include <iostream>

template <typename T>
size_t length(const T& arr) {
    return sizeof(arr) / sizeof(arr[0]);
}

int** convertToSymmetricMatrix(int* arr, size_t size) {
    int** symmetricMatrix = new int*[size];
    for (size_t i = 0; i < size; i++) {
        symmetricMatrix[i] = new int[size];
        for (size_t j = 0; j < size; j++) {
            if (i >= j)
                symmetricMatrix[i][j] = arr[i - j];
            else
                symmetricMatrix[i][j] = arr[j - i];
        }
    }
    return symmetricMatrix;
}

void displaySymmetricMatrix(int** symmetricMatrix, size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            std::cout << symmetricMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void reflectSymmetricMatrix(int** symmetricMatrix, size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            symmetricMatrix[j][i] = symmetricMatrix[i][j];
        }
    }
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size / 2; j++) {
            std::swap(symmetricMatrix[i][j], symmetricMatrix[i][size - j - 1]);
        }
    }
}

void deleteSymmetricMatrix(int** symmetricMatrix, size_t size) {
    for (size_t i = 0; i < size; i++) {
        delete[] symmetricMatrix[i];
    }
    delete[] symmetricMatrix;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    const size_t size = length(arr);

    int** symmetricMatrix = convertToSymmetricMatrix(arr, size);

    std::cout << "Original Symmetric Matrix:" << std::endl;
    displaySymmetricMatrix(symmetricMatrix, size);

    reflectSymmetricMatrix(symmetricMatrix, size);

    std::cout << "Reflected Symmetric Matrix:" << std::endl;
    displaySymmetricMatrix(symmetricMatrix, size);

    deleteSymmetricMatrix(symmetricMatrix, size);

    return 0;
}

