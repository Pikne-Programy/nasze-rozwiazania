#include <bits/stdc++.h>
using namespace std;
constexpr int limit = 1e6 + 3;
constexpr int prec = 30 + 1;
int64_t ufrags[limit], frags[limit], // used fragments
    offsets[limit], sizes[limit];
set<pair<int64_t, int64_t>> s; // -_size, _index
int64_t n, z, i, ki;
int64_t X, d, od;
vector<int> k;
set<int> ks;
int64_t _size, _index, whatIcan, whatIneed, offset, p;
map<int64_t, string> buf;
int main()
{
    std::ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> X >> z;
    cin >> d;
    od = d << prec;
    for (i = 1; i < n; ++i)
    {
        cin >> d;
        d <<= prec;
        sizes[i] = d - od;
        s.insert({-sizes[i], i});
        offsets[i] = od;
        ufrags[i] = 0;
        frags[i] = 1;
        //cerr << offsets[i] << '('<<i<< ") ";
        od = d;
    }
    //cerr << od << endl;
    while (z--)
    {
        cin >> ki;
        k.push_back(ki);
        ks.insert(ki);
    }
    i = 0;
    for (auto e : ks)
    {

        while (e != i)
        {
            // dodaj nowe kocyki
            tie(_size, _index) = *s.begin();
            _size = -_size;
            //cerr << "q " << _size << ' ' << _index << endl;
            whatIcan = frags[_index] - ufrags[_index];
            whatIneed = e - i;
            //cerr << "w " << whatIcan << ' ' << whatIneed << endl;
            if (whatIcan <= whatIneed)
            {
                // możemy całe policzyć
                i += whatIcan;
                if (e == i)
                    offset = offsets[_index] + _size * (frags[_index] - 1) + (_size >> 1);
                s.erase(s.begin());
                frags[_index] <<= 1;
                ufrags[_index] = 0;
                s.insert({-(_size >> 1), _index});
            }
            else
            {
                // liczymy tylko część
                i = e;
                ufrags[_index] += whatIneed;
                offset = offsets[_index] + _size * (ufrags[_index] - 1) + (_size >> 1);
            }
        }
        // zapisz
        p = prec;
        while (!(offset & 1) && p != 0)
        {
            offset >>= 1;
            --p;
        }
        buf[i] = to_string(offset) + '/' + to_string(1 << p) + '\n';
    }
    for (auto e : k)
    {
        cout << buf[e];
    }
}
