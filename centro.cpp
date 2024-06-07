#include <bits/stdc++.h>
#define nl endl
#define pb push_back
#define pi pair<int, int>
#define st first
#define nd second
using namespace std;
const int maxn = 1e5+5;
vector<int> odleglosci(maxn);
vector <pair<int, int>> g[maxn];
int n;
int centroid = -1;
bool is_off[maxn];

int sz[maxn];
int parent[maxn];

void dfs(int v, int p) {
    sz[v] = 1;
    parent[v] = p;
    for (auto node : g[v]) {
        if (node.st == p || is_off[node.st]) continue;
        dfs(node.st, v);
        sz[v] += sz[node.first];
    }
}



int findCentroid(int v, int tree_size) {
    for (auto node : g[v]) {
        if (is_off[node.first]) continue;
        if (node.first == parent[v]) {
            if (tree_size - sz[v] > ((tree_size+1)/2)) return findCentroid(parent[v], tree_size);
        }
        else {
            if (sz[node.first] > ((tree_size+1)/2)) return findCentroid(node.first, tree_size);
        }
    }
    return v;
}
            

void centroid_decomposition(int v, int rozmiar) {
    if (rozmiar == 1) return;
    dfs(v, 0);
    centroid = findCentroid(v, rozmiar);
    cout << centroid << nl;
    //centroid zostal znaleziony i mozna juz liczyc wynik
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    // for (int i = 0; i < n; i++) {
    //     int l;
    //     cin >> l;
    //     odleglosci[i+1] = l;
    // }
    for (int i = 0; i < n-1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].pb({b, c});
        g[b].pb({a, c});
    }
    centroid_decomposition(1, n);
}
