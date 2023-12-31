#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <locale>

using namespace std;

class StringSplitter {
public:
    // Константа для обмеження кількості точок розрізу
    const static int MAX_CUTS = 5;

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
        cin.ignore(); // очистка буфера вводу
        getline(cin, str_);

        cout << "Введіть нові точки розрізу, розділені пробілами (максимум " << MAX_CUTS << "): ";
        int cut;
        int attempts = 0;

        while (cin >> cut && attempts < MAX_CUTS) {
            cuts_.push_back(cut);
            attempts++;
        }

        if (attempts == MAX_CUTS) {
            cout << "Досягнуто максимальну кількість точок розрізу. Вихід з введення.\n";
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
            cin.ignore(); // очистка буфера вводу
            getline(cin, str_);

            cout << "Введіть нові точки розрізу, розділені пробілами (максимум " << MAX_CUTS << "): ";
            int cut;
            int attempts = 0;

            while (cin >> cut && attempts < MAX_CUTS) {
                cuts_.push_back(cut);
                attempts++;
            }

            if (attempts == MAX_CUTS) {
                cout << "Досягнуто максимальну кількість точок розрізу. Вихід з введення.\n";
            }
        }
        else {
            cout << "Невірний номер параметра." << endl;
        }
    }

    // Метод для розв'язання відповідної задачі
    void solveTask() {
        // Перевірка на наявність точок розрізу
        if (cuts_.empty()) {
            cout << "Немає точок розрізу для виконання оптимального розбиття.\n";
            return;
        }

        // Ваш код для розв'язання задачі
        vector<string> substrings;

        for (size_t i = 0; i < cuts_.size(); ++i) {
            int start = (i == 0) ? 0 : cuts_[i - 1];
            int end = cuts_[i];

            // Перевірка на валідність індексів перед доступом до str_
            if (start >= 0 && end <= static_cast<int>(str_.size()) && start <= end) {
                string substring = str_.substr(start, end - start);
                substrings.push_back(substring);
            }
            else {
                cout << "Помилка при розбитті рядка. Перевірте правильність введених точок розрізу.\n";
                return;
            }
        }

        // Виводимо оптимальне розбиття
        cout << "Оптимальне розбиття:\n";
        for (const auto& substring : substrings) {
            cout << "Substring: " << substring << endl;
        }
    }

private:
    // Поля класу
    string str_;
    vector<int> cuts_;
};

class InputData {
public:
    // Максимальна кількість точок розрізу
    const static int MAX_CUTS = 5;

    // Метод для задавання початкових даних
    static void setInitialData(StringSplitter& splitter) {
        string str;
        vector<int> cuts;

        cout << "Введіть рядок: ";
        cin.ignore(); // очистка буфера вводу
        getline(cin, str);

        cout << "Введіть точки розрізу, розділені пробілами (максимум " << MAX_CUTS << "): ";
        int cut;
        int attempts = 0;

        while (cin >> cut && attempts < MAX_CUTS) {
            cuts.push_back(cut);
            attempts++;
        }

        if (attempts == MAX_CUTS) {
            cout << "Досягнуто максимальну кількість точок розрізу. Вихід з введення.\n";
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
