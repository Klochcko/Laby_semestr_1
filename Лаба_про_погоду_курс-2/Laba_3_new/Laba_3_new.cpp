#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>

using namespace std;

// Структура для представления товара
struct Product {
    int id;  // идентификатор товара
    bool isPopular;  // является ли товар популярным

    // Добавьте другие необходимые характеристики товара
};

// Объявление класса UserInterface для исправления ошибки
class UserInterface {
public:
    // Функция для ввода заказов пользователя
    static vector<Product> getUserOrders();

    // Функции для взаимодействия с данными пользователя
    static Product inputProduct();
    static int getProductId();

    // Функция для вывода информации пользователю
    static void displayOrderInfo(const Product& product, bool isAvailable, int totalTime);
};

// Класс, описывающий магазин
class Shop {
public:
    // Конструктор, принимающий список популярных товаров
    Shop(const vector<Product>& popularProducts);

    // Функция для обработки очереди заказов покупателей
    void processOrders(const vector<Product>& customerOrders);

    // Дополнительные функции для работы с данными
    void addProduct(const Product& newProduct);
    void updateProduct(int productId, const Product& updatedProduct);
    void removeProduct(int productId);

private:
    // Очередь для товаров под рукой
    queue<Product> productsUnderHand;

    // Множество для отслеживания популярных товаров под рукой
    unordered_set<int> popularProductsUnderHand;

    // Список популярных товаров
    vector<Product> popularProducts;

    // Время, которое займет обработка всех заказов
    int totalTime;

    // Индекс текущего популярного товара для возможной замены
    size_t currentPopularIndex;
};

// Внешние определения методов UserInterface
vector<Product> UserInterface::getUserOrders() {
    vector<Product> orders;
    int numberOfOrders;

    cout << "Enter the number of orders: ";
    cin >> numberOfOrders;

    for (int i = 0; i < numberOfOrders; ++i) {
        Product order;
        cout << "Enter the product ID for order " << i + 1 << ": ";
        cin >> order.id;

        cout << "Is the product popular? (1 for yes, 0 for no): ";
        cin >> order.isPopular;

        orders.push_back(order);
    }

    return orders;
}

Product UserInterface::inputProduct() {
    // Ввод данных для нового товара
    Product newProduct;
    cout << "Enter the product ID: ";
    cin >> newProduct.id;

    cout << "Is the product popular? (1 for yes, 0 for no): ";
    cin >> newProduct.isPopular;

    return newProduct;
}

int UserInterface::getProductId() {
    // Ввод идентификатора товара для обновления или удаления
    int productId;
    cout << "Enter the product ID: ";
    cin >> productId;

    return productId;
}

void UserInterface::displayOrderInfo(const Product& product, bool isAvailable, int totalTime) {
    cout << "Order for Product " << product.id << " is ";
    if (isAvailable) {
        cout << "available ";
    }
    else {
        cout << "not available ";
    }
    cout << "(Total Time: " << totalTime << " units)" << endl;
}

// Определение методов класса Shop
Shop::Shop(const vector<Product>& popularProducts) : popularProducts(popularProducts), totalTime(0), currentPopularIndex(0) {}

void Shop::processOrders(const vector<Product>& customerOrders) {
    for (const auto& order : customerOrders) {
        // Проверка, есть ли товар под рукой
        bool isAvailable = false;

        if (popularProductsUnderHand.count(order.id) > 0) {
            isAvailable = true;
        }
        else {
            // Если товара нет под рукой, получаем его с полок
            // и решаем, стоит ли заменить какой-то популярный товар
            if (productsUnderHand.size() < popularProducts.size()) {
                // Если еще есть место для нового популярного товара
                productsUnderHand.push(order);
                popularProductsUnderHand.insert(order.id);
            }
            else {
                // Ищем популярный товар, который закончится позже всего
                Product latestPopularProduct = productsUnderHand.front();
                while (!productsUnderHand.empty()) {
                    const auto& product = productsUnderHand.front();
                    if (product.isPopular && product.id != order.id) {
                        if (product.id == latestPopularProduct.id || product.id > latestPopularProduct.id) {
                            latestPopularProduct = product;
                        }
                    }
                    productsUnderHand.pop();
                }

                // Удаляем самый дорогой популярный товар
                popularProductsUnderHand.erase(latestPopularProduct.id);

                // Добавляем новый товар
                productsUnderHand.push(order);
                popularProductsUnderHand.insert(order.id);

                // Замена товара занимает дополнительное время
                totalTime += 1;

                // Замена только одного популярного товара за раз
                currentPopularIndex = (currentPopularIndex + 1) % popularProducts.size();
                popularProductsUnderHand.erase(popularProducts[currentPopularIndex].id);
                productsUnderHand.push(popularProducts[currentPopularIndex]);
                popularProductsUnderHand.insert(popularProducts[currentPopularIndex].id);
            }
        }

        // Обработка заказа (здесь может быть ваша логика обслуживания товара)
        // Здесь мы имитируем, что обработка заказа занимает 1 единицу времени
        totalTime += 1;

        // Вывод информации пользователю
        UserInterface::displayOrderInfo(order, isAvailable, totalTime);
    }
}

void Shop::addProduct(const Product& newProduct) {
    // Добавление нового товара в список популярных товаров
    popularProducts.push_back(newProduct);
}

void Shop::updateProduct(int productId, const Product& updatedProduct) {
    // Обновление существующего товара по идентификатору
    for (auto& product : popularProducts) {
        if (product.id == productId) {
            product = updatedProduct;
            break;
        }
    }
}

void Shop::removeProduct(int productId) {
    // Удаление товара по идентификатору
    auto it = remove_if(popularProducts.begin(), popularProducts.end(),
        [productId](const Product& product) { return product.id == productId; });

    popularProducts.erase(it, popularProducts.end());
}

// Объявление класса HuffmanNode и функции compare для сжатия Хаффмана
struct HuffmanNode {
    char data;
    unsigned frequency;
    HuffmanNode* left, * right;

    HuffmanNode(char data, unsigned frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->frequency > right->frequency;
    }
};

// Класс для сжатия и распаковки Huffman
class HuffmanCoding {
private:
    std::string inputFileName;
    std::string compressedFileName;
    std::string decompressedFileName;
    std::unordered_map<char, std::string> huffmanCodes;

    HuffmanNode* buildHuffmanTree(const std::unordered_map<char, unsigned>& frequencies);
    void generateCodes(HuffmanNode* root, std::string code);

public:
    HuffmanCoding(const std::string& inputFileName, const std::string& compressedFileName, const std::string& decompressedFileName);

    void compress();
    void decompress();
    void displayStatistics();

    ~HuffmanCoding();
};

HuffmanCoding::HuffmanCoding(const std::string& inputFileName, const std::string& compressedFileName, const std::string& decompressedFileName)
    : inputFileName(inputFileName), compressedFileName(compressedFileName), decompressedFileName(decompressedFileName) {}

HuffmanNode* HuffmanCoding::buildHuffmanTree(const std::unordered_map<char, unsigned>& frequencies) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> minHeap;

    for (const auto& entry : frequencies) {
        minHeap.push(new HuffmanNode(entry.first, entry.second));
    }

    while (minHeap.size() != 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();

        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* internalNode = new HuffmanNode('$', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    return minHeap.top();
}

void HuffmanCoding::generateCodes(HuffmanNode* root, std::string code) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '$') {
        huffmanCodes[root->data] = code;
    }

    generateCodes(root->left, code + "0");
    generateCodes(root->right, code + "1");
}

void HuffmanCoding::compress() {
    std::ifstream inputFile(inputFileName, std::ios::binary);
    std::ofstream compressedFile(compressedFileName, std::ios::binary | std::ios::trunc);

    std::unordered_map<char, unsigned> frequencies;
    char ch;

    while (inputFile.get(ch)) {
        frequencies[ch]++;
    }

    inputFile.clear();
    inputFile.seekg(0);

    HuffmanNode* root = buildHuffmanTree(frequencies);
    generateCodes(root, "");

    for (const auto& entry : frequencies) {
        compressedFile.write(reinterpret_cast<const char*>(&entry.first), sizeof(char));
        compressedFile.write(reinterpret_cast<const char*>(&entry.second), sizeof(unsigned));
    }

    char buffer = 0;
    int bitCount = 0;

    while (inputFile.get(ch)) {
        std::string code = huffmanCodes[ch];
        for (char bit : code) {
            buffer <<= 1;
            buffer |= bit - '0';
            bitCount++;

            if (bitCount == 8) {
                compressedFile.put(buffer);
                buffer = 0;
                bitCount = 0;
            }
        }
    }

    if (bitCount > 0) {
        buffer <<= (8 - bitCount);
        compressedFile.put(buffer);
    }

    inputFile.close();
    compressedFile.close();
}

void HuffmanCoding::decompress() {
    std::ifstream compressedFile(compressedFileName, std::ios::binary);
    std::ofstream decompressedFile(decompressedFileName, std::ios::binary | std::ios::trunc);

    std::unordered_map<char, unsigned> frequencies;
    char ch;
    unsigned freq;

    while (compressedFile.read(reinterpret_cast<char*>(&ch), sizeof(char))) {
        compressedFile.read(reinterpret_cast<char*>(&freq), sizeof(unsigned));
        frequencies[ch] = freq;
    }

    HuffmanNode* root = buildHuffmanTree(frequencies);
    generateCodes(root, "");

    HuffmanNode* current = root;
    char bit;

    while (compressedFile.get(ch)) {
        for (int i = 7; i >= 0; i--) {
            bit = (ch >> i) & 1;
            if (bit == 0) {
                current = current->left;
            }
            else {
                current = current->right;
            }

            if (current->left == nullptr && current->right == nullptr) {
                decompressedFile.put(current->data);
                current = root;
            }
        }
    }

    compressedFile.close();
    decompressedFile.close();
}

void HuffmanCoding::displayStatistics() {
    // Вывод статистики
    std::cout << "Huffman Coding Statistics:\n";
    std::cout << "--------------------------\n";
    std::cout << "Input File: " << inputFileName << "\n";
    std::cout << "Compressed File: " << compressedFileName << "\n";
    std::cout << "Decompressed File: " << decompressedFileName << "\n\n";

    // Размер исходного файла
    std::ifstream inputFile(inputFileName, std::ios::binary | std::ios::ate);
    std::streamsize inputSize = inputFile.tellg();
    inputFile.close();
    std::cout << "Original File Size: " << inputSize << " bytes\n";

    // Размер сжатого файла
    std::ifstream compressedFile(compressedFileName, std::ios::binary | std::ios::ate);
    std::streamsize compressedSize = compressedFile.tellg();
    compressedFile.close();
    std::cout << "Compressed File Size: " << compressedSize << " bytes\n";

    // Размер распакованного файла
    std::ifstream decompressedFile(decompressedFileName, std::ios::binary | std::ios::ate);
    std::streamsize decompressedSize = decompressedFile.tellg();
    decompressedFile.close();
    std::cout << "Decompressed File Size: " << decompressedSize << " bytes\n";

    // Статистика сжатия
    double compressionRatio = static_cast<double>(compressedSize) / inputSize;
    std::cout << "Compression Ratio: " << compressionRatio * 100 << "%\n";

    // Статистика времени выполнения (может потребоваться дополнительная р
}

HuffmanCoding::~HuffmanCoding() {
    // Реализация логики очистки (например, удаление динамически выделенной памяти)
}

int main() {
    std::string inputFileName = "input.txt";
    std::string compressedFileName = "compressed.bin";
    std::string decompressedFileName = "decompressed.txt";

    HuffmanCoding huffmanCoder(inputFileName, compressedFileName, decompressedFileName);

    huffmanCoder.compress();
    huffmanCoder.decompress();
    huffmanCoder.displayStatistics();

    // Пример входных данных
    vector<Product> popularProducts = { {1, true}, {2, true}, {3, true} };

    // Создание объекта магазина
    Shop shop(popularProducts);

    // Получение заказов пользователя
    vector<Product> customerOrders = UserInterface::getUserOrders();

    // Обработка заказов
    shop.processOrders(customerOrders);

    // Добавление нового товара
    Product newProduct = UserInterface::inputProduct();
    shop.addProduct(newProduct);

    // Обновление существующего товара
    int productIdToUpdate = UserInterface::getProductId();
    Product updatedProduct = UserInterface::inputProduct();
    shop.updateProduct(productIdToUpdate, updatedProduct);

    // Удаление товара
    int productIdToRemove = UserInterface::getProductId();
    shop.removeProduct(productIdToRemove);

    return 0;
}