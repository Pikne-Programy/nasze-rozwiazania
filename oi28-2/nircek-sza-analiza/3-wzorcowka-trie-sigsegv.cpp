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
class trie
{
    struct _trie
    {
        _trie *parent = nullptr;
        bitset<limit> x;
        _trie *t[26];
    } * root, *c;
    string s;

public:
    set<string> w;
    trie()
    {
        c = root = new _trie;
    }
    void reset()
    {
        c = root;
        s = "";
    }
    void up()
    {
        c = c->parent;
        s.pop_back();
    }
    void down(char x)
    {
        if (c->t[x - 'A'] == nullptr)
        {
            c->t[x - 'A'] = new _trie;
            c->t[x - 'A']->parent = c;
        }
        c = c->t[x - 'A'];
        s.push_back(x);
    }
    void add(bitset<limit> x)
    {
        c->x |= x;
        if (c->x.count() == n - 1)
            w.insert(s);
    }

} trie;
vector<droga> tree[limit];
bitset<limit> vis;
bitset<limit> ov;
set<char> app;
void _dfs(int v)
{
    vis[v] = 1;
    for (droga u : tree[v])
    {
        if (!vis[u.to])
        {
            trie.down(u.what);
            ov[u.id] = 1;
            trie.add(ov);
            _dfs(u.to);
            ov[u.id] = 0;
            trie.up();
        }
    }
}
void dfs(int v)
{
    vis.reset();
    ov.reset();
    trie.reset();
    vis[v] = 1;
    for (droga u : tree[v])
        if (app.count(u.what))
        {
            trie.down(u.what);
            ov[u.id] = 1;
            trie.add(ov);
            _dfs(u.to);
            ov[u.id] = 0;
            trie.up();
        }
}
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
    for (auto e : trie.w)
        trie.w.insert(string(e.rbegin(), e.rend()));
    cout << trie.w.size() << '\n';
    for (auto e : trie.w)
        cout << e << '\n';
}
