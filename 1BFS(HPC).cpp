#include <iostream>
#include <vector>
#include <queue>
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

    void parallelBFS(int start) {
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int q_size = q.size();

            #pragma omp parallel for
            for (int i = 0; i < q_size; ++i) {
                int current;
                #pragma omp critical
                {
                    current = q.front();
                    q.pop();
                }

                cout << current << " ";

                for (int neighbor : adj[current]) {
                    if (!visited[neighbor]) {
                        #pragma omp critical
                        {
                            q.push(neighbor);
                            visited[neighbor] = true;
                        }
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

    cout << "Parallel Breadth First Search: ";
    g.parallelBFS(0);

    return 0;
}
