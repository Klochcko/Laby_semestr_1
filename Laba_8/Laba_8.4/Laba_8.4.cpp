#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <locale>

struct Contact {
    std::string lastName;
    std::string firstName;
    std::string phoneNumber;
    std::string birthDate;

    // Перегрузка оператора вывода для вывода контакта
    friend std::ostream& operator<<(std::ostream& os, const Contact& contact) {
        os << contact.lastName << " " << contact.firstName << " " << contact.phoneNumber << " " << contact.birthDate;
        return os;
    }

    // Перегрузка оператора ввода для ввода контакта
    friend std::istream& operator>>(std::istream& is, Contact& contact) {
        is >> contact.lastName >> contact.firstName >> contact.phoneNumber >> contact.birthDate;
        return is;
    }
};

// Функция для поиска номеров телефонов по фамилии и сортировки результатов по алфавиту
std::vector<Contact> searchAndSortByLastName(const std::vector<Contact>& contacts, const std::string& lastName) {
    std::vector<Contact> foundContacts;

    for (const Contact& contact : contacts) {
        if (contact.lastName == lastName) {
            foundContacts.push_back(contact);
        }
    }

    std::sort(foundContacts.begin(), foundContacts.end(), [](const Contact& a, const Contact& b) {
        return a.lastName < b.lastName;
        });

    return foundContacts;
}

// Функция для добавления новых записей в файл
void addContactsToFile(std::ofstream& file, const std::vector<Contact>& newContacts) {
    for (const Contact& newContact : newContacts) {
        file << newContact << "\n";
    }
}

int main() {

    std::locale::global(std::locale("uk_UA"));

    // Открытие файла для чтения и записи
    std::ifstream inputFile("contacts.txt");
    std::ofstream outputFile("contacts.txt", std::ios::app); // Режим добавления в файл

    if (!inputFile || !outputFile) {
        std::cout << "Ошибка при открытии файла.\n";
        return 1;
    }

    // Чтение контактов из файла
    std::vector<Contact> contacts;
    Contact contact;

    while (inputFile >> contact) {
        contacts.push_back(contact);
    }

    // Добавление новых контактов в файл
    std::cout << "Введите новые контакты (фамилия имя номер_телефона дата_рождения), или нажмите Enter, чтобы завершить:\n";
    std::vector<Contact> newContacts;
    std::string input;

    while (true) {
        std::getline(std::cin, input);

        if (input.empty()) {
            break;
        }

        std::istringstream iss(input);
        Contact newContact;
        iss >> newContact;

        newContacts.push_back(newContact);
    }

    addContactsToFile(outputFile, newContacts);

    // Поиск и вывод контактов
    while (true) {
        std::string searchLastName;
        std::cout << "Введите фамилию для поиска (или нажмите Enter, чтобы завершить): ";
        std::cin >> searchLastName;

        if (searchLastName.empty()) {
            break; // Завершаем цикл, если пользователь не ввел фамилию
        }

        std::vector<Contact> foundContacts = searchAndSortByLastName(contacts, searchLastName);

        // Вывод результатов поиска
        if (foundContacts.empty()) {
            std::cout << "Контактов с фамилией " << searchLastName << " не найдено.\n";
        }
        else {
            std::cout << "Контакты с фамилией " << searchLastName << " (отсортированы по алфавиту):\n";
            for (const Contact& contact : foundContacts) {
                std::cout << contact << "\n";
            }
        }
    }

    // Закрытие файлов
    inputFile.close();
    outputFile.close();

    return 0;
}
