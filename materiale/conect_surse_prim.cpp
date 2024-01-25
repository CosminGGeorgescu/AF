// * Algoritmul lui Prim pentru arbore partial de cost minim
// * Complexitate O(|V|^2)

#include <fstream>
#include <queue>
#include <cmath>
#include <iomanip>

using namespace std;

ifstream fin("retea2.in");
ofstream fout("retea2.out");

int main() {
    int n, m, x, y;
    fin >> n >> m;
    vector<pair<int, int>> powerhouse(n), building(m);
    vector<double> d(m);
    vector<bool> vis(m, false);
    double s = 0;

    for (int i = 0; i < n; i++) {
        fin >> x >> y;
        powerhouse[i] = {x, y};
    }

    for (int i = 0; i < m; i++) {
        fin >> x >> y;
        building[i] = {x, y};

        double min = 1.79769e+308;
        for (pair<int, int>& pw : powerhouse) {
            double dist = sqrt(pow(x - pw.first, 2) + pow(y - pw.second, 2));
            if (dist < min)
                min = dist;
        }
        d[i] = min;
    }

    for (int i = 0; i < m; i++) {
        pair<int, double> bmin = {-1, 1.79769e+308};

        for (int j = 0; j < m; j++)
            if (!vis[j] && d[j] < bmin.second)
                bmin = {j, d[j]};
        
        vis[bmin.first] = true;
        s += bmin.second;

        for (int j = 0; j < m; j++)
            d[j] = min(d[j], sqrt(pow(building[bmin.first].first - building[j].first, 2) + pow(building[bmin.first].second - building[j].second, 2)));
    }

    fout <<  setprecision(6) << fixed << s;

    return 0;
}
