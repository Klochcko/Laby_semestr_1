#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <locale>

using namespace std;

// Клас для розв'язання задачі розбиття рядка
class StringSplitter {
public:
    // Конструктор за замовчуванням
    StringSplitter() {}

    // Метод для задання початкових даних
    void setInitialData(const string& str, const vector<int>& cuts) {
        str_ = str;
        cuts_ = cuts;
    }

    // Метод для вводу нових параметрів
    void inputNewParameters() {
        cout << "Введіть новий рядок: ";
        getline(cin, str_);

        cout << "Введіть нові точки розрізу, розділені пробілами: ";
        int cut;
        cuts_.clear();
        while (cin >> cut) {
            cuts_.push_back(cut);
        }
    }

    // Метод для коригування та видалення існуючих параметрів
    void modifyExistingParameters() {
        cout << "Введіть номер параметра для коригування або 0 для видалення: ";
        int choice;
        cin >> choice;

        if (choice == 0) {
            // Видалення параметрів
            str_ = "";
            cuts_.clear();
        }
        else if (choice > 0 && choice <= cuts_.size()) {
            // Коригування параметрів
            cout << "Введіть новий рядок: ";
            getline(cin, str_);

            cout << "Введіть нові точки розрізу, розділені пробілами: ";
            int cut;
            cuts_.clear();
            while (cin >> cut) {
                cuts_.push_back(cut);
            }
        }
        else {
            cout << "Невірний номер параметра." << endl;
        }
    }

    // Метод для розв'язання відповідної задачі
    void solveTask() {
        findMinCostAndSplit();
    }

private:
    // Допоміжна функція для знаходження мінімальної вартості та оптимального розбиття
    void findMinCostAndSplit() {
        int n = str_.length();

        // Ініціалізація таблиці для збереження вартостей розбиття та позначення розрізів
        vector<vector<int>> cost(n, vector<int>(n, 0));
        vector<vector<int>> split(n, vector<int>(n, 0));

        // Обчислення вартості для всіх можливих розбиттів
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                cost[i][j] = INT_MAX;

                // Обчислення вартості для кожного розрізу
                for (int k = i; k < j; ++k) {
                    int currentCost = cost[i][k] + cost[k + 1][j] + (cuts_[j] - cuts_[i] + 1);
                    if (currentCost < cost[i][j]) {
                        cost[i][j] = currentCost;
                        split[i][j] = k;
                    }
                }
            }
        }

        // Виведення мінімальної вартості
        cout << "Мінімальна вартість розбиття: " << cost[0][n - 1] << endl;

        // Виведення оптимального розбиття
        cout << "Оптимальне розбиття рядка: ";
        printOptimalSplit(split, 0, n - 1);
        cout << endl;
    }

    // Допоміжна функція для виведення оптимального розбиття
    void printOptimalSplit(const vector<vector<int>>& split, int i, int j) {
        if (i == j) {
            cout << "S" << i + 1 << " ";
        }
        else {
            cout << "(";
            printOptimalSplit(split, i, split[i][j]);
            printOptimalSplit(split, split[i][j] + 1, j);
            cout << ")";
        }
    }

    // Поля класу
    string str_;
    vector<int> cuts_;
};

// Клас для вхідних даних задачі
class InputData {
public:
    // Метод для задавання початкових даних
    static void setInitialData(StringSplitter& splitter) {
        string str;
        vector<int> cuts;

        cout << "Введіть рядок: ";
        getline(cin, str);

        cout << "Введіть точки розрізу, розділені пробілами (наприклад, 2 5): ";
        int cut;
        while (cin >> cut) {
            cuts.push_back(cut);
        }

        splitter.setInitialData(str, cuts);
    }

    // Метод для вводу нових параметрів
    static void inputNewParameters(StringSplitter& splitter) {
        splitter.inputNewParameters();
    }

    // Метод для коригування та видалення існуючих параметрів
    static void modifyExistingParameters(StringSplitter& splitter) {
        splitter.modifyExistingParameters();
    }

    // Метод для розв'язання відповідної задачі
    static void solveTask(StringSplitter& splitter) {
        splitter.solveTask();
    }
};

// Модуль інтерфейсної взаємодії з користувачем
class UserInterface {
public:
    // Метод для виклику необхідних операцій
    static void performOperations(StringSplitter& splitter) {
        int choice;
        do {
            cout << "\nОберіть операцію:\n";
            cout << "1. Задати початкові дані\n";
            cout << "2. Ввести нові параметри\n";
            cout << "3. Коригувати та видалити існуючі\n";
            cout << "4. Розв'язати задачу\n";
            cout << "0. Вийти\n";

            cout << "Ваш вибір: ";
            cin >> choice;
            cin.ignore(); // очистка буфера вводу

            switch (choice) {
            case 1:
                InputData::setInitialData(splitter);
                break;
            case 2:
                InputData::inputNewParameters(splitter);
                break;
            case 3:
                InputData::modifyExistingParameters(splitter);
                break;
            case 4:
                InputData::solveTask(splitter);
                break;
            case 0:
                cout << "Програма завершена.\n";
                break;
            default:
                cout << "Невірний вибір. Спробуйте ще раз.\n";
            }
        } while (choice != 0);
    }
};

int main() {

    locale::global(std::locale("ru_RU"));

    StringSplitter splitter;

    // Запуск інтерфейсу користувача
    UserInterface::performOperations(splitter);

    return 0;
}
