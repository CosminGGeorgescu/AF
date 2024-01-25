// * Algoritmul lui Kosaraju
// * Folosim DFS pentru determinarea componentelor tare conexe
// * Complexitate O(|V| + |E|)

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

unordered_map<int, vector<int>> graph, graph_t;
vector<int> visited;
// Timpul la care este accesat un nod
int t = 0;
// Un vector care ne spune timpul terminarii accesarii cu nodul respectiv
map<int, int> fin;
// Indice al carei comp tare conex apartine fiecare nod
int tconex = 0;

void dfs(int node) {
    visited[node] = 1;

    for (int& neighbour : graph[node])
        if (!visited[neighbour])
            dfs(neighbour);

    fin[node] = t++;
}

void dfs_t(int node) {
    visited[node] = tconex;

    for (int& neighbour : graph_t[node])
        if (!visited[neighbour])
            dfs_t(neighbour);
}

int main(){
    int n, m, a, b;
    cin >> n >> m;
    for (int i = 0 ; i < m; ++i){
        cin >> a >> b;
        graph[a].push_back(b);
        graph_t[b].push_back(a);
    }
    visited.resize(n + 1, 0);

    for (int i = 1; i <= n; ++i)
        if (!visited[i])
            dfs(i);
    
    vector<pair<int, int>> sorted(fin.begin(), fin.end());
    sort(sorted.begin(), sorted.end(), [&](const pair<int, int> a, const pair<int, int> b) { return a.second > b.second; });
    
    fill(visited.begin(), visited.end(), 0);
    for (pair<int, int>& it : sorted)
        if (!visited[it.first]){
            tconex++;
            dfs_t(it.first);
        }

    cout << tconex << '\n';
    for (vector<int>::iterator it = visited.begin() + 1; it != visited.end(); it++)
        cout << *it << ' ';

    return 0;
}
