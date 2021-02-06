#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

constexpr int N = 100000;
vector<int> parent;
vector<int> size;

char c;
int q, a, b;

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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    parent.resize(N);
    size.resize(N);
    cin >> q;
    while (q--)
    {
        cin >> c;
        switch (c)
        {
        case 'M':
            cin >> a;
            make_s(a);
            break;
        case 'F':
            cin >> a;
            cout << find_s(a) << '\n';
            break;
        case 'U':
            cin >> a >> b;
            union_s(a, b);
        }
    }
}