#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

constexpr long long base = 1 << 17;
vector<int> tree(base << 1, 0);

bool z;
long long q, a, b, c;

void update(long long v, long long x)
{
    v += base;
    tree[v] = x;
    v >>= 1;
    while (v)
    {
        tree[v] = tree[2 * v] + tree[2 * v + 1];
        v >>= 1;
    }
}

int querry(long long l, long long r)
{
    long long result = 0;
    l += base - 1;
    r += base + 1;
    while (r - l > 1)
    {
        if (!(l & 1))
        {
            result += tree[l + 1];
        }
        if (r & 1)
        {
            result += tree[r - 1];
        }
        l >>= 1;
        r >>= 1;
    }
    return result;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int q;
    cin >> q;
    bool z;
    long long a, b;
    while (q--)
    {
        cin >> z >> a >> b;
        if (!z)
        {
            update(a, b);
        }
        else
        {
            cout << querry(a, b) << '\n';
        }
    }
}