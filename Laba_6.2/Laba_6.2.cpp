#include <iostream>
#include <string>
#include <vector>
#include <clocale>

struct Employee {
    std::string lastName;
    std::string firstName;
    std::string middleName;
    std::string position;
    int salary;
    std::string dateOfBirth;
    std::string hireDate;
    std::string education;
};

// Функція для обчислення середньої заробітної плати
int calculateAverageSalary(const std::vector<Employee>& employees) {
    int totalSalary = 0;
    for (const auto& employee : employees) {
        totalSalary += employee.salary;
    }
    return employees.empty() ? 0 : totalSalary / employees.size();
}

// Функція для обчислення віку співробітника за датою народження
int calculateAge(const std::string& dateOfBirth) {
    // Враховуємо, що формат дати дд-мм-рррр
    int birthDay, birthMonth, birthYear;
    sscanf(dateOfBirth.c_str(), "%d-%d-%d", &birthDay, &birthMonth, &birthYear);

    // Визначаємо поточну дату (припустимо, що це 26-07-2023)
    const int currentDay = 26;
    const int currentMonth = 7;
    const int currentYear = 2023;

    // Обчислюємо вік
    int age = currentYear - birthYear;
    if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)) {
        age--; // Ще не відзначив день народження в поточному році
    }
    return age;
}

int main() {
    setlocale(LC_ALL, "uk_UA.UTF-8"); // Додано українські літери

    std::vector<Employee> employees;
    int numEmployees;

    std::cout << "Введіть кількість співробітників: ";
    std::cin >> numEmployees;

    employees.resize(numEmployees);

    for (int i = 0; i < numEmployees; i++) {
        std::cout << "Співробітник " << i + 1 << ":" << std::endl;
        std::cout << "Прізвище: ";
        std::cin >> employees[i].lastName;
        std::cout << "Ім'я: ";
        std::cin >> employees[i].firstName;
        std::cout << "По батькові: ";
        std::cin >> employees[i].middleName;
        std::cout << "Посада: ";
        std::cin >> employees[i].position;
        std::cout << "Заробітна плата: ";
        std::cin >> employees[i].salary;
        std::cout << "Дата народження (формат: дд-мм-рррр): ";
        std::cin >> employees[i].dateOfBirth;
        std::cout << "Дата працевлаштування (формат: дд-мм-рррр): ";
        std::cin >> employees[i].hireDate;
        std::cout << "Освіта (вища, середня): ";
        std::cin >> employees[i].education;

        // Автоматичне зниження зарплати на 10% для працівників з освітою "середня"
        if (employees[i].education == "середня") {
            employees[i].salary -= employees[i].salary / 10;
        }
    }

    // Перераховуємо заробітну плату працівників з освітою "середня" на 10%
    int averageSalary = calculateAverageSalary(employees);
    for (auto& employee : employees) {
        if (employee.education == "середня") {
            employee.salary -= employee.salary / 10;
        }
    }

    // Виведення інформації про співробітників
    std::cout << "Дані про співробітників:" << std::endl;
    for (const auto& employee : employees) {
        std::cout << employee.lastName << " " << employee.firstName << " " << employee.middleName
                  << ", посада: " << employee.position << ", зарплата: " << employee.salary
                  << ", дата народження: " << employee.dateOfBirth << ", дата працевлаштування: "
                  << employee.hireDate << ", освіта: " << employee.education << std::endl;
    }

    // Виведення співробітників з зарплатнею на 25% вище середнього і віком до 25 років
    std::cout << std::endl << "Співробітники з зарплатнею на 25% вище середнього і віком до 25 років:" << std::endl;
    bool foundEmployees = false;
    for (const auto& employee : employees) {
        int age = calculateAge(employee.dateOfBirth);
        if (employee.salary > averageSalary * 1.25 && age <= 25) {
            std::cout << employee.lastName << " " << employee.firstName << " " << employee.middleName
                      << ", зарплата: " << employee.salary << ", вік: " << age << " років" << std::endl;
            foundEmployees = true;
        }
    }
    if (!foundEmployees) {
        std::cout << "Немає співробітників із заданими умовами." << std::endl;
    }

    return 0;
}

