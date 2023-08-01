#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


//some test changes

struct Contact {
    std::string lastName;
    std::string firstName;
    std::string phoneNumber;
    std::string birthDate;
};

// Функція для пошуку номерів телефонів за заданим прізвищем
std::vector<std::string> searchByLastName(const std::vector<Contact>& contacts, const std::string& lastName) {
    std::vector<std::string> foundPhoneNumbers;

    for (const Contact& contact : contacts) {
        if (contact.lastName == lastName) {
            foundPhoneNumbers.push_back(contact.phoneNumber);
        }
    }

    std::sort(foundPhoneNumbers.begin(), foundPhoneNumbers.end());

    return foundPhoneNumbers;
}

// Функція для додавання нового запису до файлу
void addContactToFile(std::ofstream& file, const Contact& newContact) {
    file << newContact.lastName << " "
        << newContact.firstName << " "
        << newContact.phoneNumber << " "
        << newContact.birthDate << "\n";
}

// Функція для зчитування даних з файлу
std::vector<Contact> readContactsFromFile(std::ifstream& file) {
    std::vector<Contact> contacts;
    Contact contact;

    while (file >> contact.lastName >> contact.firstName >> contact.phoneNumber >> contact.birthDate) {
        contacts.push_back(contact);
    }

    return contacts;
}

int main() {
    // Відкриття файлу для зчитування та запису
    std::ifstream inputFile("contacts.txt");
    std::ofstream outputFile("contacts.txt", std::ios::app); // Режим додавання до файлу

    if (!inputFile || !outputFile) {
        std::cout << "Помилка при відкритті файлу.\n";
        return 1;
    }

    // Зчитування контактів з файлу
    std::vector<Contact> contacts = readContactsFromFile(inputFile);

    // Приклад пошуку номерів телефонів за прізвищем "Ivanov"
    std::string searchLastName = "Ivanov";
    std::vector<std::string> foundPhoneNumbers = searchByLastName(contacts, searchLastName);

    // Виведення результатів пошуку
    if (foundPhoneNumbers.empty()) {
        std::cout << "Записів з прізвищем " << searchLastName << " не знайдено.\n";
    }
    else {
        std::cout << "Номери телефонів за прізвищем " << searchLastName << " (відсортовані):\n";
        for (const std::string& phoneNumber : foundPhoneNumbers) {
            std::cout << phoneNumber << "\n";
        }
    }

    // Приклад додавання нового контакту до файлу
    Contact newContact;
    newContact.lastName = "Smith";
    newContact.firstName = "John";
    newContact.phoneNumber = "+1234567890";
    newContact.birthDate = "01/01/1990";

    addContactToFile(outputFile, newContact);

    // Закриття файлів
    inputFile.close();
    outputFile.close();

    return 0;
}
