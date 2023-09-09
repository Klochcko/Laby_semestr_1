#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include<locale>

struct Contact {
    std::string lastName;
    std::string firstName;
    std::string phoneNumber;
    std::string birthDate;

    // Перевантаження оператора виведення для виводу контакту
    friend std::ostream& operator<<(std::ostream& os, const Contact& contact) {
        os << contact.lastName << " " << contact.firstName << " " << contact.phoneNumber << " " << contact.birthDate;
        return os;
    }
};

// Функція для пошуку номерів телефонів за заданим прізвищем та сортування результатів за абеткою
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

// Функція для додавання нових записів до файлу
void addContactsToFile(std::ofstream& file, const std::vector<Contact>& newContacts) {
    for (const Contact& newContact : newContacts) {
        file << newContact.lastName << " "
            << newContact.firstName << " "
            << newContact.phoneNumber << " "
            << newContact.birthDate << "\n";
    }
}

int main() {

    std::locale::global(std::locale("uk_UA."));

    // Відкриття файлу для зчитування та запису
    std::ifstream inputFile("contacts.txt");
    std::ofstream outputFile("contacts.txt", std::ios::app); // Режим додавання до файлу

    if (!inputFile || !outputFile) {
        std::cout << "Помилка при відкритті файлу.\n";
        return 1;
    }

    // Зчитування контактів з файлу
    std::vector<Contact> contacts;
    Contact contact;

    while (inputFile >> contact.lastName >> contact.firstName >> contact.phoneNumber >> contact.birthDate) {
        contacts.push_back(contact);
    }

    // Пошук та виведення контактів
    std::string searchLastName;
    std::cout << "Введіть фамілію для пошуку: ";
    std::cin >> searchLastName;

    std::vector<Contact> foundContacts = searchAndSortByLastName(contacts, searchLastName);

    // Виведення результатів пошуку
    if (foundContacts.empty()) {
        std::cout << "Записів з фамілією " << searchLastName << " не знайдено.\n";
    }
    else {
        std::cout << "Контакти з фамілією " << searchLastName << " (відсортовані за абеткою):\n";
        for (const Contact& contact : foundContacts) {
            std::cout << contact << "\n";
        }
    }

    // Додавання нових контактів до файлу
    std::cout << "Введіть нові контакти (прізвище ім'я номер телефону дата народження), або натисніть Enter, щоб завершити:\n";
    std::cin.ignore(); // Очищення буфера введення

    std::vector<Contact> newContacts;
    std::string input;

    while (true) {
        std::getline(std::cin, input);

        if (input.empty()) {
            break;
        }

        Contact newContact;
        std::istringstream iss(input);
        iss >> newContact.lastName >> newContact.firstName >> newContact.phoneNumber >> newContact.birthDate;

        newContacts.push_back(newContact);
    }

    addContactsToFile(outputFile, newContacts);

    // Закриття файлів
    inputFile.close();
    outputFile.close();

    return 0;
}
