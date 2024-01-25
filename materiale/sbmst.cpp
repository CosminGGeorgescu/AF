// * Second best minimum spanning tree
// * Facem APM si apoi eliminam cate o muchie din el si vedem costul

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct DisjointSet {
    int parent[101];
    int rank[101];

    DisjointSet(int n) {
        for (int i = 1; i <= n; i++) {
            this->parent[i] = i;
            this->rank[i] = 1;
        }
    }

    int find(int& a) {
        return this->parent[a] == a ? a : this->parent[a] = this->find(this->parent[a]);
    }

    void _union(int& a, int& b) {
        auto helper = [&, this](const int a, const int b) {
            this->parent[b] = a;
            this->rank[a] += this->rank[b];
            this->rank[b] = 0;
        };
        
        int pa = this->find(a), pb = this->find(b);
        
        if (pa == pb)
            return;

        this->rank[pa] > this->rank[pb] ? helper(pa, pb) : helper(pb, pa);
    }
};

struct edge {
    int src, dest, cost;

    const bool operator!=(const edge& other) const {
        return this->src != other.src || this->dest != other.dest || this->cost != other.cost;
    }
};

int main() {
    int n, m, s1 = 0, s2 = __INT_MAX__, x, y, z;
    cin >> n >> m;
    vector<edge> edges(m), apm;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> z;
        edges[i] = {x, y, z};
    }

    sort(edges.begin(), edges.end(), [&](const edge a, const edge b) { return a.cost < b.cost; });

    DisjointSet ds(n);
    for (int i = 0; i < m; i++)
        if (ds.find(edges[i].src) != ds.find(edges[i].dest)) {
            ds._union(edges[i].src, edges[i].dest);
            apm.push_back(edges[i]);
            s1 += edges[i].cost;
        }

    for (int i = 0; i < n - 1; i++) {
        DisjointSet ds(n);
        int si = 0;
        
        for (int j = 0; j < m; j++)
            if (edges[j] != apm[i] && ds.find(edges[j].src) != ds.find(edges[j].dest)) {
                ds._union(edges[j].src, edges[j].dest);
                si += edges[j].cost;
            }
        
        if (s1 <= si && si < s2)
            s2 = si;
    }

    cout << s1 << ' ' << s2;

    return 0;
}
