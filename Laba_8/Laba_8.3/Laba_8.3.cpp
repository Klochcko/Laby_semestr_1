#include <cstdio>
#include <locale>

int main() {
    std::locale::global(std::locale("ru_RU"));

    const char* inputFileName = "input.bin";
    const char* outputFileName = "output.hex";

    FILE* inputFile;
    if (fopen_s(&inputFile, inputFileName, "rb") != 0) {
        perror("Помилка відкриття вхідного файлу");
        return 1;
    }

    FILE* outputFile;
    if (fopen_s(&outputFile, outputFileName, "w") != 0) {
        perror("Помилка відкриття вихідного файлу");
        fclose(inputFile);
        return 1;
    }

    int byte;
    while ((byte = fgetc(inputFile)) != EOF) {
        fprintf(outputFile, "%02X ", byte);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Шістнадцятковий дамп збережено у файлі '%s'\n", outputFileName);

    return 0;
}
