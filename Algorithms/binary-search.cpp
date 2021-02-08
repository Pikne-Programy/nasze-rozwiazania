#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

vector<int> v;
set<int> s;

int lower_bound(set<int>::iterator begin, set<int>::iterator end, int val, bool greater = true)
{
    set<int>::iterator it;
    int L = 0;
    int R = distance(begin, end);
    int m;
    if (greater)
    {
        while (L < R)
        {
            m = (L + R) >> 1;
            it = begin;
            advance(it, m);
            if (*it < val)
                L = m + 1;
            else
                R = m;
        }
        return L;
    }
    else
    {
        while (L < R)
        {
            m = (L + R) >> 1;
            it = begin;
            advance(it, m);
            if (*it > val)
                R = m;
            else
                L = m + 1;
        }
        return R - 1;
    }
}

int lower_bound(vector<int>::iterator begin, vector<int>::iterator end, int val, bool greater = true)
{
    int L = 0;
    int R = end - begin;
    int m;
    if (greater)
    {
        while (L < R)
        {
            m = (L + R) >> 1;
            if (*(begin + m) < val)
                L = m + 1;
            else
                R = m;
        }
        return L;
    }
    else
    {
        while (L < R)
        {
            m = (L + R) >> 1;
            if (*(begin + m) > val)
                R = m;
            else
                L = m + 1;
        }
        return R - 1;
    }
}

int upper_bound(set<int>::iterator begin, set<int>::iterator end, int val, bool greater = true)
{
    set<int>::iterator it;
    int L = 0;
    int R = distance(begin, end);
    int m;
    if (greater)
    {
        while (L < R)
        {
            m = (L + R) >> 1;
            it = begin;
            advance(it, m);
            if (*it <= val)
                L = m + 1;
            else
                R = m;
        }
        return L;
    }
    else
    {
        while (L < R)
        {
            m = (L + R) >> 1;
            it = begin;
            advance(it, m);
            if (*it >= val)
                R = m;
            else
                L = m + 1;
        }
        return R - 1;
    }
}

int upper_bound(vector<int>::iterator begin, vector<int>::iterator end, int val, bool greater = true)
{
    int L = 0;
    int R = end - begin;
    int m;
    if (greater)
    {
        while (L < R)
        {
            m = (L + R) >> 1;
            if (*(begin + m) <= val)
                L = m + 1;
            else
                R = m;
        }
        return L;
    }
    else
    {
        while (L < R)
        {
            m = (L + R) >> 1;
            if (*(begin + m) >= val)
                R = m;
            else
                L = m + 1;
        }
        return R - 1;
    }
}

int main()
{
    int val;
    cin >> val;
    s = {0, 1, 3, 3, 4};
    v = {0, 1, 3, 3, 4};
    cout << "lower_bound for set (>=): "  << lower_bound(s.begin(), s.end(), val) << '\n';
    cout << "lower_bound for set (<=): " << lower_bound(s.begin(), s.end(), val, false) << '\n';
    cout << "lower_bound for vector (>=): " << lower_bound(v.begin(), v.end(), val) << '\n';
    cout << "lower_bound for vector (<=): " << lower_bound(v.begin(), v.end(), val, false) << '\n';
    cout << "upper_bound for set (>):" << upper_bound(s.begin(), s.end(), val) << '\n';
    cout << "upper_bound for set (<):" << upper_bound(s.begin(), s.end(), val, false) << '\n';
    cout << "upper_bound for vector (>): " << upper_bound(v.begin(), v.end(), val) << '\n';
    cout << "upper_bound for vector (<): " << upper_bound(v.begin(), v.end(), val, false) << '\n';
}
