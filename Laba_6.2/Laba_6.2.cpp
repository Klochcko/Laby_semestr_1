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

// ������� ��� ���������� �������� �������� �����
int calculateAverageSalary(const std::vector<Employee>& employees) {
    int totalSalary = 0;
    for (const auto& employee : employees) {
        totalSalary += employee.salary;
    }
    return employees.empty() ? 0 : totalSalary / employees.size();
}

// ������� ��� ���������� ��� ����������� �� ����� ����������
int calculateAge(const std::string& dateOfBirth) {
    // ���������, �� ������ ���� ��-��-����
    int birthDay, birthMonth, birthYear;
    sscanf(dateOfBirth.c_str(), "%d-%d-%d", &birthDay, &birthMonth, &birthYear);

    // ��������� ������� ���� (����������, �� �� 26-07-2023)
    const int currentDay = 26;
    const int currentMonth = 7;
    const int currentYear = 2023;

    // ���������� ��
    int age = currentYear - birthYear;
    if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)) {
        age--; // �� �� �������� ���� ���������� � ��������� ����
    }
    return age;
}

int main() {
    setlocale(LC_ALL, "uk_UA.UTF-8"); // ������ �������� �����

    std::vector<Employee> employees;
    int numEmployees;

    std::cout << "������ ������� �����������: ";
    std::cin >> numEmployees;

    employees.resize(numEmployees);

    for (int i = 0; i < numEmployees; i++) {
        std::cout << "���������� " << i + 1 << ":" << std::endl;
        std::cout << "�������: ";
        std::cin >> employees[i].lastName;
        std::cout << "��'�: ";
        std::cin >> employees[i].firstName;
        std::cout << "�� �������: ";
        std::cin >> employees[i].middleName;
        std::cout << "������: ";
        std::cin >> employees[i].position;
        std::cout << "�������� �����: ";
        std::cin >> employees[i].salary;
        std::cout << "���� ���������� (������: ��-��-����): ";
        std::cin >> employees[i].dateOfBirth;
        std::cout << "���� ���������������� (������: ��-��-����): ";
        std::cin >> employees[i].hireDate;
        std::cout << "����� (����, �������): ";
        std::cin >> employees[i].education;

        // ����������� �������� �������� �� 10% ��� ���������� � ������ "�������"
        if (employees[i].education == "�������") {
            employees[i].salary -= employees[i].salary / 10;
        }
    }

    // ������������ �������� ����� ���������� � ������ "�������" �� 10%
    int averageSalary = calculateAverageSalary(employees);
    for (auto& employee : employees) {
        if (employee.education == "�������") {
            employee.salary -= employee.salary / 10;
        }
    }

    // ��������� ���������� ��� �����������
    std::cout << "��� ��� �����������:" << std::endl;
    for (const auto& employee : employees) {
        std::cout << employee.lastName << " " << employee.firstName << " " << employee.middleName
                  << ", ������: " << employee.position << ", ��������: " << employee.salary
                  << ", ���� ����������: " << employee.dateOfBirth << ", ���� ����������������: "
                  << employee.hireDate << ", �����: " << employee.education << std::endl;
    }

    // ��������� ����������� � ���������� �� 25% ���� ���������� � ���� �� 25 ����
    std::cout << std::endl << "����������� � ���������� �� 25% ���� ���������� � ���� �� 25 ����:" << std::endl;
    bool foundEmployees = false;
    for (const auto& employee : employees) {
        int age = calculateAge(employee.dateOfBirth);
        if (employee.salary > averageSalary * 1.25 && age <= 25) {
            std::cout << employee.lastName << " " << employee.firstName << " " << employee.middleName
                      << ", ��������: " << employee.salary << ", ��: " << age << " ����" << std::endl;
            foundEmployees = true;
        }
    }
    if (!foundEmployees) {
        std::cout << "���� ����������� �� �������� �������." << std::endl;
    }

    return 0;
}

