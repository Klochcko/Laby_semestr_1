#include <iostream>
#include <string>
#include <vector>
#include <locale>

// Структура, що представляє співробітника 1
struct Employee {
    std::string lastName;
    std::string firstName;
    std::string middleName;
    std::string position;
    int salary;
    std::string dateOfBirth;
    std::string hireDate;
    std::string education;

    // Функція для розрахунку віку співробітника на основі дати народження
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

// Структура, що представляє компанію та її співробітників
struct Company {
    std::vector<Employee> employees;

    // Функція для розрахунку середньої зарплати співробітників на підприємстві 3
    int calculateAverageSalary() const {
        int totalSalary = 0;
        for (const auto& employee : employees) {
            totalSalary += employee.salary;
        }
        return employees.empty() ? 0 : totalSalary / employees.size();
    }

    // Функція для зменшення зарплати для співробітників з відповідними умовами
    void decreaseSalaryForAllMatchingConditions() {
        for (int i = 0; i < employees.size(); i++) {
            if (employees[i].education != "высшее" && employees[i].position == "ваша_посада") {
                std::string allowDecrease;
                std::cout << "Разрешить уменьшение зарплаты для сотрудника " << i + 1 << "? (да/нет): ";
                std::cin >> allowDecrease;

                if (allowDecrease == "да") {
                    employees[i].salary -= employees[i].salary / 10;
                }
            }
        }
    }
};

int main() {
    // Налаштування локалізації для введення/виведення російською мовою
    std::locale::global(std::locale("ru_RU"));

    Company company;
    int numEmployees;

    std::cout << "Введите количество сотрудников: ";
    std::cin >> numEmployees;

    company.employees.resize(numEmployees);
    // 2
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

        // Зменшення зарплати на 10% для співробітників зі середнім освітнім рівнем 4
        if (company.employees[i].education == "среднее") {
            company.employees[i].salary -= company.employees[i].salary / 10;
        }
    }

    int averageSalary = company.calculateAverageSalary();

    // Виклик функції для зменшення зарплати для відповідних співробітників
    company.decreaseSalaryForAllMatchingConditions();

    // Виведення інформації про всіх співробітників
    std::cout << "Информация о сотрудниках:" << std::endl;
    for (const auto& employee : company.employees) {
        std::cout << employee.lastName << " " << employee.firstName << " " << employee.middleName
            << ", Должность: " << employee.position << ", Зарплата: " << employee.salary
            << ", Дата рождения: " << employee.dateOfBirth << ", Дата принятия на работу: "
            << employee.hireDate << ", Образование: " << employee.education << std::endl;
    }

    // Розрахунок різниці між фондами зарплати до та після зменшення 5,6
    int totalSalaryBefore = 0;
    for (const auto& employee : company.employees) {
        totalSalaryBefore += employee.salary;
    }

    int totalSalaryAfter = 0;
    for (const auto& employee : company.employees) {
        totalSalaryAfter += employee.salary;
    }
    int salaryDifference = totalSalaryAfter - totalSalaryBefore;
    std::cout << "Збільшення фонду заробітної платні: " << salaryDifference << std::endl;

    return 0;
}
