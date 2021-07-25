// Zadanie Temperatura XVIII POI II etap dzień drugi
// Rozwiązanie alternatywne z zastosowaniem drzewa przedziałowego 100 / 100
// Złożoność czasowa O(n*log(n))
// Autor: Michał Szymocha

#include <bits/stdc++.h>
using namespace std;
int n, maks, pocz;
vector<pair<int, int>> A;
constexpr int base = 1 << 20;
vector<int> tree(base << 1, INT_MIN);

void build()
{
    int n = A.size();
    for (int i = 0; i < n; ++i)
        tree[base + i] = A[i].first;

    for (int i = base - 1; i > 0; --i)
        tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
}

int query(int l, int r)
{
    int res = INT_MIN;
    l += base - 1;
    r += base + 1;
    while (r - l > 1)
    {
        if (!(l & 1))
            res = max(res, tree[l + 1]);
        if (r & 1)
            res = max(res, tree[r - 1]);
        l >>= 1;
        r >>= 1;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    A.resize(n);
    for (auto &p : A)
        cin >> p.first >> p.second;
    build();
    int res = 1, j = 0;
    for (int i = 0; i < n; ++i)
    {
        maks = query(i, j);
        while (j < n && maks <= A[j].second)
        {
            maks = max(maks, query(i, j));
            ++j;
            res = max(res, j - i);
        }
    }
    cout << res << '\n';
}
