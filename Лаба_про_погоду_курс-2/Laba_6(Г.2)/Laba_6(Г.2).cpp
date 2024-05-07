#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

// Структура для представлення ребра графа
struct Edge {
    int from;
    int to;
    int weight;
};

class BellmanFord {
private:
    int num_vertices;
    vector<Edge> edges;

public:
    BellmanFord(int n) : num_vertices(n) {}

    void addEdge(int from, int to, int weight) {
        edges.push_back({ from, to, weight });
    }

    vector<int> shortestPaths(int start) {
        vector<int> dist(num_vertices, INF);
        dist[start] = 0;

        // Запускаємо алгоритм Беллмана-Форда
        for (int i = 0; i < num_vertices - 1; ++i) {
            for (const Edge& e : edges) {
                if (dist[e.from] != INF && dist[e.from] + e.weight < dist[e.to]) {
                    dist[e.to] = dist[e.from] + e.weight;
                }
            }
        }

        // Перевірка на наявність від'ємного циклу
        for (const Edge& e : edges) {
            if (dist[e.from] != INF && dist[e.from] + e.weight < dist[e.to]) {
                cout << "Граф містить від'ємний цикл" << endl;
                return {};
            }
        }

        return dist;
    }
};

int main() {
    // Кількість аеропортів
    const int num_airports = 6;

    // Створення графу представлення маршрутів та їх вартостей
    BellmanFord graph(num_airports);
    
    graph.addEdge(0, 1, 200);
    graph.addEdge(1, 0, 200);
    graph.addEdge(0, 5, 500); 
    graph.addEdge(5, 0, 500); 

    
    vector<int> shortest_paths = graph.shortestPaths(0);

    
    cout << "Мінімальна вартість перельоту з Києва до Стокгольма: " << shortest_paths[5] << endl;
    cout << "Мінімальна вартість перельоту з Києва до Стокгольма: " << shortest_paths[1] << endl;

    return 0;
}
