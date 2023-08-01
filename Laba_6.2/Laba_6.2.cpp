#include <iostream>
#include <string>
#include <vector>

struct Employee {
    std::string lastName;
    std::string firstName;
    std::string middleName;
    std::string position;
    double salary;
    std::string dateOfBirth;
    std::string hireDate;
    std::string education;
};

int main() {
    std::vector<Employee> employees;
    int numEmployees;

    std::cout << "Введіть кількість співробітників: ";
    std::cin >> numEmployees;

    employees.resize(numEmployees);

    // Заповнення даних про співробітників з клавіатури
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
        std::cout << "Освіта: ";
        std::cin >> employees[i].education;
    }

    // Зменшення зарплати працівникам, які не мають вищої освіти та працюють на заданій користувачем посаді, на 10%
    std::string targetPosition;
    std::cout << "Введіть посаду, для якої потрібно знизити зарплату: ";
    std::cin >> targetPosition;

    for (auto& employee : employees) {
        if (employee.education != "вища" && employee.position == targetPosition) {
            employee.salary *= 0.9;
        }
    }

    // Виведення даних про співробітників
    std::cout << "Дані про співробітників:" << std::endl;
    for (const auto& employee : employees) {
        std::cout << employee.lastName << " " << employee.firstName << " " << employee.middleName
            << ", посада: " << employee.position << ", зарплата: " << employee.salary
            << ", освіта: " << employee.education << std::endl;
    }

    return 0;
}
