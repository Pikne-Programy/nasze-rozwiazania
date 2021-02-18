/**
 * pomysł był ciekawy, nie wiem czy by to zadziałało na dwóch
 * drzewach, ale jedno drzewo nie przechodziło już czasu dla podzadań
 * 4-6 w SIO, także nie wiem po co to tak "optymalizowałem" jak miałem
 * 38 za darmo... także ostatecznie 0 i rozpaczliwe wrzucenie ostatniego
 * "działającego" blefa, który nawet nie przechodził przykładu z zadania
 * (chociaż gdyby nie 1h i 1i to bym miał 3 punkty)
*/
#include <bits/stdc++.h>
using namespace std;
constexpr int limit = 5e3 + 3;
int n;
int i;
uint64_t wi;

// SRC: https://github.com/Pikne-Programy/nasze-rozwiazania/blob/5b4affff309039c2281aa758a654bf2010c51d35/Algorithms/point-segment.cpp
constexpr long long base = 1 << 20;
vector<pair<uint64_t, size_t>> tree(base << 1, {-1, -1});
bool z;
long long q, a, b, c;
void init()
{
    for (size_t v = base - 1; v != 0; --v)
        tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}
void update(size_t v, uint64_t x)
{
    v += base;
    tree[v] = {x, v - base};
    v >>= 1;
    while (v)
    {
        tree[v] = min(tree[2 * v], tree[2 * v + 1]);
        v >>= 1;
    }
}

pair<uint64_t, size_t> query(size_t l, size_t r)
{
    pair<uint64_t, size_t> result = {-1, -1};
    l += base - 1;
    r += base + 1;
    while (r - l > 1)
    {
        if (!(l & 1))
        {
            result = min(result, tree[l + 1]);
        }
        if (r & 1)
        {
            result = min(result, tree[r - 1]);
        }
        l >>= 1;
        r >>= 1;
    }
    return result;
}

vector<int> tree2(base << 1, 0);
void update2(long long v, long long x)
{
    v += base;
    tree2[v] = x;
    v >>= 1;
    while (v)
    {
        tree2[v] = tree2[2 * v] + tree2[2 * v + 1];
        v >>= 1;
    }
}
int query2(long long l, long long r)
{
    long long result = 0;
    l += base - 1;
    r += base + 1;
    while (r - l > 1)
    {
        if (!(l & 1))
        {
            result += tree2[l + 1];
        }
        if (r & 1)
        {
            result += tree2[r - 1];
        }
        l >>= 1;
        r >>= 1;
    }
    return result;
}

/// ----

set<pair<uint64_t, int>> wset;
uint64_t d;
bitset<limit> wziete;
bool czy_wezmie(uint64_t suma, size_t i)
{

    cerr << "Sprawdzamy czy wezmie z sumą " << suma << " przedmiot " << i << endl;
    auto minimum = query(0, i - 1);
    if(minimum.first == -1) return false;
    auto dotych_suma = query2(0, minimum.second - 1);
    cerr << minimum.first << ':' << minimum.second << ' ' << dotych_suma << endl;
    cerr << suma << ' ' << dotych_suma + minimum.first << endl;
    return suma >= minimum.first - dotych_suma;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (i = 0; i < n; ++i)
    {
        cin >> d;
        tree[i + base] = {d, i};
        wset.insert({d, i});
    }
    init();
    uint64_t suma = 0;
    for (i = 0; i < n; ++i)
    {
        cerr << "-----------------\n";
        auto it = wset.begin();
        while (it != wset.end())
        {
            //sprawdzić dla niższych
            bool good = !czy_wezmie(suma + it->first, it->second);
            if (good)
                for (size_t j = 0; j < it->second; ++j)
                {
                    cerr << "xd " << j << endl;
                    if ((!wziete[j]) && czy_wezmie(suma + it->first, j))
                    {
                        good = false;
                        break;
                    }
                }
            if (!good)
            {
                ++it;
                continue;
            }

            update(it->second, -1);
            suma += it->first;
            cerr << "sumuje też na " << it->second << ": " << it->first << endl;
            update2(it->second, it->first);
            wziete[it->second] = 1;
            auto oit = it++;
            wset.erase(oit);
            cout << suma << ' ';
            break;
        }
    }
}
