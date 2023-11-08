#include <iostream>
#include <fstream>
#include <string>

// Клас, що представляє запис у геш-таблиці
class HashTableEntry {
public:
    std::string email;
    std::string company;

    HashTableEntry(const std::string& email, const std::string& company)
        : email(email), company(company) {}
};

// Клас геш-таблиці
class HashTable {
public:
    HashTable(int size);
    ~HashTable();

    void insert(const std::string& email, const std::string& company);
    std::string find(const std::string& email);

private:
    int tableSize;
    HashTableEntry** table;

    int hash(const std::string& email);
    int doubleHash(const std::string& email);
};

HashTable::HashTable(int size) : tableSize(size) {
    table = new HashTableEntry * [tableSize] {};
    for (int i = 0; i < tableSize; ++i) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < tableSize; ++i) {
        if (table[i] != nullptr) {
            delete table[i];
        }
    }
    delete[] table;
}

int HashTable::hash(const std::string& email) {
    // Геш-функція ділення з остачею
    int hashValue = 0;
    for (char c : email) {
        hashValue = (hashValue * 31 + c) % tableSize;
    }
    return hashValue;
}

int HashTable::doubleHash(const std::string& email) {
    // Геш-функція подвійного гешування
    int hash1 = hash(email);
    int hash2 = 1 + (hash(email) % (tableSize - 1));
    return (hash1 + hash2) % tableSize;
}

void HashTable::insert(const std::string& email, const std::string& company) {
    int index = hash(email);
    int step = doubleHash(email);

    while (table[index] != nullptr) {
        // Виконуємо пересування, якщо колізія
        index = (index + step) % tableSize;
    }

    table[index] = new HashTableEntry(email, company);
}

std::string HashTable::find(const std::string& email) {
    int index = hash(email);
    int step = doubleHash(email);

    while (table[index] != nullptr) {
        if (table[index]->email == email) {
            return table[index]->company;
        }
        index = (index + step) % tableSize;
    }

    return "The company was not found";
}

int main() {
    const int tableSize = 100; // Розмір геш-таблиці
    HashTable hashtable(tableSize);

    // Зчитуємо дані з текстового файлу та вставляємо їх до геш-таблиці
    std::ifstream file("data.txt");
    if (file.is_open()) {
        std::string email, company;
        while (file >> email >> company) {
            hashtable.insert(email, company);
        }
        file.close();
    }

    // Запит на знаходження підприємства за електронною адресою
    std::string emailToFind;
    std::cout << "Enter your email address: ";
    std::cin >> emailToFind;

    std::string foundCompany = hashtable.find(emailToFind);
    std::cout << "Company: " << foundCompany << std::endl;

    return 0;
}
