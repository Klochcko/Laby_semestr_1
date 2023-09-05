#include <iostream>
#include <string>
#include <map>
#include <locale>

using namespace std;

struct WeatherEntry {
    int year;
    int month;
    bool hasPrecipitation;
};

int main() {
    // Встановіть українську локалізацію
    locale::global(locale("uk_UA"));

    // Створіть контейнер (map) для збереження кількості днів з опадами за місяцями
    map<int, map<int, int>> precipitationByMonth;

    // Введення даних про погоду
    cout << "Введіть дані про погоду (рік, місяць, наявність опадів, -1 для завершення вводу):" << endl;

    int year, month;
    bool hasPrecipitation;

    while (true) {
        cout << "Рік: ";
        cin >> year;
        if (year == -1) {
            break;
        }

        cout << "Місяць: ";
        cin >> month;

        cout << "Наявність опадів (1 - так, 0 - ні): ";
        cin >> hasPrecipitation;

        // Додайте дані в контейнер
        precipitationByMonth[year][month] += hasPrecipitation;
    }

    // Виведіть результат
    cout << "Місяці з опадами у порядку зменшення кількості днів:" << endl;
    for (const auto& yearEntry : precipitationByMonth) {
        int year = yearEntry.first;
        for (const auto& monthEntry : yearEntry.second) {
            int month = monthEntry.first;
            int daysWithPrecipitation = monthEntry.second;
            cout << "Рік " << year << ", Місяць " << month << ": " << daysWithPrecipitation << " днів" << endl;
        }
    }

    return 0;
}
