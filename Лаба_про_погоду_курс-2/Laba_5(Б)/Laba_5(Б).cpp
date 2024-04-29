#include <iostream>
#include <vector>
#include <queue>
#include <locale>

using namespace std;

class Graph {
    int V; // кількість вершин
    vector<vector<int>> adj; // список суміжності

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    // Додати ребро в граф
    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v); // для неорієнтованого графа
    }

    // Пошук в ширину
    vector<int> BFS(int start) {
        vector<bool> visited(V, false); // масив відвіданих вершин
        vector<int> parent(V, -1); // масив батьківських вершин для побудови дерева
        queue<int> q; // черга для обходу вершин
        vector<int> traversal; // результат обходу

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            traversal.push_back(u); // додаємо вершину до результату обходу
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        return traversal;
    }

    // Побудова дерева пошуку в ширину
    vector<pair<int, int>> buildBFSTree(int start) {
        vector<int> parent(V, -1); // масив батьківських вершин для побудови дерева
        queue<int> q; // черга для обходу вершин
        vector<pair<int, int>> tree; // дерево пошуку

        parent[start] = start; // початкова вершина має сама себе як батька
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (parent[v] == -1) {
                    parent[v] = u;
                    q.push(v);
                    tree.push_back({ u, v }); // додаємо ребро до дерева
                }
            }
        }

        return tree;
    }

    // Вивести результат обходу
    void printTraversal(const vector<int>& traversal) {
        cout << "Порядок обходу графу в ширину: ";
        for (int v : traversal) {
            cout << v << " ";
        }
        cout << endl;
    }

    // Вивести дерево пошуку в ширину
    void printBFSTree(const vector<pair<int, int>>& tree) {
        cout << "Дерево пошуку в ширину: \n";
        for (const auto& edge : tree) {
            cout << edge.first << " -> " << edge.second << endl;
        }
    }
};

int main() {

    locale::global(locale("uk_UA"));

    Graph g(6); // створюємо граф з 6 вершинами
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);

    vector<int> traversal = g.BFS(0); // обхід в ширину
    g.printTraversal(traversal); // виводимо результат обходу

    cout << endl;

    vector<pair<int, int>> tree = g.buildBFSTree(0); // побудова дерева пошуку в ширину
    g.printBFSTree(tree); // виводимо дерево пошуку

    return 0;
}
