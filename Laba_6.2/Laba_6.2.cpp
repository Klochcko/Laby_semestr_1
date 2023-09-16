#include <iostream>
#include <string>
#include <vector>
#include <locale>

// ���������, �� ����������� ����������� 1
struct Employee {
    std::string lastName;
    std::string firstName;
    std::string middleName;
    std::string position;
    int salary;
    std::string dateOfBirth;
    std::string hireDate;
    std::string education;

    // ������� ��� ���������� ��� ����������� �� ����� ���� ����������
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

// ���������, �� ����������� ������� �� �� �����������
struct Company {
    std::vector<Employee> employees;

    // ������� ��� ���������� �������� �������� ����������� �� ��������� 3
    int calculateAverageSalary() const {
        int totalSalary = 0;
        for (const auto& employee : employees) {
            totalSalary += employee.salary;
        }
        return employees.empty() ? 0 : totalSalary / employees.size();
    }

    // ������� ��� ��������� �������� ��� ����������� � ���������� �������
    void decreaseSalaryForAllMatchingConditions() {
        for (int i = 0; i < employees.size(); i++) {
            if (employees[i].education != "������" && employees[i].position == "����_������") {
                std::string allowDecrease;
                std::cout << "��������� ���������� �������� ��� ���������� " << i + 1 << "? (��/���): ";
                std::cin >> allowDecrease;

                if (allowDecrease == "��") {
                    employees[i].salary -= employees[i].salary / 10;
                }
            }
        }
    }
};

int main() {
    // ������������ ���������� ��� ��������/��������� ��������� �����
    std::locale::global(std::locale("ru_RU"));

    Company company;
    int numEmployees;

    std::cout << "������� ���������� �����������: ";
    std::cin >> numEmployees;

    company.employees.resize(numEmployees);
    // 2
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

        // ��������� �������� �� 10% ��� ����������� � ������� ������ ����� 4
        if (company.employees[i].education == "�������") {
            company.employees[i].salary -= company.employees[i].salary / 10;
        }
    }

    int averageSalary = company.calculateAverageSalary();

    // ������ ������� ��� ��������� �������� ��� ��������� �����������
    company.decreaseSalaryForAllMatchingConditions();

    // ��������� ���������� ��� ��� �����������
    std::cout << "���������� � �����������:" << std::endl;
    for (const auto& employee : company.employees) {
        std::cout << employee.lastName << " " << employee.firstName << " " << employee.middleName
            << ", ���������: " << employee.position << ", ��������: " << employee.salary
            << ", ���� ��������: " << employee.dateOfBirth << ", ���� �������� �� ������: "
            << employee.hireDate << ", �����������: " << employee.education << std::endl;
    }

    // ���������� ������ �� ������� �������� �� �� ���� ��������� 5,6
    int totalSalaryBefore = 0;
    for (const auto& employee : company.employees) {
        totalSalaryBefore += employee.salary;
    }

    int totalSalaryAfter = 0;
    for (const auto& employee : company.employees) {
        totalSalaryAfter += employee.salary;
    }
    int salaryDifference = totalSalaryAfter - totalSalaryBefore;
    std::cout << "��������� ����� �������� �����: " << salaryDifference << std::endl;

    return 0;
}
