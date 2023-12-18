#include <fstream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <iostream>

using namespace std;

ifstream file("activitati.in");
unordered_map<int, vector<int>> graph;
vector<bool> visited;
stack<int> s;
vector<int> dm, dp, fin, d, tata;
int t;

void dfs(int node) {
    visited[node] = true;

    for (int& neighbour : graph[node])
        if (!visited[neighbour])
            dfs(neighbour);
        else if (!fin[neighbour])
            exit(0);

    fin[node] = t++;
    s.push(node);
}

vector<int> sortare_topologica(int& n) {
    vector<int> temp;
    
    visited.resize(n + 1, false);
    fin.resize(n + 1, 0);

    for (int i = 0; i <= n; i++)
        if (!visited[i])
            dfs(i);

    temp.push_back(0);
    while (!s.empty()) {
        temp.push_back(s.top());
        s.pop();
    }
    temp.pop_back();

    return temp;
}

int main() {
    int n, m, x, y;
    file >> n;
    int w[n + 1]; w[0] = 0;
    for (int i = 1; i <= n; i++)
        file >> w[i];
    file >> m;
    dm.resize(n + 1, 0);
    dp.resize(n + 1, 0);
    for (int i = 0; i < m; i++) {
        file >> x >> y;
        graph[x].push_back(y);
        dm[y]--;
        dp[x]++;
    }

    tata.resize(n + 2, 0);
    d.resize(n + 2, -2147483648);
    d[0] = 0;

    vector<int> sortTop = sortare_topologica(n);
    
    for (int i = 1; i <= n; i++)
        if (!dm[i])
            graph[0].push_back(i);
    for (int i = 1; i <= n; i++)
        if (!dp[i])
            graph[i].push_back(n + 1);
    for (int& u : sortTop)
        for (int& v : graph[u])
            if (d[u] + w[u] > d[v]) {
                d[v] = d[u] + w[u];
                tata[v] = u;
            }

    cout << "Timp minim " << d[n + 1] << "\nActivitati critice: ";
    int curr = n + 1;
    while (tata[curr])
        cout << (curr = tata[curr]) << ' ';
    for (int i = 1; i <= n; i++)
        cout << '\n' << i << ": " << d[i] << ' ' << d[i] + w[i];

    return 0;
}
