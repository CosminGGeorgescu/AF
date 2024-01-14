#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

ifstream fin("retea.in");

unordered_map<int, vector<pair<int, int>>> graph;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
vector<int> d, tata;


int main() {
    int n, m, k, s, t, x, y, z;
    fin >> n >> m;
    for (int i = 0; i < m; i++) {
        fin >> x >> y >> z;
        graph[x].push_back({y, z});
    }

    cin >> s >> t;

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
    
    stack<int> drum;
    int curr = t;
    while (curr != s) {
        drum.push(curr);
        curr = tata[curr];
    }
    cout << s << ' ';
    while (!drum.empty()) {
        cout << drum.top() << ' ';
        drum.pop();
    }
    cout << '\n';

    return 0;
}
