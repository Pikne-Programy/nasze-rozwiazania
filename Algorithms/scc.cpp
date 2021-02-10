// Basic demonstration of algorithm for finding SCC. 
// It gets a graph as an adjacency list and prints SCC's identifier of every vertex;  
// Time complexity: O(V + E)
// Space complexity: linear
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

constexpr int N = 1e5;

int n, m, color, a, b;
bitset<N + 1> visited;
vector<int> graph[N + 1], reversed_order[N + 1];
vector<int> SCC, res;

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

void scc(int v, int color)
{
    SCC[v] = color;
    for (auto u : reversed_order[v])
    {
        if (!SCC[u])
            scc(u, color);
    }
}

// function to read a graph
// n -> number of verticies
// m -> number of edges
// a, b -> connections between verticies
void read()
{
    cin >> n >> m;
    SCC.assign(n + 1, 0);
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b;
        graph[a].push_back(b);
        reversed_order[b].push_back(a);
    }
}

int main()
{
    read();
    for (int i = 1; i <= n; ++i)
    {
        if (!visited[i])
            dfs(i);
    }
    visited = 0;
    for (int i = res.size() - 1; i >= 0; --i)
    {
        if (SCC[res[i]] == 0)
        {
            scc(res[i], ++color);
        }
    }

    for(int i = 1; i <= n; ++i)
    {
        cout << i << " : " << SCC[i] << '\n';
    }
}
