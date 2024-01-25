// * Algoritm de clustering folosind distanta Levenstein folosind Disjoint Set
// * Complexitate O(|cuv1| * |cuv2|)

#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <iostream>

using namespace std;

ifstream fin("cuvinte.in");

struct DisjointSet
{
    vector<int> parent;
    vector<int> rank;
    unordered_set<int> cluster_nr;
    unordered_map<int, unordered_set<int>> cluster;

    DisjointSet(int n) : parent(n), rank(n, 1), cluster_nr(n), cluster(n) {
        iota(parent.begin(), parent.end(), 0);
        for (int i = 0; i < n; i++){
            cluster_nr.insert(i);
            cluster[i].insert(i);
        }
    }

    int find(int& a) {
        return this->parent[a] == a ? a : this->parent[a] = this->find(this->parent[a]);
    }

    void _union(int& a, int& b) {
        auto helper = [this](int a, int b) {
            this->parent[b] = a;
            this->rank[a] += (this->rank[b] = a);
            this->cluster[a].merge(this->cluster[b]);
            this->rank[b] = 0;
            this->cluster_nr.erase(this->cluster_nr.find(b));
        };
        
        int pa = this->find(a), pb = this->find(b);
        
        if (pa == pb)
            return;

        this->rank[pa] > this->rank[pb] ? helper(pa, pb) : helper(pb, pa);
    }
};

int levenshtein_distance(string word1, string word2) {
    int word1_len = word1.length(), word2_len = word2.length();
    int d[word1_len + 1][word2_len + 1], i, j;

    d[0][0] = 0;
    for (i = 1; i < min(word1_len, word2_len) + 1; i++)
        d[i][0] = d[0][i] = i;
    for (; i < word1_len + 1; i++)
        d[i][0] = i;
    for (; i < word2_len + 1; i++)
        d[0][i] = i;
    for (i = 1; i < word1_len + 1; i++)
        for (j = 1; j < word2_len + 1; j++)
            d[i][j] = word1[i - 1] != word2[j - 1] ? 1 + min({d[i - 1][j], d[i][j - 1], d[i - 1][j - 1]}) : d[i - 1][j - 1];

    return d[i - 1][j - 1];
}

int main() {
    vector<string> words;
    string word;
    while (fin >> word)
        words.push_back(word);

    int k = cin.get() - '0', words_len = words.size();
    DisjointSet ds(words_len);

    for (int l = 0; l < words_len - k; l++){
        pair<int, int> imin;
        int min = -1;

        for (int i = 0; i < words_len; i++)
            for (int j = 0; j < words_len; j++)
                if (i != j && ds.find(i) != ds.find(j)) {
                    int x = levenshtein_distance(words[i], words[j]);
                    if (min == -1 || x < min){
                        min = x;
                        imin = make_pair(i, j);
                    }
                }

        ds._union(imin.first, imin.second);
    }

    for (int x : ds.cluster_nr) {
        cout << x << ": ";
        for (int y : ds.cluster[x])
            cout << words[y] << ' ';
        cout << '\n';
    }

    int min = -1;
    for (int i = 0; i < words_len; i++)
        for (int j = 0; j < words_len; j++)
            if (i != j && ds.find(i) != ds.find(j)) {
                int x = levenshtein_distance(words[i], words[j]);
                if (min == -1 || x < min)
                    min = x;
            }
    
    cout << min;

    return 0;
}
