#include <fstream>
#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>

using namespace std;

ifstream f("graf.in");
ofstream o("graf.out");
unordered_map<int, vector<int>> graph;
vector<int> visited, controls, d;
queue<int> q;
int n, m;

void bfs(int node) {
    q.push(node);
    visited[node] = true;
    d[node] = 0;

    while (!q.empty()){
        node = q.front(); q.pop();
        for (int& neighbour : graph[node])
            if (!visited[neighbour]){
                if (!d[neighbour] || d[node] + 1 < d[neighbour])
                    d[neighbour] = d[node] + 1;
                visited[neighbour] = true;
                q.push(neighbour);
            }
    }
}

int main() {
    int a, b;
    f >> n >> m;
    for (int i = 0; i < m; ++i) {
        f >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    d.resize(n + 1, 0);
    while (f >> a)
        controls.push_back(a);

    for (int& control : controls) {
        visited.assign(n + 1, false);
        bfs(control);
    }
    for (int& control : controls)
        d[control] = 0;

    for (auto it = d.begin() + 1; it < d.end(); it++)
        o << *it << ' ';

    return 0;
}
