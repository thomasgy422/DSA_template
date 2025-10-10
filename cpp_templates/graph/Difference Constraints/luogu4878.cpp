#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second

#define present(c, x) ((c).find(x) != (c).end())
#define cpresent(c, x) (find(all(c), x) != (c).end())
#define sz(a) int((a).size())

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long i64;
typedef __int128_t i128;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;
typedef double ld;

// https://www.luogu.com.cn/problem/P4878
// spfa从0跑可以看是否有负环，0作为超级远点
// 而从1跑可以算出1和n的最大距离（满足所有条件的最大上界，本质是最短路）
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, ml, md, a, b, d;
    cin >> n >> ml >> md;

    vector<vector<ii>> g(n + 1);

    for (int i= 2; i <= n; i++) {
        g[i].pb({i - 1, 0});
    }

    for (int i= 1; i <= ml; i++) {
        cin >> a >> b >> d;
        // b - a <= d
        g[a].pb({b, d});
    }

    for (int i= 1; i <= md; i++) {
        cin >> a >> b >> d;
        // b - a >= d
        g[b].pb({a, -d});
    }

    for (int i= 1; i <= n; i++) {
        g[0].pb({i, 0});
    }

    auto spfa= [&](int i) -> int {
        vi times(n + 1, 0);
        vi value(n + 1, INT_MAX);
        queue<int> q;
        vector<bool> enter(n + 1, false);
        enter[i]= true;
        times[i]= 1;
        value[i]= 0;
        q.push(i);
        int nxt, w;
        bool f= true;
        while (!q.empty()) {
            if (!f) break;
            int cur= q.front();
            q.pop();
            enter[cur]= false;
            for (auto e : g[cur]) {
                nxt= e.fi;
                w= e.se;
                if (value[cur] + w < value[nxt]) {
                    value[nxt]= value[cur] + w;
                    times[nxt]++;
                    if (times[nxt] > n) {
                        f= false;
                        break;
                    }
                    enter[nxt]= true;
                    q.push(nxt);
                }
            }
        }

        if (!f) {
            return -1;
        }
        if (value[n] == INT_MAX) return -2;
        return value[n] - value[1];
    };

    int ans= spfa(0);
    if (ans == -1) {
        cout << -1 << endl;
    } else {
        ans= spfa(1);
        cout << ans << endl;
    }
}
