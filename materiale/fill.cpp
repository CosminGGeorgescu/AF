// * algoritmul de Fill pentru umplerea spatiilor intr-o matrice

#include <iostream>

using namespace std;

unsigned short int n, m;
char building[1000][1000];
int rooms = 0;

void fill(int i, int j) {
    building[i][j] = '#';
    if (i - 1 >= 0 && building[i - 1][j] == '.')
        fill(i - 1, j);
    if (j + 1 < m && building[i][j + 1] == '.')
        fill(i, j + 1);
    if (i + 1 < n && building[i + 1][j] == '.')
        fill(i + 1, j);
    if (j - 1 >= 0 && building[i][j - 1] == '.')
        fill(i, j - 1);
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> building[i][j];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (building[i][j] == '.'){
                rooms++;
                fill(i, j);
            }

    cout << rooms;

    return 0;
}
