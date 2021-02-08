#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5;
bitset<N> visited;
vector<int> graph[N];

void dfs(int v)
{
    visited[v] = 1;
    for (auto u : graph[v])
    {
        if (!visited[u])
            dfs(u);
    }
}
int main()
{
    //Your program
}
