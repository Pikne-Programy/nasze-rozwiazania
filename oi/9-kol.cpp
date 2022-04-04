#include <bits/stdc++.h>
using namespace std;

constexpr int base = 1<<16;
int tree[2*base];
int tree2[2*base];

int tree_a, tree_b, tree_c;
inline void add(int v, int L, int R) {
    if(tree_b < L || R < tree_a) return;
    if(tree_a <= L && R <= tree_b) {
        tree[v] += tree_c, tree2[v] += tree_c;
        return;
    }
    int l = 2*v, r = 2*v+1, mid = (L+R)/2;
    tree[l] += tree2[v], tree[r] += tree2[v];
    tree2[l] += tree2[v], tree2[r] += tree2[v];
    tree2[v] = 0;

    add(l, L, mid);
    add(r, mid+1, R);

    tree[v] = max(tree[l], tree[r]);
}
inline int query(int v, int L, int R) {
    if(tree_b < L || R < tree_a) return INT_MIN;
    if(tree_a <= L && R <= tree_b) {
        return tree[v];
    }

    int l = 2*v, r = 2*v+1, mid = (L+R)/2;
    tree[l] += tree2[v], tree[r] += tree2[v];
    tree2[l] += tree2[v], tree2[r] += tree2[v];
    tree2[v] = 0;

    return max(query(l, L, mid), query(r, mid+1, R));
}

int n, m, z, a, b, c;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> z;
    while(z--) {
        cin >> a >> b >> c;
        a -= 1, b -= 2; // kraw -> wierzch
        tree_a = a, tree_b = b;
        if(query(1, 0, base-1)+c<=m) {
            cout << "T\n";
            tree_a = a, tree_b = b, tree_c = c;
            add(1, 0, base-1);
        } else cout << "N\n";
    }
}
