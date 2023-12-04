#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("apm2.in");
ofstream fout("apm2.out");

struct DisjointSet {
    int parent[10001];
    int rank[10001];

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
};

int main() {

    edge edges[100000], apm[10000], proposals[1000];
    int n, m, q, x, y, z;
    fin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        fin >> x >> y >> z;
        edges[i] = {x, y, z};
    }
    for (int i = 0; i < q; i++) {
        fin >> x >> y;
        proposals[i] = {x, y, -1};
    }

    sort(edges, edges + m, [&](const edge a, const edge b) { return a.cost < b.cost; });

    DisjointSet ds(n);
    for (int i = 0; i < m; i++)
        if (ds.find(edges[i].src) != ds.find(edges[i].dest)) {
            ds._union(edges[i].src, edges[i].dest);

            for (int j = 0; j < q; j++)
                if (proposals[j].cost == -1 && ds.find(proposals[j].src) == ds.find(proposals[j].dest))
                    proposals[j].cost = edges[i].cost - 1;
        }

    for (int i = 0; i < q; i++)
        fout << proposals[i].cost << '\n';

    return 0;
}
