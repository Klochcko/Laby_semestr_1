#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Для використання std::sort

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

bool compareEmployees(const Employee& a, const Employee& b) {
    if (a.dateOfBirth == b.dateOfBirth) {
        return a.lastName < b.lastName;
    }
    return a.dateOfBirth < b.dateOfBirth;
}

int main() {
    std::vector<Employee> employees;
    int numEmployees;

    std::cout << "Введіть кількість співробітників: ";
    std::cin >> numEmployees;

    employees.resize(numEmployees);

    // Заповнення масиву даними про співробітників з клавіатури
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

    // Виведення співробітників, зарплатня яких вище середнього рівня на 25% і вік не перевищує 25 років
    double totalSalary = 0.0;
    int numValidEmployees = 0;
    for (const auto& employee : employees) {
        totalSalary += employee.salary;
    }
    for (const auto& employee : employees) {
        if (employee.salary > totalSalary / numEmployees * 1.25 && employee.dateOfBirth.substr(6) >= "1998") {
            std::cout << employee.lastName << " " << employee.firstName << ": " << employee.salary << std::endl;
            numValidEmployees++;
        }
    }

    // Повідомлення, якщо таких співробітників немає
    if (numValidEmployees == 0) {
        std::cout << "Немає співробітників, які задовольняють умовам." << std::endl;
    }

    // Зменшення зарплати працівникам, які не мають вищої освіти та працюють на заданій користувачем посаді, на 10%
    std::string targetPosition;
    std::cout << "Введіть посаду, для якої потрібно зменшити зарплату: ";
    std::cin >> targetPosition;

    char decision;
    for (auto& employee : employees) {
        if (employee.education != "вища" && employee.position == targetPosition) {
            std::cout << "Чи зменшити зарплатню для співробітника " << employee.lastName << " " << employee.firstName << "? (y/n): ";
            std::cin >> decision;

            if (decision == 'y' || decision == 'Y') {
                employee.salary *= 0.9;
            }
        }
    }

    // Визначення, яким чином збільшився фонд заробітної платні після змін
    double totalNewSalary = 0.0;
    for (const auto& employee : employees) {
        totalNewSalary += employee.salary;
    }

    std::cout << "Фонд заробітної платні після змін: " << totalNewSalary << std::endl;

    // Визначення, яким чином збільшився би фонд заробітної платні, якщо б зменшення виконувалось для всіх співробітників
    double totalNewSalaryForAll = 0.0;
    for (const auto& employee : employees) {
        totalNewSalaryForAll += employee.salary * 0.9;
    }

    std::cout << "Фонд заробітної платні зі зменшенням для всіх: " << totalNewSalaryForAll << std::endl;

    // Виведення даних про співробітників за датами народження, а у випадку однакових дат - за прізвищем
    std::sort(employees.begin(), employees.end(), compareEmployees);

    std::cout << "Дані про співробітників за датами народження:" << std::endl;
    for (const auto& employee : employees) {
        std::cout << employee.lastName << " " << employee.firstName << ": " << employee.dateOfBirth << std::endl;
    }

    return 0;
}
