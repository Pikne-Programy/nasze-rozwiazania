#include <bits/stdc++.h>

using namespace std;

constexpr int p = 29, mod = 1e9 + 7;
int n, m, a, b;
uint64_t h1, h2;
vector<uint64_t> pot;
vector<uint64_t> pref;
string s;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    pref.assign(n + 1, 0);
    pot.assign(n, 0);
    pot[0] = 1;
    for (int i = 1; i < n; ++i)
    {
        pot[i] = pot[i - 1] * p;
        pot[i] %= mod;
    }
    cin >> s;
    pref[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        pref[i] = pref[i - 1] + (s[i - 1] - 'a' + 1) * pot[i-1];
        pref[i] %= mod;
    }
    cin >> m;
    while (m--)
    {
        cin >> a >> b;
        if (!((a + b) & 1))
        {
            cout << "NIE\n";
            continue;
        }
        h1 = ((pref[(a + b) / 2] - pref[a - 1]+mod) * pot[(b - a + 1) / 2]) % mod;
        h2 = (pref[b] - pref[(a + b) / 2]+mod) % mod;
        if (h1 == h2)
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }
}
