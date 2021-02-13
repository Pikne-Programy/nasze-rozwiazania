#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

constexpr int N = 2e5;
bitset<N + 1> visited;
vector<int> graph[N + 1], preorder, low;
vector<pair<int,int>> bridges;
// set<int> cutpoint;
int n, m, Time, a, b;

void dfs(int v, int root=0)
{
    visited[v] = 1;
    ++Time;
    preorder[v] = Time;
    low[v] = Time;
    // int children = 0;
    for (auto u : graph[v])
    {
        if (u == root)
            continue;
        if (!visited[u])
        {
            dfs(u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] > preorder[v])
                bridges.push_back(make_pair(v, u));     
            // if (low[u] >= preorder[v] && root!=0)
            //     cutpoint.insert(v);
            // children++;
        }
        else
        {
            low[v] = min(low[v], preorder[u]);
        }
    }
    // if (root == 0 && children > 1)
    //     cutpoint.insert(v);
    ++Time;
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
    preorder.assign(n + 1, 0);
    low.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        if (!visited[i])
            dfs(i);
    }
    for (auto b : bridges)
    {
        cout << b.first << ' ' << b.second << ' ';
    }
    // cout << '\n';
    // for (auto c : cutpoint)
    // {
    //     cout << c << ' ';
    // }
}