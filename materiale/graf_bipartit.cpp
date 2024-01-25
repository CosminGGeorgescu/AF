// * Folosim DFS pentru a determina o impartire binara a grafului
// * Complexitate O(|V| + |E|)

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<int, vector<int>> graph;
// Repartizarea nodurilor
vector<int> teams;

bool dfs(int node, int team) {
    teams[node] = team;
    for (const int& neighbor : graph[node]) {
        // Dam fail daca doua noduri vecine au aceeasi echipa 
        // sau continuam colorarea si are un conflict at some point
        if (teams[neighbor] == team || (teams[neighbor] == 0 && !dfs(neighbor, 3 - team))) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, m, a, b;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    teams.resize(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        // Incepem colorarea componentei conexe cu `1`
        if (teams[i] == 0 && !dfs(i, 1)) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }
   
    for (int i = 1; i <= n; ++i) {
        cout << teams[i] << " ";
    }

    return 0;
}
