#include <fstream>
#include <vector>
#include <optional>
#include <stack>

#include <iostream>

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
        d[x][y] = d[y][x] = z;
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

    int raza = INF;
    int diametru = 0;
    int centrul = -1;

    for (int i = 1; i <= n; i++) {
        int excentricitate = 0;
        for (int j = 1; j <= n; j++) {
            if (d[i][j] == INF) continue;
            excentricitate = max(excentricitate, d[i][j]);
        }

        if (excentricitate > 0 && excentricitate < raza) {
            raza = excentricitate;
            centrul = i;
        }

        diametru = max(diametru, excentricitate);
    }

    fout << "Raza: " << raza << '\n';
    fout << "Centrul: " << centrul << '\n';
    fout << "Diametrul: " << diametru << '\n';
    fout << "Lant diametral: ";

    int u, v;
    for (u = 1; u <= n; ++u) {
        for (v = 1; v <= n; ++v) {
            if (d[u][v] == diametru) {
                break;
            }
        }
        if (v <= n) {
            break;
        }
    }

    stack<int> lantDiametral;
    while (v != u) {
        lantDiametral.push(v);
        v = p[u][v];
    }
    lantDiametral.push(u);

    while (!lantDiametral.empty()) {
        fout << lantDiametral.top() << ' ';
        lantDiametral.pop();
    }

    return 0;
}
