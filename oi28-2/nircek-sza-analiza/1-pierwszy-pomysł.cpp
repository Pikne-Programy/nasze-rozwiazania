#include <bits/stdc++.h>
using namespace std;
constexpr int limit = 2e3 + 3;
int n, i;
int a, b;
char c;
struct droga
{
    int id;
    int to;
    char what;
};
vector<droga> tree[limit];
bitset<limit> vis;
map<string, bitset<limit>> m;
string o;
bitset<limit> ov;
void _dfs(int v)
{
    vis[v] = 1;
    for (droga u : tree[v])
        if (!vis[u.to])
        {
            o.push_back(u.what);
            ov[u.id] = 1;
            m[o] |= ov;
            _dfs(u.to);
            ov[u.id] = 0;
            o.pop_back();
        }
}
void dfs(int v)
{
    vis.reset();
    o = "";
    ov.reset();
    _dfs(v);
}
set<string> xd;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (i = 1; i < n; ++i)
    {
        cin >> a >> b >> c;
        tree[a].push_back({i, b, c});
        tree[b].push_back({i, a, c});
    }
    for (i = 1; i <= n; ++i)
        dfs(i);
    m[""].set();
    string x;
    size_t nn = 0;
    for (auto e : m)
        if (e.second.count() == n - 1)
        {
            ++nn;
            x += e.first + '\n';
        }
    cout << nn << '\n' << x;
}
