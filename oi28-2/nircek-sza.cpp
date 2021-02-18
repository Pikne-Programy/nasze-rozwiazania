#include <bits/stdc++.h>
using namespace std;
constexpr int limit = 2e3 + 3;
int n, i;
int a, b;
char c;
vector<pair<int, char>> tree[limit];
bitset<limit> vis;
unordered_map<string, bitset<limit>> m;
string o;
bitset<limit> ov;
//int _v;
void _dfs(int v)
{
    vis[v] = 1;
    ov[v] = 1;
    //cerr << _v << "->" << v << ' ' << o << endl;
    m[o] |= ov;
    for (auto u : tree[v])
    {
        if (!vis[u.first])
        {
            o.push_back(u.second);
            _dfs(u.first);
            o.pop_back();
        }
    }
    ov[v] = 0;
}
void dfs(int v)
{
    //_v = v;
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
        tree[a].push_back({b, c});
        tree[b].push_back({a, c});
    }
    for (i = 1; i <= n; ++i)
    {
        dfs(i);
    }
    m[""].set();
    for (auto e : m)
        if (e.second.count() == n)
        {
            xd.insert(e.first);
        }
    cout << xd.size() << '\n';
    for(auto e: xd) {
        cout << e << '\n';
    }
}
