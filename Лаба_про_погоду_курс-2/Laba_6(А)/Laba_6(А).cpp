#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Клас для представлення графа
class Graph {
private:
    int V; // Кількість вершин
    vector<vector<pair<int, double>>> adjList; // Список суміжності (вершина, вага ребра)

public:
    // Конструктор класу Graph
    Graph(int vertices) : V(vertices) {
        adjList.resize(V);
    }

    // Додавання ребра до графа
    void addEdge(int from, int to, double weight) {
        adjList[from].push_back(make_pair(to, weight));
    }

    // Метод для виконання алгоритму Дейкстри
    vector<double> dijkstra(int start) {
        // Ініціалізуємо відстані до всіх вершин як нескінченні
        vector<double> dist(V, numeric_limits<double>::infinity());
        // Ініціалізуємо відстань від початкової вершини до неї самої як 0
        dist[start] = 0;

        // Пріоритетна черга для вибору вершин з мінімальною відстанню
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
        pq.push(make_pair(0, start));

        // Поки черга не пуста
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            // Проходимо по всіх суміжних вершинах
            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                double weight = neighbor.second;

                // Оновлюємо відстань, якщо знайдено коротший шлях
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        return dist;
    }
};

// Функція для тестування алгоритму Дейкстри
void testDijkstra() {
    int V = 4; // Кількість вершин
    Graph graph(V);

    // Додавання ребер до графа
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 5);
    graph.addEdge(1, 3, 7);

    int startVertex = 0; // Початкова вершина
    vector<double> distances = graph.dijkstra(startVertex);

    // Виведення результатів
    cout << "Shortest distances from vertex " << startVertex << ":\n";
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << ": " << distances[i] << endl;
    }
}

int main() {
    // Тестування алгоритму Дейкстри
    testDijkstra();

    return 0;
}
