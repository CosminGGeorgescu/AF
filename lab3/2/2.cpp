#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

ifstream fin("grafpond.in");

unordered_map<int, vector<pair<int, int>>> graph;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
vector<int> controls, d, tata;


int main() {
    int n, m, k, s, x, y, z;
    fin >> n >> m;
    for (int i = 0; i < m; i++) {
        fin >> x >> y >> z;
        graph[x].push_back({y, z});
        graph[y].push_back({x, z});
    }
    fin >> k;
    for (int i = 0; i < k; i++) {
        fin >> x;
        controls.push_back(x);
    }
    fin >> s;

    q.push({0, s});
    d.resize(n + 1, __INT_MAX__);
    tata.resize(n + 1, 0);
    d[s] = 0;

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        for (pair<int, int>& it : graph[u])
            if (d[u] + it.second < d[it.first]) {
                d[it.first] = d[u] + it.second;
                q.push({d[it.first], it.first});
                tata[it.first] = u;
            }
    }

    int min = -1;
    for (int& control : controls)
        if (d[control] < d[min] || min == -1)
            min = control;
    cout << min << '\n';

    stack<int> drum;
    while (min != s) {
        drum.push(min);
        min = tata[min];
    }
    cout << s << ' ';
    while (!drum.empty()) {
        cout << drum.top() << ' ';
        drum.pop();
    }
    cout << '\n';
    
    return 0;
}
