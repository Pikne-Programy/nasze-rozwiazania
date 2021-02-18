#include <bits/stdc++.h>
using namespace std;
constexpr int limit = 5e5 + 3;
int n, m;
struct wiazanie
{
    int p; // przyjaciel
    int i; // index
};
struct osoba
{
    vector<wiazanie> p;
    int mniejsze = 0;
    int wieksze = 0;
    bool gotowy = false;
} krasnale[limit];
bitset<limit> faliste, falistosc;
struct query
{
    int p;  // przyjaciel
    bool w; // fala
};
queue<query> q;
int a, b, i;
int wskaznik = 0;
pair<int, int> wiazania[limit];
int lewy, prawy;
int miejsca[limit];
int memory = 0;
bitset<limit> odwiedzone;
bool dfs(int v = 2)
{
    odwiedzone[v] = 1;
    bool r = false;
    for (auto u : krasnale[v].p)
    {
        if (!odwiedzone[u.p])
            if (u.p == 1 || (r = dfs(u.p)))
            {
                r = true;
                break;
            }
    }
    return r;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (i = 0; i < m; ++i)
    {
        cin >> a >> b;
        krasnale[a].p.push_back({b, i});
        krasnale[b].p.push_back({a, i});
        wiazania[i] = {a, b};
    }
    if (dfs())
    {
        //cerr << "JEST POLACZENIE\n";
        miejsca[1] = 1;
        miejsca[2] = n;
        lewy = 1;  // ostatni lewy
        prawy = n; // ostatni prawy
        for (auto p : krasnale[1].p)
        {
            //cerr << "[-] z 1 na " << p.p << endl;
            q.push({p.p, false});
            faliste[p.i] = 1;
            falistosc[p.i] = false ^ p.p == wiazania[p.i].first;
        }
        for (auto p : krasnale[2].p)
        {
            //cerr << "[+] z 2 na " << p.p << endl;
            q.push({p.p, true});
            faliste[p.i] = 1;
            falistosc[p.i] = true ^ p.p == wiazania[p.i].first;
        }
    }
    else
    {
        //cerr << "NIE MA POLACZENIA\n";
        lewy = 0;
        prawy = n + 1;
    }
    while ((!q.empty()) || wskaznik != m)
    {
        while (!q.empty())
        {
            auto query = q.front();
            q.pop();
            if (query.p <= 2)
                continue; //?
            auto &k = krasnale[query.p];
            if (query.w)
                ++k.wieksze;
            else
                ++k.mniejsze;
            //cerr << query.p << ' ' << k.wieksze << ' ' << k.mniejsze << endl;
            if (k.mniejsze > k.p.size() / 2 || k.wieksze > k.p.size() / 2)
            {
                cout << "NIE\n";
                return 0;
            }
            if (!k.gotowy)
            {
                if (k.mniejsze == k.p.size() / 2)
                {
                    miejsca[query.p] = ++lewy;
                    k.gotowy = true;
                    //cerr << "ustawilem " << query.p << " na " << miejsca[query.p] << endl;
                    //k.wieksze = k.mniejsze;
                    for (auto p : k.p)
                    {
                        if (!faliste[p.i])
                        {
                            //cerr << "[-] z " << query.p << " na " << p.p << endl;
                            ++k.wieksze;
                            q.push({p.p, false});
                            faliste[p.i] = 1;
                            falistosc[p.i] = false ^ p.p == wiazania[p.i].first;
                        }
                    }
                }
                else if (k.wieksze == k.p.size() / 2)
                {
                    miejsca[query.p] = --prawy;
                    k.gotowy = true;
                    //cerr << "ustawilem " << query.p << " na " << miejsca[query.p] << endl;
                    //k.mniejsze = k.wieksze;
                    for (auto p : k.p)
                    {
                        if (!faliste[p.i])
                        {
                            //cerr << "[+] z " << query.p << " na " << p.p << endl;
                            ++k.mniejsze;
                            q.push({p.p, true});
                            faliste[p.i] = 1;
                            falistosc[p.i] = true ^ p.p == wiazania[p.i].first;
                        }
                    }
                }
            }
        }
        while (wskaznik != m && faliste[wskaznik])
            ++wskaznik;
        if (wskaznik != m)
        {
            // losowy

            //cerr << "[+] randomowy z " << wiazania[wskaznik].first << " na " << wiazania[wskaznik].second << endl;
            ++krasnale[wiazania[wskaznik].first].wieksze;
            //cerr << "byl " << wiazania[wskaznik].first << ' ';
            //cerr << krasnale[wiazania[wskaznik].first].wieksze << ' ';
            //cerr << krasnale[wiazania[wskaznik].first].mniejsze << endl;
            q.push({wiazania[wskaznik].second, true});
            faliste[wskaznik] = 1;
            falistosc[wskaznik] = true ^ true;
        }
    }
    /*//cerr << "Sprawdzam falistosci...\n";
    for(i = 0; i < m; ++i) {
        //cerr << wiazania[i].first << ' ' <<wiazania[i].second << ' ' << falistosc[i] << endl;
        //cerr << miejsca[wiazania[i].first]<< miejsca[wiazania[i].second] << endl;
        if((miejsca[wiazania[i].first] > miejsca[wiazania[i].second]) ^ falistosc[i])
            //cerr << "NOK\n";
    }*/
    for (i = 3; i <= n; ++i)
    {
        //cerr << i << ' ' << krasnale[i].mniejsze << ' ' << krasnale[i].wieksze << endl;
        auto &k = krasnale[i];
        if (k.mniejsze > k.p.size() / 2 || k.wieksze > k.p.size() / 2)
        {
            cout << "NIE\n";
            return 0;
        }
    }
    cout << "TAK\n";
    for (i = 1; i <= n; ++i)
        if (miejsca[i])
            cout << miejsca[i] << ' ';
        else
            cout << ++lewy << ' ';
}
