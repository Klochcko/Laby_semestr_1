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
        // Розрахунок віку на основі дати народження
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
        // Розрахунок середньої зарплати співробітників на підприємстві
        int totalSalary = 0;
        for (const auto& employee : employees) {
            totalSalary += employee.salary;
        }
        return employees.empty() ? 0 : totalSalary / employees.size();
    }

    void decreaseSalaryForMatchingConditions(const std::string& targetPosition) {
        // Зменшення зарплати для співробітників з відповідними умовами
        for (int i = 0; i < employees.size(); i++) {
            if (employees[i].education != "высшее" && employees[i].position == targetPosition) {
                std::string allowDecrease;
                std::cout << "Разрешить уменьшение зарплаты для сотрудника " << i + 1 << "? (да/нет): ";
                std::cin >> allowDecrease;

                if (allowDecrease == "да") {
                    employees[i].salary -= employees[i].salary / 10;
                }
            }
        }
    }

    int calculateTotalSalary() const {
        // Розрахунок фонду заробітної платні без вирахувань
        int totalSalary = 0;
        for (const auto& employee : employees) {
            totalSalary += employee.salary;
        }
        return totalSalary;
    }

    int calculateTotalSalaryAfterDecrease() const {
        // Розрахунок фонду заробітної платні після внесених змін
        int totalSalary = 0;
        for (const auto& employee : employees) {
            totalSalary += employee.salary;
        }
        return totalSalary;
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

        if (company.employees[i].education == "среднее") {
            company.employees[i].salary -= company.employees[i].salary / 10;
        }
    }

    int averageSalary = company.calculateAverageSalary();

    // Зменшення зарплати для співробітників з відповідними умовами
    std::string targetPosition;
    std::cout << "Введите должность для проверки уменьшения зарплаты: ";
    std::cin >> targetPosition;
    company.decreaseSalaryForMatchingConditions(targetPosition);

    // Виведення інформації про всіх співробітників
    std::cout << "Информация о сотрудниках:" << std::endl;
    for (const auto& employee : company.employees) {
        std::cout << employee.lastName << " " << employee.firstName << " " << employee.middleName
            << ", Должность: " << employee.position << ", Зарплата: " << employee.salary
            << ", Дата рождения: " << employee.dateOfBirth << ", Дата принятия на работу: "
            << employee.hireDate << ", Образование: " << employee.education << std::endl;
    }

    // Визначення збільшення фонду заробітної платні
    int totalSalaryBefore = company.calculateTotalSalary();
    int totalSalaryAfter = company.calculateTotalSalaryAfterDecrease();
    int salaryDifference = totalSalaryAfter - totalSalaryBefore;
    std::cout << "Збільшення фонду заробітної платні: " << salaryDifference << std::endl;

    // Виведення співробітників з зарплатою на 25% вище від середньої
    std::cout << "Співробітники з зарплатою на 25% вище від середньої:" << std::endl;
    for (const auto& employee : company.employees) {
        if (employee.salary > averageSalary * 1.25) {
            std::cout << employee.lastName << " " << employee.firstName << " " << employee.middleName
                << ", Должность: " << employee.position << ", Зарплата: " << employee.salary << std::endl;
        }
    }

    return 0;
}
