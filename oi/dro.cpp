// Zadanie Drogi rowerowe XXV POI II etap dzień pierwszy
// Rozwiązanie wzorcowe 100 / 100
// Złożoność czasowa O(n + m)
// Autor: Michał Szymocha, Marcin Wykpis

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

constexpr int N = 1e5;

int n, m, color, a, b;
bitset<N + 1> visited;
vector<int> graph[N + 1], reversed_order[N + 1], new_graph[N + 1], new_reversed[N + 1];
vector<int> SCC, res, SCCsize, dp;

void dfs(int v)
{
    visited[v] = 1;
    for (auto u : graph[v])
    {
        if (!visited[u])
        {
            dfs(u);
        }
    }
    res.push_back(v);
}

void dfs2(int v)
{
    visited[v] = 1;
    for (auto u : new_graph[v])
    {
        if (!visited[u])
        {
            dfs2(u);
        }
    }
    res.push_back(v);
}

void scc(int v, int color)
{
    SCC[v] = color;
    for (auto u : reversed_order[v])
    {
        if (!SCC[u])
            scc(u, color);
    }
}

void topological_sort()
{
    visited = 0;
    res.clear();
    for (int i = 1; i <= n; ++i)
    {
        if (!visited[i])
        {
            dfs2(i);
        }
    }
}
void read()
{
    cin >> n >> m;
    SCC.assign(n + 1, 0);
    SCCsize.assign(n + 1, 0);
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b;
        graph[a].push_back(b);
        reversed_order[b].push_back(a);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    for (int i = 1; i <= n; ++i)
    {
        if (!visited[i])
            dfs(i);
    }
    for (int i = res.size() - 1; i >= 0; --i)
    {
        if (SCC[res[i]] == 0)
        {
            scc(res[i], ++color);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        ++SCCsize[SCC[i]];
        for (auto v : graph[i])
            if (SCC[v] != SCC[i])
                new_graph[SCC[i]].push_back(SCC[v]);
    }
    topological_sort();
    dp.assign(n + 1, 0);
    for (int i = 0; i < res.size(); ++i)
    {
        int u = res[i];
        dp[u] += SCCsize[u];
        for (auto v : new_graph[u])
        {
            dp[u] += dp[v];
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        cout << dp[SCC[i]] - 1 << '\n';
    }
}
