#include <iostream>
#include <fstream>
#include <cstdlib> // Для використання функції rand()
#include <ctime> // Для ініціалізації генератора випадкових чисел
#include <locale>

void generateBinaryFile(const char* filename, int num_elements) {
    std::locale::global(std::locale("ru_RU"));
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

    std::cout << "Бінарні файли були згенеровані: 'file1.bin' та 'file2.bin'." << std::endl;

    return 0;
}
