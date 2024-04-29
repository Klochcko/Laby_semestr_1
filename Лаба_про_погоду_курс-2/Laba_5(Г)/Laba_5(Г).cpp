#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <locale>

using namespace std;

// Структура для представлення графа
struct Graph {
    unordered_map<char, vector<char>> adjList;

    // Додати ребро в граф
    void addEdge(char src, char dest) {
        adjList[src].push_back(dest);
    }
};

// Допоміжна функція для перевірки наявності циклів у графі (DFS)
bool isCyclicUtil(char v, vector<bool>& visited, vector<bool>& recStack, Graph& g) {
    if (!visited[v]) {
        visited[v] = true;
        recStack[v] = true;

        for (char neighbor : g.adjList[v]) {
            if (!visited[neighbor] && isCyclicUtil(neighbor, visited, recStack, g))
                return true;
            else if (recStack[neighbor])
                return true;
        }
    }
    recStack[v] = false;
    return false;
}

// Функція для перевірки наявності циклів у графі
bool isCyclic(Graph& g) {
    vector<bool> visited(256, false);
    vector<bool> recStack(256, false);

    for (auto& pair : g.adjList) {
        char node = pair.first;
        if (isCyclicUtil(node, visited, recStack, g))
            return true;
    }
    return false;
}

// Функція для визначення порядку прочитання дисциплін
vector<char> determineCourseOrder(Graph& g) {
    vector<char> courseOrder;

    if (isCyclic(g)) {
        cout << "Неможливо визначити порядок, що уникне зациклення" << endl;
        return courseOrder;
    }

    unordered_map<char, int> inDegree;
    queue<char> q;

    // Обчислюємо ступені входу для кожної вершини
    for (auto& pair : g.adjList) {
        char node = pair.first;
        inDegree[node] = 0;
    }

    for (auto& pair : g.adjList) {
        char node = pair.first;
        for (char neighbor : g.adjList[node]) {
            inDegree[neighbor]++;
        }
    }

    // Додаємо вершини з нульовим ступенем входу у чергу
    for (auto& pair : inDegree) {
        if (pair.second == 0) {
            q.push(pair.first);
        }
    }

    // Використовуємо топологічне сортування
    while (!q.empty()) {
        char node = q.front();
        q.pop();
        courseOrder.push_back(node);
        for (char neighbor : g.adjList[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    return courseOrder;
}

int main() {

    locale::global(locale("uk_UA"));

    Graph g;

    // Додавання ребер у граф згідно вимог
    g.addEdge('C', 'A');
    g.addEdge('C', 'B');
    g.addEdge('A', 'D');
    g.addEdge('B', 'D');

    // Визначення порядку прочитання дисциплін
    vector<char> courseOrder = determineCourseOrder(g);

    // Вивід порядку прочитання
    cout << "Порядок прочитання дисциплін: ";
    for (char course : courseOrder) {
        cout << course << " ";
    }
    cout << endl;

    return 0;
}
