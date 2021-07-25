// Zadanie Drogi rowerowe XXIV POI I etap
// Rozwiązanie wzorcowe 100 / 100
// Złożoność czasowa O(n)
// Autor: Michał Szymocha

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr ll N = 5e5 + 3;
ll n, x, res, d, a, b;
vector<pair<ll, pair<ll, ll>>> obj;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> x;
    for (int i = 0; i < n; ++i)
    {
        cin >> d >> a >> b;
        obj.push_back({d, {a + 1, b - 1}});
    }
    ll curx = 0, curh = 0, curmin = 0, curmax = 0;
    for (int i = 0; i < n; ++i)
    {
        pair<ll, ll> h = obj[i].second;
        curmax = min(curmax + (obj[i].first - curx), h.second);
        curmin = max(curmin - (obj[i].first - curx), h.first);
        curx = obj[i].first;
        if ((curmax & 1) != (curx & 1))
            --curmax;
        if ((curmin & 1) != (curx & 1))
            ++curmin;
        if (curmin > h.second || curmax < h.first)
        {
            cout << "NIE\n";
            return 0;
        }
    }
    cout << (curx + curmin) / 2 << '\n';
}
