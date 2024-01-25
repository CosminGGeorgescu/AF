// * Bellman-Ford
// * Complexitate O(n * m)

#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <optional>
#include <algorithm>
#include <iterator>

using namespace std;

ifstream fin("grafpond.in");
ofstream fout("grafpond.out");

vector<tuple<int, int, int>> graph;
vector<optional<int>> d;
vector<int> tata;


int main() {
    int n, m, k, s, x, y, z;
    fin >> n >> m;
    for (int i = 0; i < m; i++) {
        fin >> x >> y >> z;
        graph.push_back({x, y, z});
    }
    fin >> s;

    d.resize(n + 1);
    tata.resize(n + 1, 0);
    d[s] = 0;
    
    for (int k = 1; k <= n - 1; k++)
        for (const tuple<int, int, int>& muchie : graph) {
            int u = get<0>(muchie), v = get<1>(muchie), w = get<2>(muchie);
            if (d[u].has_value() && d[u].value() + w < d[v].value_or(__INT_MAX__)) {
                d[v] = d[u].value() + w;
                tata[v] = u;
            }
        }


    for (const tuple<int, int, int>& muchie : graph) {
        int u = get<0>(muchie), v = get<1>(muchie), w = get<2>(muchie);
        if (d[u].has_value() && d[u].value() + w < d[v].value_or(__INT_MAX__)) {
            fout << "Circuit de cost negativ:\n";
            
            stack<int> s;
            int curr = u;
            
            while (curr != v) {
                s.push(curr);
                curr = tata[curr];
            }
            s.push(curr);

            while (!s.empty()) {
                fout << s.top() << ' ';
                s.pop();
            }

            return 0;
        }
    }
    
    for (int i = 1; i <= n; i++)
        if (i != s) {
            stack<int> temp;
            int curr = i, cost = 0;
            
            while (curr != s) {
                temp.push(curr);
                cost += get<2>(find_if(graph.begin(), graph.end(), [&](const tuple<int, int, int>& muchie) {return get<0>(muchie) == tata[curr] && get<1>(muchie) == curr; } )[0]);
                curr = tata[curr];
            }
            temp.push(curr);

            fout << "Drum: ";
            while (!temp.empty()) {
                fout << temp.top() << ' ';
                temp.pop();
            }
            fout << "Cost: " << cost;
            fout << '\n';
        }

    return 0;
}
