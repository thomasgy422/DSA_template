#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second

#define present(c, x) ((c).find(x) != (c).end())
#define cpresent(c, x) (find(all(c), x) != (c).end())
#define sz(a) int((a).size())

using namespace std;

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

// https://www.luogu.com.cn/problem/P4926
// 限制超级源点，用来加入确定的值
// a >= (k - limit) * b 可以转化为log(b) <= -log(k - limit) + log(a)
// 但同时要注意确定的值也要取log

ld sml= 1e-6;
ld mx= 1e12;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s, t;
    int o, a, b, k;
    int mk= 11;
    ld v;

    cin >> n >> s >> t;
    vvi lst;
    vvi fix;
    for (int i= 1; i <= s; i++) {
        cin >> o >> a >> b >> k;
        lst.pb({o, a, b, k});
        mk= min(mk, k);
    }

    for (int i= 1; i <= t; i++) {
        cin >> a >> k;
        fix.pb({a, k});
    }

    auto check= [&](ld mid) -> bool {
        queue<int> q;
        vector<ld> dis(n + 2, mx);
        vector<vector<pid>> g(n + 2);
        vector<bool> enter(n + 2, false);
        vi times(n + 2, 0);
        for (auto e : lst) {
            if (e[0] == 1) {
                g[e[1]].pb({e[2], -log2(e[3] - mid)});
            } else {
                g[e[1]].pb({e[2], log2(e[3] + mid - sml)});
            }
        }

        for (auto e : fix) {
            g[e[0]].pb({n + 1, -log2(e[1])});
            g[n + 1].pb({e[0], log2(e[1])});
        }

        for (int i= 1; i <= n + 1; i++) {
            g[0].pb({i, 0});
        }

        q.push(0);
        enter[0]= true;
        dis[0]= 0;
        times[0]= 1;

        while (!q.empty()) {
            int cur= q.front();
            q.pop();
            enter[cur]= false;
            for (auto e : g[cur]) {
                int nxt= e.fi;
                if (dis[cur] + e.se < dis[nxt]) {
                    dis[nxt]= dis[cur] + e.se;
                    if (!enter[nxt]) {
                        q.push(nxt);
                        enter[nxt]= true;
                        times[nxt]++;
                        if (times[nxt] > n + 1) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    };

    ld ans= -1;
    ld left= sml, right= mx;

    while (left + sml <= right) {
        ld mid= (left + right) / 2;
        if (check(mid)) {
            ans= mid;
            left= mid + sml;
        } else {
            right= mid - sml;
        }
    }

    cout << ans << endl;
}
/*
    a >= (k - limit) * b

    kb <= a
    b / a <= 1 / (k - limit)
    log(b) <= -log(k - limit) + log(a)
    log(b) <= log(k + limit - sml) + log(a)

    a >= 1 + b
    a <= 1 + b
    b <= a - 1
    a <= b + 1

*/
