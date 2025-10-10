#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second

#define present(c, x) ((c).find(x) != (c).end())
#define cpresent(c, x) (find(all(c), x) != (c).end())
#define sz(a) int((a).size())

typedef long long i64;
typedef double ld;
typedef __int128_t i128;
typedef pair<int, int> ii;
typedef pair<int, ld> pid;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;

template <typename T>
void dijkstra(int n, const vector<vector<pair<int, T>>> &graph, vector<T> &dist, int src) {
    using P = pair<T, int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    dist.assign(n, numeric_limits<T>::max());
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : graph[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
}

// https://www.luogu.com.cn/problem/P2662
// 若出现某个dist为inf，则表示有mod余数无法到达
// dist[i]表示最小的可以到达余i的数
// 若要找最大的无法到达的数可以找dist[i] - x的最大值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, mx = 0;
    cin >> n >> m;

    vi lst(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> lst[i];
        mx = max(mx, lst[i]);
    }

    vector<bool> vis(mx + 1, false);
    int mn = INT_MAX;
    for(int i = 1; i <=n; i++) {
        for (int j = 0; j <= m; j++) {
            if (lst[i] - j > 0) {
                vis[lst[i] - j] = true;
                mn = min(mn, lst[i] - j);
            }
        }
    }

    if(vis[1]) {
        cout << -1 << endl;
        return 0;
    }

    vector<vector<ii>> g(mn);
    for (int i = 0; i < mn; i++) {
        for(int j = mn + 1; j <= mx; j++) {
            if (vis[j]) {
                g[i].pb({(i + j) % mn, j});
            }
        }
    }
    
    vi dist;
    dijkstra(mn, g, dist, 0);
    int ans = -1;
    for(int i = 0; i < mn; i++) {
        if (dist[i] == INT_MAX) {
            cout << -1 << endl;
            return 0;
        } else {
            ans = max(ans, dist[i] - mn);
        }
    }

    cout << ans << endl;
}

/*

*/