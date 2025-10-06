#include <bits/stdc++.h>
using namespace std;

// 从start开始spfa，检测负环
template <typename T>
bool SPFA(int n, const vector<vector<pair<int, T>>>& g, vector<T>& dist,
          int start= 0) {
    vector<bool> inQueue(n + 1, false);
    vector<int> times(n + 1, 0);

    queue<int> q;
    dist.assign(n + 1, numeric_limits<T>::max());

    q.push(start);
    inQueue[start]= true;
    dist[start]= 0;
    times[start]= 1;

    while (!q.empty()) {
        int cur= q.front();
        q.pop();
        inQueue[cur]= false;

        for (auto [nxt, w] : g[cur]) {
            if (dist[cur] + w < dist[nxt]) {
                dist[nxt]= dist[cur] + w;
                if (!inQueue[nxt]) {
                    q.push(nxt);
                    inQueue[nxt]= true;
                    times[nxt]++;
                    if (times[nxt] > n) return true;  // negative cycle detected
                }
            }
        }
    }
    return false;
}