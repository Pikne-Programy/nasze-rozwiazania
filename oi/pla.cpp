// Zadanie Drogi rowerowe XV POI I etap
// Rozwiązanie wzorcowe 100 / 100
// Złożoność czasowa O(n)
// Autor: Michał Szymocha

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, h, x, res = 0;
    stack<int> s;
    s.push(0);
    cin >> n;
    while (n--)
    {
        cin >> x >> h;
        while (s.size() && h < s.top())
            s.pop();
        if (s.size() == 0 || s.top() < h)
        {
            ++res;
            s.push(h);
        }
    }
    cout << res << '\n';
}
