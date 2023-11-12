#include <iostream>
#include <vector>
#include <algorithm>
#include <locale>

class Project {
public:
    int start_date;
    int end_date;
    int profit;

    Project(int start, int end, int profit) : start_date(start), end_date(end), profit(profit) {}
};

bool compareByProfitPerDay(const Project& a, const Project& b) {
    return (a.profit / (a.end_date - a.start_date)) > (b.profit / (b.end_date - b.start_date));
}

class TaskInput {
private:
    std::vector<Project>& projects;
    int budget; // Додавання бюджету

public:
    TaskInput(std::vector<Project>& projectsRef, int budget) : projects(projectsRef), budget(budget) {}

    void setInitialData() {
        // Задає початкові дані або завантажує їх з файлу, бази даних, тощо.
        // Можна реалізувати зчитування даних з консолі або іншим способом.
        // Наприклад:
        projects.push_back(Project(1, 5, 50));
        projects.push_back(Project(2, 7, 80));
        projects.push_back(Project(3, 4, 20));
        // Додайте інші проєкти за необхідності
    }

    void addNewProject() {
        // Вводить нові параметри для нового проєкту та додає його до списку проєктів.
        // Реалізуйте введення даних з консолі або іншим способом.
        // Наприклад:
        int start, end, profit;
        std::cout << "Введіть початкову дату проєкту: ";
        std::cin >> start;
        std::cout << "Введіть кінцеву дату проєкту: ";
        std::cin >> end;
        std::cout << "Введіть прибуток проєкту: ";
        std::cin >> profit;

        projects.push_back(Project(start, end, profit));
    }

    // Додайте інші методи для коригування та видалення існуючих проєктів, які вам потрібні.

    std::vector<Project> solveTask() {
        // Розв'язання задачі з використанням жадібного алгоритму
        std::sort(projects.begin(), projects.end(), compareByProfitPerDay);

        std::vector<Project> selectedProjects;
        int currentBudget = 0;

        for (const Project& project : projects) {
            if (currentBudget + project.profit <= budget) {
                selectedProjects.push_back(project);
                currentBudget += project.profit;
            }
        }

        return selectedProjects;
    }
};

class UserInterface {
public:
    static void displayProjects(const std::vector<Project>& projects) {
        std::cout << "Вибрані проєкти:\n";
        for (const Project& project : projects) {
            std::cout << "Початок: " << project.start_date << ", Завершення: " << project.end_date
                << ", Прибуток: " << project.profit << std::endl;
        }
    }
};

int main() {

    std::locale::global(std::locale("uk_UA"));

    std::vector<Project> projects;
    int budget = 100; // Задаємо бюджет

    TaskInput taskInput(projects, budget);
    taskInput.setInitialData();
    taskInput.addNewProject();
    // Додайте виклики інших методів для коригування та видалення існуючих проєктів.

    // Виведення результатів через інтерфейс
    UserInterface::displayProjects(taskInput.solveTask());

    return 0;
}
