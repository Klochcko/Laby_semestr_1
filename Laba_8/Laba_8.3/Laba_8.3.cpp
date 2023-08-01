#include <cstdio>

int main() {
    const char* inputFileName = "input.bin";
    const char* outputFileName = "output.hex";

    // Відкриваємо вхідний файл у бінарному режимі для читання
    FILE* inputFile = fopen(inputFileName, "rb");
    if (!inputFile) {
        perror("Помилка відкриття вхідного файлу");
        return 1;
    }

    // Відкриваємо вихідний файл у текстовому режимі для запису
    FILE* outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        perror("Помилка відкриття вихідного файлу");
        fclose(inputFile);
        return 1;
    }

    // Зчитуємо байти з вхідного файлу і записуємо їх у вихідний файл у шістнадцятковому форматі
    int byte;
    while ((byte = fgetc(inputFile)) != EOF) {
        fprintf(outputFile, "%02X ", byte); // %02X - два символи, шістнадцяткове представлення байту
    }

    // Закриваємо файли
    fclose(inputFile);
    fclose(outputFile);

    printf("Шістнадцятковий дамп збережено у файлі '%s'\n", outputFileName);

    return 0;
}
