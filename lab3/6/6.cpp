#include <fstream>
#include <vector>
#include <optional>
#include <stack>

#define INF 999999

using namespace std;


ifstream fin("grafpond.in");
ofstream fout("grafpond.out");

vector<tuple<int, int, int>> graph;

int main() {
    int n, m, k, s, x, y, z;
    fin >> n >> m;
    int d[n + 1][n + 1];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            d[i][j] = INF;
    int** p = new int* [n + 1];
    for (int i = 0; i <= n; i++)
        p[i] = new int [n + 1] {0};
    for (int i = 0; i < m; i++) {
        fin >> x >> y >> z;
        d[x][y] = z;
        d[x][x] = d[y][y] = 0;
        p[x][y] = x;
        graph.push_back({x, y, z});
    }

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <=n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = p[k][j];
                }

    for (int i = 1; i <= n; i++)
        if (d[i][i] < 0) {
            fout << "Circuit de cost negativ:\n";

            int start = i, curr = i;
            stack<int> cycle;
            
            do {
                cycle.push(curr);
                curr = p[start][curr];
            } while (curr != start);

            while (!cycle.empty()) {
                fout << cycle.top() << ' ';
                cycle.pop();
            }
            fout << '\n';
            
            return 0;
        }



    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            fout << d[i][j] << ' ';
        fout << '\n';
    }

    return 0;
}
