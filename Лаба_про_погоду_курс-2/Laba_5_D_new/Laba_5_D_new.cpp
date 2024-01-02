#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <locale>

class Graph {
private:
    int vertices; // Кількість вершин графа
    std::vector<std::vector<int>> adjacencyList; // Список суміжності

public:
    Graph(int v) : vertices(v), adjacencyList(v) {}

    // Додати ребро до графа
    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u); // Для неорієнтованого графа
    }

    // Пошук в ширину
    void BFS(int start, std::vector<std::set<int>>& tree) {
        std::queue<int> queue;
        std::vector<bool> visited(vertices, false);

        queue.push(start);
        visited[start] = true;

        while (!queue.empty()) {
            int currentVertex = queue.front();
            queue.pop();

            for (int neighbor : adjacencyList[currentVertex]) {
                if (!visited[neighbor]) {
                    queue.push(neighbor);
                    visited[neighbor] = true;

                    // Додаємо ребро (currentVertex, neighbor) до дерева пошуку в ширину
                    tree[start].insert(neighbor);
                }
            }
        }
    }

    // Вивести дерево пошуку в ширину
    void printBFSTree() {
        std::vector<std::set<int>> tree(vertices);

        for (int i = 0; i < vertices; ++i) {
            if (!tree[i].empty()) {
                std::cout << "Дерево пошуку з вершини " << i << ":\n";
                for (int vertex : tree[i]) {
                    std::cout << i << " -> " << vertex << "\n";
                }
            }
        }
    }
};

int main() {

    std::locale::global(std::locale("ru_RU"));

    int vertices, edges;

    std::cout << "Введіть кількість вершин та ребер графа: ";
    std::cin >> vertices >> edges;

    Graph graph(vertices);

    std::cout << "Введіть ребра графа:\n";
    for (int i = 0; i < edges; ++i) {
        int u, v;
        std::cout << "Ребро " << (i + 1) << ": ";
        std::cin >> u >> v;
        graph.addEdge(u, v);
    }

    std::vector<std::set<int>> tree(vertices);

    // Виконати пошук в ширину для кожної вершини, якщо вона ще не була відвідана
    for (int i = 0; i < vertices; ++i) {
        if (!tree[i].empty()) {
            graph.BFS(i, tree);
        }
    }

    // Вивести дерево пошуку в ширину
    graph.printBFSTree();

    return 0;
}
