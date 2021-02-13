#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e5;
bitset<N> visited;
vector<int> graph[N], dist, parent;
queue<int> q;
int n, m, a, b;

void bfs(int r)
{
    visited[r] = 1;
    q.push(r);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (auto u : graph[v])
        {
            if (!visited[u])
            {
                q.push(u);
                visited[u] = 1;
                dist[u] = dist[v] + 1;
                parent[u] = v;
            }
        }
    }
}

int main()
{
    // n -> number of verticies, m -> number of edges
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    parent.assign(n + 1, 0);
    dist.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        if (!visited[i])
            bfs(i);
    }
    for (int i = 1; i <= n; ++i)
    {
        cout << dist[i] << ' ' << parent[i] << endl;
    }
}
