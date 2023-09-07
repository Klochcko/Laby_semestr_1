#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std; // Добавляем директиву using для std

class WeatherEntry {
public:
    string date;
    int temperature;
    string windDirection;
    int windSpeed;
    double atmosphericPressure;
    bool precipitation;

    WeatherEntry(const string& d, int temp, const string& windDir, int windSpd, double pressure, bool precip)
        : date(d), temperature(temp), windDirection(windDir), windSpeed(windSpd), atmosphericPressure(pressure), precipitation(precip) {}
};

class WeatherJournal {
private:
    vector<WeatherEntry> entries;

public:
    void addEntry(const WeatherEntry& entry) {
        entries.push_back(entry);
    }

    map<string, int> countPrecipitationByMonth(int year) {
        map<string, int> precipitationByMonth;

        for (const WeatherEntry& entry : entries) {
            if (stoi(entry.date.substr(0, 4)) == year && entry.precipitation) {
                string month = entry.date.substr(5, 2);
                precipitationByMonth[month]++;
            }
        }

        return precipitationByMonth;
    }
};

int main() {

    locale::global(locale("uk_UA"));

    WeatherJournal journal;

    // Додавання погодних записів до щоденника погоди
    journal.addEntry(WeatherEntry("2023-09-01", 25, "NE", 10, 1013.5, true));
    journal.addEntry(WeatherEntry("2023-09-02", 26, "NW", 12, 1014.0, false));
    journal.addEntry(WeatherEntry("2023-09-03", 24, "SE", 8, 1012.5, true));
    // Додавайте інші записи за потреби

    // Визначення кількості днів з опадами для заданого року та виведення результату
    int year = 2023;
    map<string, int> precipitationByMonth = journal.countPrecipitationByMonth(year);

    cout << "Місяці з опадами за рік " << year << " у порядку зменшення кількості днів:" << endl;
    for (const auto& entry : precipitationByMonth) {
        cout << "Місяць " << entry.first << ": " << entry.second << " днів" << endl;
    }

    return 0;
}
