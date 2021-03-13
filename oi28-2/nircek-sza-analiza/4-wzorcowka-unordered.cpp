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
unordered_map<string, bitset<limit>> m;
string o;
bitset<limit> ov;
set<char> app;
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
    vis[v] = 1;
    for (droga u : tree[v])
        if (app.count(u.what))
        {
            o.push_back(u.what);
            ov[u.id] = 1;
            m[o] |= ov;
            _dfs(u.to);
            ov[u.id] = 0;
            o.pop_back();
        }
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
        if (tree[i].size() == 1)
            app.insert(tree[i][0].what);
    if (app.size() > 2)
    {
        cout << "0\n";
        return 0;
    }
    for (i = 1; i <= n; ++i)
        dfs(i);
    m[""].set();
    for (auto e : m)
        if (e.second.count() == n - 1)
        {
            xd.insert(e.first);
            xd.insert(string(e.first.rbegin(), e.first.rend()));
        }
    cout << xd.size() << '\n';
    for (auto e : xd)
        cout << e << '\n';
}