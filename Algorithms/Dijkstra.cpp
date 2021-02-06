    #include <bits/stdc++.h>
    #include <ext/pb_ds/assoc_container.hpp>
    using namespace std;
    using namespace __gnu_pbds;

    constexpr int N = 200000;

    int dist[N];
    vector<pair<int,int>> graph[N];
    int n, m, a, b, w;

    void Dijkstra()
    {
        priority_queue<pair<int, int>> q;
        q.push({0,0});
        dist[0]=0;

        while (!q.empty())
        {
            int d_x = -q.top().first;
            int x = q.top().second;
            q.pop();
            if(d_x!=dist[x])
                continue;

            for(auto edge: graph[x])
            {
                int y=edge.first;
                int len=edge.second;
                if(d_x+len < dist[y])
                {
                    dist[y]=d_x+len;
                    q.push({-dist[y],y});
                }
            }
        }
    }

    int main()
    {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);

        cin >> n >> m;

        for (int i = 0; i < m; ++i)
        {
            cin >> a >> b >> w;
            graph[a-1].push_back({b-1,w});
        }

        for (int i = 0; i < n; ++i)
        {
            dist[i] = INT_MAX;
        }

        Dijkstra();
    }
