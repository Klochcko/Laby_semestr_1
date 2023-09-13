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

    void decreaseSalaryForNonDegreeEmployees(const std::string& targetPosition, bool allowDecrease) {
        for (auto& employee : employees) {
            if (employee.education != "������" && employee.position == targetPosition) {
                if (allowDecrease) {
                    employee.salary -= employee.salary / 10;
                }
            }
        }
    }
};

int main() {
    std::locale::global(std::locale("ru_RU"));

    Company company;
    int numEmployees;

    std::cout << "������� ���������� �����������: ";
    std::cin >> numEmployees;

    company.employees.resize(numEmployees);

    for (int i = 0; i < numEmployees; i++) {
        std::cout << "��������� " << i + 1 << ":" << std::endl;
        std::cout << "�������: ";
        std::cin >> company.employees[i].lastName;
        std::cout << "���: ";
        std::cin >> company.employees[i].firstName;
        std::cout << "��������: ";
        std::cin >> company.employees[i].middleName;
        std::cout << "���������: ";
        std::cin >> company.employees[i].position;
        std::cout << "��������: ";
        std::cin >> company.employees[i].salary;
        std::cout << "���� �������� (������: ��-��-����): ";
        std::cin >> company.employees[i].dateOfBirth;
        std::cout << "���� �������� �� ������ (������: ��-��-����): ";
        std::cin >> company.employees[i].hireDate;
        std::cout << "����������� (������, �������): ";
        std::cin >> company.employees[i].education;
    }

    int averageSalary = company.calculateAverageSalary();

    std::cout << "���������� � �����������:" << std::endl;
    for (const auto& employee : company.employees) {
        std::cout << employee.lastName << " " << employee.firstName << " " << employee.middleName
            << ", ���������: " << employee.position << ", ��������: " << employee.salary
            << ", ���� ��������: " << employee.dateOfBirth << ", ���� �������� �� ������: "
            << employee.hireDate << ", �����������: " << employee.education << std::endl;
    }

    std::string targetPosition;
    std::cout << "������� ������� ��������� ��� ���������� ��������: ";
    std::cin >> targetPosition;

    bool allowDecrease;
    std::cout << "��������� ���������� ��������? (1 - ��, 0 - ���): ";
    std::cin >> allowDecrease;

    company.decreaseSalaryForNonDegreeEmployees(targetPosition, allowDecrease);

    std::cout << "���������� � ����������� ����� ���������:" << std::endl;
    for (const auto& employee : company.employees) {
        std::cout << employee.lastName << " " << employee.firstName << " " << employee.middleName
            << ", ���������: " << employee.position << ", ��������: " << employee.salary
            << ", ���� ��������: " << employee.dateOfBirth << ", ���� �������� �� ������: "
            << employee.hireDate << ", �����������: " << employee.education << std::endl;
    }

    int newAverageSalary = company.calculateAverageSalary();
    int salaryIncrease = newAverageSalary - averageSalary;
    std::cout << "���� �������� ����� ��������� ��: " << salaryIncrease << std::endl;

    return 0;
}
