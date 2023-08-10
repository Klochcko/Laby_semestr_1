#include <iostream>
#include <fstream>
#include <cstdlib> // Для використання функції rand()
#include <ctime>   // Для ініціалізації генератора випадкових чисел

void generateBinaryFile(const char* filename, int num_elements) {
    std::ofstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Не вдалося створити файл: " << filename << std::endl;
        return;
    }

    // Ініціалізація генератора випадкових чисел
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Генеруємо випадкові дійсні числа та записуємо їх у файл
    for (int i = 0; i < num_elements; ++i) {
        double number = static_cast<double>(std::rand()) / RAND_MAX * 100.0; // Генеруємо число у діапазоні [0, 100)
        file.write(reinterpret_cast<const char*>(&number), sizeof(double));
    }

    file.close();
}

int main() {
    // Кількість дійсних чисел у кожному файлі
    int num_elements = 10;

    // Генеруємо файли з випадковими дійсними числами
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

    // Зчитування чисел та обчислення суми
    double number1, number2;
    while (file1.read(reinterpret_cast<char*>(&number1), sizeof(double)) &&
        file2.read(reinterpret_cast<char*>(&number2), sizeof(double))) {
        double sum = number1 + number2;
        file3.write(reinterpret_cast<const char*>(&sum), sizeof(double));
    }

    // Закриття файлів
    file1.close();
    file2.close();
    file3.close();

    std::cout << "Суми елементів двох файлів були записані у файл 'file3.bin'." << std::endl;

    return 0;
}
