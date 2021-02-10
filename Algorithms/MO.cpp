// Program with implementation of MO's algorithm. It gets an array of integers and then answer queries for the sum on a range;
// Time complexity: O((n + q) * sqrt(n))
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

constexpr int N = 2 * 10e5;
int n, q, a, b, w;
vector<pair<int, int>> queries;
vector<int> tab;

bool cmp(pair<int, int> a, pair<int, int> b)
{
    if (a.first != b.first)
        return a.first / w < b.first / w;
    else
        return a.second < b.second;
}
void MO()
{
    int L = 0, R = 0, qL, qR;
    int res = 0;
    for (int i = 0; i < q; ++i)
    {
        qL = queries[i].first;
        qR = queries[i].second;
        while (L < qL)
        {
            res -= tab[L];
            ++L;
        }
        while (L > qL)
        {
            res += tab[L - 1];
            --L;
        }
        while (R <= qR)
        {
            res += tab[R];
            ++R;
        }
        cout << "sum in range " << qL << " " << qR << " = " << res << '\n';
    }
}
int main()
{
    // n -> length of input q -> number of queries
    cin >> n >> q;
    w = sqrt(n);
    tab.assign(n, 0);
    for (int i = 0; i < n; ++i)
    {
        cin >> tab[i];
    }
    for (int i = 0; i < q; ++i)
    {
        cin >> a >> b;
        queries.push_back(make_pair(a, b));
    }
    sort(queries.begin(), queries.end(), cmp);
    MO();
}
