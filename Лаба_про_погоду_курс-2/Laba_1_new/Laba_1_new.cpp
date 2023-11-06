#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <ctime>
#include <locale>

class WeatherEntry {
public:
    std::string date;
    double temperature;
    std::string windDirection;
    double windSpeed;
    double pressure;
    bool precipitation;

    WeatherEntry(std::string date, double temperature, std::string windDirection, double windSpeed, double pressure, bool precipitation) {
        this->date = date;
        this->temperature = temperature;
        this->windDirection = windDirection;
        this->windSpeed = windSpeed;
        this->pressure = pressure;
        this->precipitation = precipitation;
    }
};

class Heap {
public:
    // Оголошення класу купи та його методів
    // Додати елемент до купи
    void insert(int value);

    // Сортування купи
    void sort();

    // Вивести купу на екран
    void print();

    void heapify(std::vector<int>& arr, int n, int i);

private:
    std::vector<int> elements;
};

void Heap::insert(int value) {
    elements.push_back(value); // Додаємо новий елемент в купу
    int i = elements.size() - 1;

    // Відновлюємо властивості піраміди вгору
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (elements[i] <= elements[parent]) {
            break; // Властивості піраміди відновлені
        }
        std::swap(elements[i], elements[parent]);
        i = parent;
    }
}

void Heap::print() {
    for (int value : elements) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

void Heap::heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void Heap::sort() {
    int n = elements.size();

    // Будуємо максимальну піраміду
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(elements, n, i);
    }

    // Виділяємо найбільший елемент із піраміди та розміщуємо його в кінці масиву
    for (int i = n - 1; i >= 0; i--) {
        std::swap(elements[0], elements[i]);
        heapify(elements, i, 0);
    }
}

class WeatherJournal {
public:
    void addEntry(const WeatherEntry& entry) {
        entries.push_back(entry);
    }

    // Генерація записів погоди для введеного користувачем року
    void generateWeatherData(int inputYear) {
        // Ініціалізуємо генератор випадкових чисел
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        for (int month = 1; month <= 12; month++) {
            for (int day = 1; day <= 30; day++) {
                // Створення запису погоди для кожного дня
                std::string date = std::to_string(inputYear) + "-" + (month < 10 ? "0" : "") + std::to_string(month) + "-" + (day < 10 ? "0" : "") + std::to_string(day);
                double temperature = 5.0 + (std::rand() % 10); // Генерація температури від 5.0 до 14.9
                std::string windDirection = "Північ";
                double windSpeed = 2.0 + (std::rand() % 10); // Генерація швидкості вітру від 2.0 до 11.9
                double pressure = 1000.0 + (std::rand() % 50); // Генерація атмосферного тиску від 1000.0 до 1049.9
                bool precipitation = (std::rand() % 2) == 1; // Випадково встановлено значення опадів

                addEntry(WeatherEntry(date, temperature, windDirection, windSpeed, pressure, precipitation));
            }
        }
    }

    // Вивести місяці заданого користувачем року в порядку зменшення кількості днів з опадами
    void printRainyMonths(int inputYear) {
        std::map<std::string, int> rainyDays;

        for (const WeatherEntry& entry : entries) {
            int year = std::stoi(entry.date.substr(0, 4));
            if (year == inputYear && entry.precipitation) {
                std::string yearMonth = entry.date.substr(0, 7);
                rainyDays[yearMonth]++;
            }
        }

        if (!rainyDays.empty()) {
            std::vector<std::pair<std::string, int>> monthsWithRain;
            for (const auto& entry : rainyDays) {
                monthsWithRain.push_back(entry);
            }

            std::sort(monthsWithRain.begin(), monthsWithRain.end(), [](const auto& a, const auto& b) {
                return a.second > b.second;
                });

            std::cout << "Місяці року " << inputYear << " в порядку зменшення кількості днів з опадами:" << std::endl;
            for (const auto& entry : monthsWithRain) {
                std::cout << entry.first << " - " << entry.second << " днів з опадами" << std::endl;
            }
        }
        else {
            std::cout << "Немає даних про опади для року " << inputYear << std::endl;
        }
    }

private:
    std::vector<WeatherEntry> entries;
};

int main() {

    std::locale::global(std::locale("uk_UA"));

    WeatherJournal weatherJournal;

    // Введення року від користувача
    int inputYear;
    std::cout << "Введіть рік для генерації даних та підрахунку опадів: ";
    std::cin >> inputYear;

    // Генерація записів погоди для введеного року
    weatherJournal.generateWeatherData(inputYear);

    // Виведення місяців з опадами
    weatherJournal.printRainyMonths(inputYear);

    // Пірамідальне сортування записів погоди
    Heap heap;

    // Додавання елементів в купу для сортування
    heap.insert(5);
    heap.insert(2);
    heap.insert(7);
    heap.insert(1);

    std::cout << "Елементи купи до сортування: ";
    heap.print();

    // Застосовуємо пірамідальне сортування
    heap.sort();

    std::cout << "Елементи купи після сортування: ";
    heap.print();

    return 0;
}
