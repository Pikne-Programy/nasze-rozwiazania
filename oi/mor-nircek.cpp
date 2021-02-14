#include <bits/stdc++.h>

using namespace std;

constexpr int N = 5e3 + 3;
vector<pair<uint16_t, uint16_t>> times[N];
vector<uint16_t> graph[N];
queue<pair<uint16_t, uint16_t>> q;
int n, m, k, a, b, d, timer;

void bfs(int r)
{
    q.push({r, 0});
    //cerr << "----------------------" << r << endl;
    while (!q.empty())
    {
        auto p = q.front();
        int v = p.first;
        int timer = p.second + 1;
        q.pop();

        for (auto u : graph[v])
        {
            if ((!times[r][u].first) && (timer & 1))
            {
                q.push({u, timer});
                times[r][u].first = timer;
                //cerr << u << ' ' <<timer << '\n';
            }
            else if ((!times[r][u].second) && (!(timer & 1)))
            {
                q.push({u, timer});
                times[r][u].second = timer;
                //cerr << u << ' ' <<timer << '\n';
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for (int i = 0; i <= N; ++i)
        times[i].assign(N, {0, 0});
    cin >> n >> m >> k;

    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for (int i = 1; i <= n; ++i)
    {
        bfs(i);
    }

    while (k--)
    {
        cin >> a >> b >> d;
        if (d & 1)
        {
            if (d < times[a][b].first || times[a][b].first == 0)
                cout << "NIE\n";
            else
                cout << "TAK\n";
        }
        else
        {
            if (d < times[a][b].second || times[a][b].second == 0)
                cout << "NIE\n";
            else
                cout << "TAK\n";
        }
    }
}
