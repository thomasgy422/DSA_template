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

// https://www.luogu.com.cn/problem/P3403
// 找到最小的数，用另外两个数建图
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 h;
    vi64 lst(3);

    cin >> h;
    h--;
    cin >> lst[0] >> lst[1] >> lst[2];
    sort(lst.begin(), lst.end());
    i64 x, y, z, nxt;
    x = lst[0]; y = lst[1]; z = lst[2]; 

    vector<vector<vector<i64>>> g(x);
    for (int i = 0 ; i < x; i++) {
        nxt = (i + y) % x;
        g[i].pb({nxt, y});
        nxt = (i + z) % x;
        g[i].pb({nxt, z});
    }

    vi64 dis(x, LLONG_MAX);
    
    auto dijkstra = [&](vi64 &dis) {
        priority_queue<vi64, vvi64, greater<vi64>> pq;
        dis[0] = 0;
        pq.push({0, 0});
        i64 w, node, nxt;
        while(!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            w = cur[0]; node = cur[1];
            for (auto e : g[node]) {
                nxt = e[0];
                if (dis[nxt] > w + e[1]) {
                    dis[nxt] = w + e[1];
                    pq.push({w + e[1], nxt});
                }
            }
        }
    };

    dijkstra(dis);
    i64 ans = 0;
    for (int i = 0; i < x; i++) {
        if (h >= dis[i]) {
            ans += (h - dis[i]) / x + 1;
        }
    }
    cout << ans << endl;
}
/*
*/