// Simple program with implementation of topological sort. It prints a topological order of graph given as an adjacency list.
// Time complexity O(V + E).
// Space complexity: linear
// Note: before running toposort make sure that your graph is acyclic.

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

constexpr int N = 1e5;

bitset<N + 1> visited;
vector<int> graph[N + 1], res;
int n, m, a, b;

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
// topological sort
void topological_sort()
{
    res.clear();
    for (int32_t i = 1; i <= n; ++i)
    {
        if (!visited[i])
            dfs(i);
    }
    for (int i = res.size() - 1; i >= 0; --i)
    {
        cout << res[i] << " ";
    }
}
// function to read a graph
// n -> number of verticies
// m -> number of edges
// a, b -> connections between verticies
void read()
{
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b;
        graph[a].push_back(b);
    }
}
int main()
{
    read();
    topological_sort();
}
