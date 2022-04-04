#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graf;
constexpr int base = 1<<18;
int tree[2*base];
vector<int> autostrada; // wierzchołek -> krawędź
vector<int> zaleznedo; // krawędź -> postorder

int indeks=0, depth = 0;
void dfs(int v) {
    autostrada[v] = indeks;
    tree[base+indeks] = depth;
    ++indeks, ++depth;
    for(auto&& u : graf[v]) {
        dfs(u);
    }
    zaleznedo[autostrada[v]] = indeks-1;
    --depth;
}

int n, m, i, a, b;
char c;

inline void _add(int a, int b) {
    a += base-1, b += base+1;
    while(b-a > 1) {
        if(a%2 == 0) // prawy syn pierwotnie
            tree[a+1] -= 1;
        if(b%2 == 1) // lewy syn pierwotnie
            tree[b-1] -= 1;
        a /= 2, b /= 2;
    }
}

inline int _query(int a) {
    int r = 0;
    a += base;
    while(a != 0) {
        r += tree[a];
        a /= 2;
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    graf.resize(n+1);
    autostrada.resize(n+1);
    zaleznedo.resize(n+1);
    for(i = 1; i < n; ++i) {
        cin >> a >> b;
        graf[a].push_back(b);
    }
    dfs(1);
    cin >> m;
    for(i = 0; i < n + m - 1; ++i) {
        cin >> c;
        if(c=='A') {
            cin >> a >> b;
            _add(autostrada[b], zaleznedo[autostrada[b]]);
        } else {
            cin >> a;
            cout << _query(autostrada[a]) << '\n';
        }
    }
}
