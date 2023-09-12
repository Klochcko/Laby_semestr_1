#include <iostream>
#include <string>
#include <vector>
#include <locale>

struct Employee {
    std::string lastName;
    std::string firstName;
    std::string middleName;
    std::string position;
    int salary;
    std::string dateOfBirth;
    std::string hireDate;
    std::string education;

    int calculateAge() const {
        int birthDay, birthMonth, birthYear;
        sscanf_s(dateOfBirth.c_str(), "%d-%d-%d", &birthDay, &birthMonth, &birthYear);

        const int currentDay = 26;
        const int currentMonth = 7;
        const int currentYear = 2023;

        int age = currentYear - birthYear;
        if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)) {
            age--;
        }
        return age;
    }
};

struct Company {
    std::vector<Employee> employees;

    int calculateAverageSalary() const {
        int totalSalary = 0;
        for (const auto& employee : employees) {
            totalSalary += employee.salary;
        }
        return employees.empty() ? 0 : totalSalary / employees.size();
    }
};

int main() {
    std::locale::global(std::locale("ru_RU"));

    Company company;
    int numEmployees;

    std::cout << "Введите количество сотрудников: ";
    std::cin >> numEmployees;

    company.employees.resize(numEmployees);

    for (int i = 0; i < numEmployees; i++) {
        std::cout << "Сотрудник " << i + 1 << ":" << std::endl;
        std::cout << "Фамилия: ";
        std::cin >> company.employees[i].lastName;
        std::cout << "Имя: ";
        std::cin >> company.employees[i].firstName;
        std::cout << "Отчество: ";
        std::cin >> company.employees[i].middleName;
        std::cout << "Должность: ";
        std::cin >> company.employees[i].position;
        std::cout << "Зарплата: ";
        std::cin >> company.employees[i].salary;
        std::cout << "Дата рождения (формат: дд-мм-гггг): ";
        std::cin >> company.employees[i].dateOfBirth;
        std::cout << "Дата принятия на работу (формат: дд-мм-гггг): ";
        std::cin >> company.employees[i].hireDate;
        std::cout << "Образование (высшее, среднее): ";
        std::cin >> company.employees[i].education;
    }

    int averageSalary = company.calculateAverageSalary();

    std::cout << "Информация о сотрудниках:" << std::endl;
    for (const auto& employee : company.employees) {
        std::cout << employee.lastName << " " << employee.firstName << " " << employee.middleName
            << ", Должность: " << employee.position << ", Зарплата: " << employee.salary
            << ", Дата рождения: " << employee.dateOfBirth << ", Дата принятия на работу: "
            << employee.hireDate << ", Образование: " << employee.education << std::endl;
    }

    std::cout << std::endl << "Сотрудники с зарплатой на 25% выше средней и возрастом до 25 лет:" << std::endl;
    bool foundEmployees = false;
    for (const auto& employee : company.employees) {
        int age = employee.calculateAge();
        if (employee.salary > averageSalary * 1.25 && age <= 25) {
            std::cout << employee.lastName << " " << employee.firstName << " " << employee.middleName
                << ", Зарплата: " << employee.salary << ", Возраст: " << age << " лет" << std::endl;
            foundEmployees = true;
        }
    }
    if (!foundEmployees) {
        std::cout << "Нет сотрудников, удовлетворяющих указанным условиям." << std::endl;
    }

    return 0;
}
