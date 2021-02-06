#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

constexpr long long base = 1 << 17;
vector<int> tree(base << 1, 0);

bool z;
long long q, a, b, c;

void update(long long l, long long r, long long x)
{
    l += base - 1;
    r += base + 1;
    while (r - l > 1)
    {
        if (!(l & 1))
        {
            tree[l + 1] += x;
        }
        if (r & 1)
        {
            tree[r - 1] += x;
        }
        l >>= 1;
        r >>= 1;
    }
}

int querry(long long v)
{
    long long result = 0;
    v += base;
    while (v)
    {
        result += tree[v];
        v >>= 1;
    }
    return result;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> q;
    while (q--)
    {
        cin >> z;
        if (!z)
        {
            cin >> a >> b >> c;
            update(a, b, c);
        }
        else
        {
            cin >> a;
            cout << querry(a) << '\n';
        }
    }
}
