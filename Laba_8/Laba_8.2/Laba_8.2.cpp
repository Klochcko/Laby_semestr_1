#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string file_path;
    std::string word_to_replace;
    std::string replacement_word;

    // Запитуємо в користувача слово для заміни та нове слово
    std::cout << "Введіть шлях до файлу: ";
    std::getline(std::cin, file_path);

    std::cout << "Введіть слово, яке потрібно замінити: ";
    std::cin >> word_to_replace;

    std::cout << "Введіть слово, на яке потрібно замінити: ";
    std::cin >> replacement_word;

    // Відкриваємо файл для читання та запису
    std::fstream file(file_path, std::ios::in | std::ios::out);

    if (!file) {
        std::cout << "Помилка відкриття файлу!" << std::endl;
        return 1;
    }

    std::string line;
    size_t pos;

    // Читаємо файл рядок за рядком
    while (std::getline(file, line)) {
        // Знаходимо всі входження слова для заміни та замінюємо їх
        while ((pos = line.find(word_to_replace)) != std::string::npos) {
            line.replace(pos, word_to_replace.length(), replacement_word);
        }
        // Записуємо змінений рядок назад у файл
        file << line << std::endl;
    }

    // Закриваємо файл
    file.close();

    std::cout << "Заміна виконана успішно." << std::endl;

    return 0;
}
