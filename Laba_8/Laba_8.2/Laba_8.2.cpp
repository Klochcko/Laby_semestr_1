#include <iostream>
#include <fstream>
#include <string>
#include <locale>

int main() {
    std::locale::global(std::locale("ru_RU"));
    std::string file_path;
    std::string word_to_replace;
    std::string replacement_word;

    // Запитуємо в користувача слово для заміни та нове слово
    std::cout << "Введите путь к файлу: ";
    std::getline(std::cin, file_path);

    std::cout << "Введите слово, которое нужно заменить: ";
    std::cin >> word_to_replace;

    std::cout << "Введите слово, на которое нужно заменить: ";
    std::cin >> replacement_word;

    // Відкриваємо вхідний файл для читання
    std::ifstream input_file(file_path);
    if (!input_file) {
        std::cout << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    std::string line;
    std::string file_contents;

    // Зчитуємо весь файл
    while (std::getline(input_file, line)) {
        file_contents += line + "\n";
    }

    // Знаходимо всі входження слова для заміни та замінюємо їх
    size_t pos = 0;
    while ((pos = file_contents.find(word_to_replace, pos)) != std::string::npos) {
        file_contents.replace(pos, word_to_replace.length(), replacement_word);
        pos += replacement_word.length();
    }

    // Закриваємо вхідний файл
    input_file.close();

    // Відкриваємо вихідний файл для запису
    std::ofstream output_file("output.txt");
    if (!output_file) {
        std::cout << "Ошибка создания файла для записи!" << std::endl;
        return 1;
    }

    // Записуємо змінений вміст у вихідний файл
    output_file << file_contents;

    // Закриваємо вихідний файл
    output_file.close();

    std::cout << "Замена выполнена успешно." << std::endl;

    return 0;
}