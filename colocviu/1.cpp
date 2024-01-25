#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>

using namespace std;

map<int, vector<int>> graph;
set<pair<int, int>> dfs_ap, bfs_ap;

void dfs(vector<bool>& vis, const int& node) {
    vis[node] = true;
    for (const int& neighbor : graph[node]) {
        if (!vis[neighbor]) {
            dfs_ap.insert(make_pair(node, neighbor));
            dfs(vis, neighbor);
        }
    }
}

void bfs(vector<bool>& vis, const int& start) {
    queue<int> q; q.push(start);
    vis[start] = true;

    while (!q.empty()) {
        int curr = q.front(); q.pop();

        for (const int& neighbor : graph[curr])
            if (!vis[neighbor]) {
                bfs_ap.insert(make_pair(curr, neighbor));
                vis[neighbor] = true;
                q.push(neighbor);
            }
    }
}

int main() {
    int n, m, x, y;

    cin >> n >> m;

    if (m <= n - 1) {
        cout << "Nu";
        return 0;
    }

    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    vector<bool> dfs_vis(n + 1, false), bfs_vis(n + 1, false);

    dfs(dfs_vis, 1);
    for (int i = 1; i <= n; i++)
        if (!dfs_vis[i]) {
            cout << "Nu";
            return 0;
        }
    bfs(bfs_vis, 1);

    for (const pair<int, int>& dfs_it : dfs_ap) {
        bool ok = false;

        for (const pair<int, int>& bfs_it : bfs_ap)
            if ((dfs_it.first == bfs_it.first && dfs_it.second == bfs_it.second) || (dfs_it.first == bfs_it.second && dfs_it.second == bfs_it.first))
                ok = true;
        
        if (!ok) {
            cout << "Da\n";
        
            for (const pair<int, int>& dfs_it : dfs_ap)
                cout << dfs_it.first << ' ' << dfs_it.second << '\n';
            for (const pair<int, int>& bfs_it : bfs_ap)
                cout << bfs_it.first << ' ' << bfs_it.second << '\n';
        
            return 0;
        }
    }
    
    cout << "Nu";
    return 0;
}
