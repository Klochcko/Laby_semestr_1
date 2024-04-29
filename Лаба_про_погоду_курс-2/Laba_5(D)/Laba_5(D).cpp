#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <locale>

using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> adjList;

public:
    Graph(int V) : vertices(V), adjList(V + 1) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    void addUndirectedEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void DFSUtil(int start, unordered_set<int>& visited) {
        stack<int> stk;
        stk.push(start);
        visited.insert(start);

        while (!stk.empty()) {
            int current = stk.top();
            stk.pop();
            cout << current << " ";

            for (int neighbor : adjList[current]) {
                if (visited.find(neighbor) == visited.end()) {
                    stk.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }
    }

    void DFSForest() {
        unordered_set<int> visited;

        cout << "Ліс пошуку в глибину:" << endl;
        for (int i = 1; i <= vertices; ++i) {
            if (visited.find(i) == visited.end()) {
                DFSUtil(i, visited);
                cout << endl;
            }
        }
    }
};

int main() {

    locale::global(locale("uk_UA"));

    int n; // кількість вершин графа
    cout << "Введіть кількість вершин графа: ";
    cin >> n;

    Graph g(n);

    int m; // кількість ребер
    cout << "Введіть кількість ребер графа: ";
    cin >> m;

    cout << "Введіть ребра графа (у форматі вершина1 вершина2):" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g.addUndirectedEdge(u, v);
    }

    g.DFSForest();

    return 0;
}
