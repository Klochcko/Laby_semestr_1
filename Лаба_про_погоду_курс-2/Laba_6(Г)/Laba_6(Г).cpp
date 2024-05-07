#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

class FloydWarshall {
private:
    int num_vertices;
    vector<vector<int>> dist;

public:
    FloydWarshall(int n) : num_vertices(n) {
        dist.assign(n, vector<int>(n, INF));
    }

    void addEdge(int from, int to, int weight) {
        dist[from][to] = weight;
    }

    void shortestPaths() {
        // Алгоритм Флойда-Уоршелла
        for (int k = 0; k < num_vertices; ++k) {
            for (int i = 0; i < num_vertices; ++i) {
                for (int j = 0; j < num_vertices; ++j) {
                    if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    int getShortestPath(int from, int to) {
        return dist[from][to];
    }
};

int main() {
    const int num_airports = 6;
    FloydWarshall fw(num_airports);

    // Додавання ребер графу (маршрутів та їх вартостей)
    fw.addEdge(0, 1, 200);
    fw.addEdge(1, 0, 200);
    fw.addEdge(0, 2, 500); 
    fw.addEdge(2, 0, 500); 
    fw.addEdge(1, 3, 300); 
    fw.addEdge(3, 1, 300); 
    fw.addEdge(2, 4, 400); 
    fw.addEdge(4, 2, 400); 
    fw.addEdge(3, 4, 600); 
    fw.addEdge(4, 3, 600); 
    fw.addEdge(4, 5, 700); 
    fw.addEdge(5, 4, 700); 

    fw.shortestPaths();

    cout << "Minimum flight prices between all pairs of cities:" << endl;
    for (int i = 0; i < num_airports; ++i) {
        for (int j = 0; j < num_airports; ++j) {
            if (i != j) {
                int shortest_path = fw.getShortestPath(i, j);
                cout << "З " << i << " for " << j << ": " << shortest_path << endl;
            }
        }
    }

    return 0;
}

