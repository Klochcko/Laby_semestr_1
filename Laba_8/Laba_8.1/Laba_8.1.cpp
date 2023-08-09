#include <iostream>
#include <fstream>
#include <vector>
#include <locale>

void generateBinaryFile(const char* filename, int num_elements) {
    std::ofstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Не вдалося створити файл: " << filename << std::endl;
        return;
    }

    // Генеруємо випадкові байти та записуємо їх у файл
    for (int i = 0; i < num_elements; ++i) {
        char byte = static_cast<char>(std::rand() % 256); // Генеруємо випадковий байт
        file.write(&byte, sizeof(char));
    }

    file.close();
}

int main() {
    std::locale::global(std::locale("ru_RU"));
    // Кількість байтів у кожному файлі
    int num_elements = 10;

    // Генеруємо файли з випадковими байтами
    generateBinaryFile("file1.bin", num_elements);
    generateBinaryFile("file2.bin", num_elements);

    // Відкриваємо вхідні файли
    std::ifstream file1("file1.bin", std::ios::binary);
    std::ifstream file2("file2.bin", std::ios::binary);

    if (!file1 || !file2) {
        std::cerr << "Не вдалося відкрити вхідні файли." << std::endl;
        return 1;
    }

    // Відкриваємо вихідний файл
    std::ofstream file3("file3.bin", std::ios::binary);

    if (!file3) {
        std::cerr << "Не вдалося створити вихідний файл." << std::endl;
        return 1;
    }

    // Зчитування байтів та обчислення суми
    char byte1, byte2;
    while (file1.read(&byte1, sizeof(char)) &&
        file2.read(&byte2, sizeof(char))) {
        char sum = byte1 + byte2;
        file3.write(&sum, sizeof(char));
    }

    // Закриття файлів
    file1.close();
    file2.close();
    file3.close();

    std::cout << "Суми байтів двох файлів були записані у файл 'file3.bin'." << std::endl;

    return 0;
}