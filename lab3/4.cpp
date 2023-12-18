#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("catun.in");
ofstream fout("catun.out");

unordered_map<int, vector<pair<int, int>>> graph;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
vector<int> fortareata, d;

int main() {
    int n, m, k, x, y, z;
    fin >> n >> m >> k;
    fortareata.resize(n + 1);
    d.resize(n + 1, __INT_MAX__);
    for (int i = 0; i < k; i++) {
        fin >> x;
        fortareata[x] = x;
        q.push({0, x});
        d[x] = 0; 
    }
    for (int i = 0; i < m; i++) {
        fin >> x >> y >> z;
        graph[x].push_back({y, z});
        graph[y].push_back({x, z});
    }

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        for (pair<int, int>& it : graph[u])
            if (d[u] + it.second < d[it.first]) {
                d[it.first] = d[u] + it.second;
                q.push({d[it.first], it.first});
                fortareata[it.first] = fortareata[u];
            }
            else if (d[u] + it.second == d[it.first])
                fortareata[it.first] = min(fortareata[it.first], fortareata[u]);
    }

    for (int i = 1; i <= n; i++)
        if (fortareata[i] == i)
            fout << 0 << ' ';
        else
            fout << fortareata[i] << ' ';

    return 0;
}
