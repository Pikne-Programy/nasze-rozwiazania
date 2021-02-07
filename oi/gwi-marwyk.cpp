#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

long long result;
int n, s, l, r;
int direction, planets_l, planets_r, planet;
vector<int> l_cost, r_cost;
vector<bool> teleportations;
set<int> planetsLeft; 
priority_queue<pair<int, int>> pq;

int main()
{
    cin >> n >> s;
    l_cost.resize(n-1);
    r_cost.resize(n-1);
    teleportations.resize(n-1);

    planets_l = s - 1;
    planets_r = n - s;

    for (int i = 0; i < n - 1; ++i)
    {
        cin >> l;
        cin >> r;
        l_cost[i] = l;
        r_cost[i] = r;
    }
    for (int i = 1; i <= n; ++i)
    {
        planetsLeft.insert(i);
    }
    for (int i = 0; i < n - 1; ++i)
    {
        l = l_cost[i];
        r = r_cost[i];
        // if all in pq are in the same direction after pushing new element
        if ((direction < 0 && l <= r) || (direction > 0 && l >= r) || direction == 0 || pq.empty())
        {
            // left || right || all 0 || empty
            pq.push({-abs(l - r), i});
            // update direction (to avoid 0 if not all 0)
            if (l != r)
                direction = l - r;

            // left || all 0
            if (direction <= 0 && pq.size() > planets_l)
            {
                // add smalles difference
                result += (long long)r_cost[pq.top().second];
                teleportations[pq.top().second]=1;
                pq.pop();
                // add the rest
                while (!pq.empty())
                {
                    result += (long long)l_cost[pq.top().second];
                    teleportations[pq.top().second] = 0;
                    pq.pop();
                }
                planets_l = n - i - 1;
                planets_r = n - i - 1;
            }
            // right
            else if (direction > 0 && pq.size() > planets_r)
            {
                // add smalles difference
                result += (long long)l_cost[pq.top().second];
                teleportations[pq.top().second]=0;
                pq.pop();
                // add the rest
                while (!pq.empty())
                {
                    result += (long long)r_cost[pq.top().second];
                    teleportations[pq.top().second]=1;
                    pq.pop();
                }
                planets_l = n - i - 1;
                planets_r = n - i - 1;
            }
        }
        //change of direction
        else
        {
            // was right, now left
            if (direction < 0)
            {
                while (!pq.empty())
                {
                    result += (long long)l_cost[pq.top().second];
                    teleportations[pq.top().second]=0;
                    pq.pop();
                }
            }
            // was left, now right
            else
            {
                while (!pq.empty())
                {
                    result += (long long)r_cost[pq.top().second];
                    teleportations[pq.top().second]=1;
                    pq.pop();
                }
            }
            // add element with different direction to pq
            pq.push({-abs(l - r), i});
            planets_l = n - i - 1;
            planets_r = n - i - 1;

            // update direction
            if (l != r)
                direction = l - r;
        }
    }
    // add remaining elements
    if (direction <= 0)
    {
        while (!pq.empty())
        {
            result += (long long)l_cost[pq.top().second];
            teleportations[pq.top().second]=0;
            pq.pop();
        }
    }
    else
    {
        while (!pq.empty())
        {
            result += (long long)r_cost[pq.top().second];
            teleportations[pq.top().second]=1;
            pq.pop();
        }
    }
    cout << result << '\n' << s << ' ';
    for (int i = 0; i < n-2; ++i)
    {
        if (teleportations[i])
        {
            if (teleportations[i+1])
            {
                planet = *++planetsLeft.find(s);
                planetsLeft.erase(s);
            }
            else
            {
                planetsLeft.erase(s);
                planet = *--planetsLeft.end(); 
            }
        }
        else
        {
            if (teleportations[i+1])
            {
                planetsLeft.erase(s);
                planet = *planetsLeft.begin();
            }
            else
            {
                planet = *--planetsLeft.find(s); 
                planetsLeft.erase(s);
            }
        }
        cout << planet << ' ';
        s=planet;
    }
    planetsLeft.erase(s);
    cout << *planetsLeft.begin();
}
