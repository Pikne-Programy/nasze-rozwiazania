#include <bits/stdc++.h>
using namespace std;

int constexpr N = 320;

int n, k;
int a, l, d;

vector<int> wyniki;
vector<priority_queue<int>> poczatki[N], konce[N]; // [d][mod]
vector<int> aktywne[N];                            // [d][mod]

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    wyniki.assign(n + 1, 0);

    for (int i = 1; i < N; ++i)
    {
        poczatki[i].resize(i);
        konce[i].resize(i);
        aktywne[i].assign(i, 0);
    }

    for (int i = 0; i < k; ++i)
    {
        cin >> a >> l >> d;
        if (l < N)
        {
            for (int j = 0; j < l; ++j)
                wyniki[a + j * d]++;
        }
        else
        {
            poczatki[d][a % d].push(-a);
            konce[d][a % d].push(-(a + (l - 1) * d));
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j < N; ++j)
        {
            while (!poczatki[j][i % j].empty() && -poczatki[j][i % j].top() <= i)
            {
                aktywne[j][i % j]++;
                poczatki[j][i % j].pop();
            }
            while (!konce[j][i % j].empty() && -konce[j][i % j].top() < i)
            {
                aktywne[j][i % j]--;
                konce[j][i % j].pop();
            }
            wyniki[i] += aktywne[j][i % j];
        }
        cout << wyniki[i] << ' ';
    }
}
