#include <bits/stdc++.h>
using namespace std;
int n, X, z;
int64_t d, od;
priority_queue<pair<int64_t, int64_t>> pq; // wielkość, odległość
vector<int> k;
set<int> ks;
map<int, string> buf;
int64_t wielkosc, miejsce;
int p, i;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> X >> z;
    cin >> d;
    od = d << 30;
    for (i = 1; i < n; ++i)
    {
        cin >> d;
        d <<= 30;
        pq.push({d - od, -od});
        //cerr << od << ' ';
        od = d;
    }
    //cerr << endl;
    while (z--)
    {
        cin >> d;
        k.push_back(d);
        ks.insert(d);
    }
    i = 0;
    for (auto e : ks)
    {
        do
        {
            // dodaj nowy kocyk
            tie(wielkosc, miejsce) = pq.top();
            //cerr << 'q' << wielkosc << ' ' << -miejsce << endl;
            pq.pop();
            wielkosc >>= 1; // na połowy
            pq.push({wielkosc, miejsce});
            miejsce -= wielkosc; // dodaję wielkość
            pq.push({wielkosc, miejsce});
            //cerr << wielkosc << endl;
        } while ((++i) != e);
        // zapisz
        miejsce = -miejsce;
        //cerr << miejsce << ' ';
        p = 30;
        while (!(miejsce & 1) && p != 0)
        {
            miejsce >>= 1;
            --p;
        }
        buf[i] = to_string(miejsce) + '/' + to_string(1 << p) + '\n';
    }
    for (auto e : k)
    {
        cout << buf[e];
    }
}
