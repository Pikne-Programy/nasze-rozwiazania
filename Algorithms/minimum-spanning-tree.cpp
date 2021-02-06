#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

struct Edge
{
    int u, v, weight;
    bool operator<(Edge const &other)
    {
        return weight < other.weight;
    }
};

constexpr int N = 100000;
vector<int> parent(N, -1);
vector<int> size(N, 1);
vector<Edge> edges;
vector<Edge> result;

int n, u, v, w, cost;
Edge e;

void make_s(int v)
{
    parent[v] = v;
    size[v] = 1;
}

int find_s(int v)
{
    if (v == parent[v])
        return v;
    parent[v] = find_s(parent[v]);
    return parent[v];
}

void union_s(int a, int b)
{
    a = find_s(a);
    b = find_s(b);
    if (a != b)
    {
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}

int main()
{
    parent.resize(N);
    size.resize(N);
    for (int i = 0; i < N; ++i)
        make_s(i);
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> u >> v >> w;
        e.u = u;
        e.v = v;
        e.weight = w;
        edges.push_back(e);
    }
    sort(edges.begin(), edges.end());
    for (Edge e : edges)
    {
        if (find_s(e.u) != find_s(e.v))
        {
            cost += e.weight;
            result.push_back(e);
            union_s(e.u, e.v);
        }
    }
    cout << cost << '\n';
}
