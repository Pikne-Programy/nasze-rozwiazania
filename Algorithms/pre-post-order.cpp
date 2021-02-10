// Pre- and Postorder traversal of a directed acyclic graph given as an adjacency list.
// Time complexity: O(V + E)
// Space complexity: linear
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

constexpr int N = 2e5;
bitset<N + 1> visited;
vector<int> graph[N + 1], preorder, postorder;
int n, m, Time, a, b;

void read()
{
    // n -> number of verticies, m -> number of edges
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b;
        graph[a].push_back(b);
    }
    preorder.assign(n + 1, 0);
    postorder.assign(n + 1, 0);
}

void dfs(int v)
{
    visited[v] = 1;
    ++Time;
    preorder[v] = Time;
    for (auto u : graph[v])
    {
        if (!visited[u])
            dfs(u);
    }
    ++Time;
    postorder[v] = Time;
}
int main()
{
    read();
    for (int i = 1; i <= n; ++i)
    {
        if (!visited[i])
            dfs(i);
    }
    for(int i = 1; i <= n; ++i)
    {
        cout << i << ": preorder: " << preorder[i] << " postorder: " << postorder[i] << '\n';
    }
}
