#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

unordered_map<int, vector<int>> graph;
vector<bool> visited;
stack<int> s;
// Timpul la care este accesat un nod
int t = 0;
// Un vector care ne spune timpul terminarii accesarii cu nodul respectiv
vector<int> fin;

void dfs(int node) {
    visited[node] = true;

    for (int& neighbour : graph[node])
        if (!visited[neighbour])
            dfs(neighbour);
        // `neighbour` e gri, in explorare, in stiva
        else if (fin[neighbour] == 0) {
            cout << "IMPOSSIBLE";
            exit(0);
        }

    fin[node] = t++;
    s.push(node);
}

int main(){
    int n, m, a, b;
    cin >> n >> m;
    for (int i = 0 ; i < m; ++i){
        cin >> a >> b;
        graph[a].push_back(b);
    }
    visited.resize(n + 1, false);
    fin.resize(n + 1, 0);

    for (int i = 0; i <= n; ++i)
        if (!visited[i])
            dfs(i);

    // Unwind the stack, o sa iasa grupate
    // in ordinea inversa descoperirii comp conexe
    while (s.top()) {
        cout << s.top() << " ";
        s.pop();
    }

    return 0;
}
