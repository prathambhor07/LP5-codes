#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> adj;
    vector<bool> visited;

public:
    Graph(int v) : vertices(v), adj(v), visited(v, false) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void parallelDFS(int start) {
        stack<int> s;
        s.push(start);
        visited[start] = true;

        while (!s.empty()) {
            int current;
            #pragma omp critical
            {
                current = s.top();
                s.pop();
            }

            cout << current << " ";

            #pragma omp parallel for
            for (int neighbor : adj[current]) {
                if (!visited[neighbor]) {
                    #pragma omp critical
                    {
                        s.push(neighbor);
                        visited[neighbor] = true;
                    }
                }
            }
        }
    }
};

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    cout << "Parallel Depth First Search: ";
    g.parallelDFS(0);

    return 0;
}
