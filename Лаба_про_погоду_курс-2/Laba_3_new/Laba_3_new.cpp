#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Huffman Coding class
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
    // Implement your logic to display compression/decompression statistics
}

HuffmanCoding::~HuffmanCoding() {
    // Implement your logic for cleanup (e.g., deleting dynamically allocated memory)
}

// Shop class (from your previous code)
struct Product {
    int id;
    bool isPopular;
};

class Shop {
public:
    Shop(const vector<Product>& popularProducts) : popularProducts(popularProducts), totalTime(0) {}

    void processOrders(const vector<Product>& customerOrders);

    void addProduct(const Product& newProduct);
    void updateProduct(int productId, const Product& updatedProduct);
    void removeProduct(int productId);

private:
    queue<Product> productsUnderHand;
    unordered_set<int> popularProductsUnderHand;
    vector<Product> popularProducts;
    int totalTime;
};

void Shop::processOrders(const vector<Product>& customerOrders) {
    for (const auto& order : customerOrders) {
        bool isAvailable = false;

        if (popularProductsUnderHand.count(order.id) > 0) {
            isAvailable = true;
        }
        else {
            if (productsUnderHand.size() < popularProducts.size()) {
                productsUnderHand.push(order);
                popularProductsUnderHand.insert(order.id);
            }
            else {
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

                popularProductsUnderHand.erase(latestPopularProduct.id);

                productsUnderHand.push(order);
                popularProductsUnderHand.insert(order.id);

                totalTime += 1;
            }
        }

        totalTime += 1;

        // Display order information
        cout << "Order for Product " << order.id << " is ";
        if (isAvailable) {
            cout << "available ";
        }
        else {
            cout << "not available ";
        }
        cout << "(Total Time: " << totalTime << " units)" << endl;
    }
}

void Shop::addProduct(const Product& newProduct) {
    popularProducts.push_back(newProduct);
}

void Shop::updateProduct(int productId, const Product& updatedProduct) {
    for (auto& product : popularProducts) {
        if (product.id == productId) {
            product = updatedProduct;
            break;
        }
    }
}

void Shop::removeProduct(int productId) {
    auto it = remove_if(popularProducts.begin(), popularProducts.end(),
        [productId](const Product& product) { return product.id == productId; });

    popularProducts.erase(it, popularProducts.end());
}

// UserInterface class (from your previous code)
class UserInterface {
public:
    static vector<Product> getUserOrders();
    static Product inputProduct();
    static int getProductId();
    static void displayOrderInfo(const Product& product, bool isAvailable, int totalTime);
};

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
    Product newProduct;
    cout << "Enter the product ID: ";
    cin >> newProduct.id;

    cout << "Is the product popular? (1 for yes, 0 for no): ";
    cin >> newProduct.isPopular;

    return newProduct;
}

int UserInterface::getProductId() {
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

int main() {
    // Example input for Shop
    vector<Product> popularProducts = { {1, true}, {2, true}, {3, true} };
    Shop shop(popularProducts);

    // Example input for UserInterface
    vector<Product> customerOrders = UserInterface::getUserOrders();
    shop.processOrders(customerOrders);

    // Example input for Shop (continued)
    Product newProduct = UserInterface::inputProduct();
    shop.addProduct(newProduct);

    int productIdToUpdate = UserInterface::getProductId();
    Product updatedProduct = UserInterface::inputProduct();
    shop.updateProduct(productIdToUpdate, updatedProduct);

    int productIdToRemove = UserInterface::getProductId();
    shop.removeProduct(productIdToRemove);

    // Example input for HuffmanCoding
    std::string inputFileName = "input.txt";
    std::string compressedFileName = "compressed.bin";
    std::string decompressedFileName = "decompressed.txt";

    HuffmanCoding huffmanCoder(inputFileName, compressedFileName, decompressedFileName);

    huffmanCoder.compress();
    huffmanCoder.decompress();
    huffmanCoder.displayStatistics();

    return 0;
}
