#include <iostream>
#include <vector>
#include <queue>
#include <locale>

using namespace std;

class Graph {
public:
    int vertices;
    vector<vector<int>> adjacencyList;

    Graph(int n) : vertices(n), adjacencyList(n) {}

    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u); // Assuming an undirected graph
    }

    void breadthFirstSearch(int start) {
        vector<bool> visited(vertices, false);
        vector<int> parent(vertices, -1); // Array to store the parent of each vertex in the BFS tree

        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            cout << "Visiting vertex: " << current << endl;

            for (int neighbor : adjacencyList[current]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                }
            }
        }

        // Output the BFS tree
        cout << "BFS Tree:" << endl;
        for (int i = 0; i < vertices; ++i) {
            if (parent[i] != -1) {
                cout << "Edge: (" << parent[i] << " -> " << i << ")" << endl;
            }
        }
    }
};

int main() {

    locale::global(locale("uk_UA"));

    int n; // Кількість вершин графа
    cout << "Введіть кількість вершин графа: ";
    cin >> n;

    Graph graph(n);

    // Додавання ребер графа
    int u, v;
    cout << "Введіть ребра графа (по парі чисел, -1 для завершення):" << endl;
    while (true) {
        cin >> u;
        if (u == -1) break;
        cin >> v;
        graph.addEdge(u, v);
    }

    // Початкова вершина для обходу в ширину
    int startVertex;
    cout << "Введіть початкову вершину для обходу в ширину: ";
    cin >> startVertex;

    // Обхід в ширину та побудова дерева пошуку
    cout << "Результат обходу в ширину:" << endl;
    graph.breadthFirstSearch(startVertex);

    return 0;
}
