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

// https://www.luogu.com.cn/problem/P1993
// a = b可以转化为 a-b >= 0 和 a-b <= 0
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t, x, y, c;
    cin >> n >> m;

    vector<vector<ii>> g(n + 1);
    vi times(n + 1, 0);
    vi value(n + 1, INT_MAX);

    for (int i= 1; i <= m; i++) {
        cin >> t;
        if (t == 1) {
            cin >> x >> y >> c;
            // x - y >= c
            g[x].pb({y, -c});
        } else if (t == 2) {
            cin >> x >> y >> c;
            // x - y <= c
            g[y].pb({x, c});
        } else {
            // x - y >= 0
            // x - y <= 0
            cin >> x >> y;
            g[y].pb({x, 0});
            g[x].pb({y, 0});
        }
    }

    for (int i= 1; i <= n; i++) {
        g[0].pb({i, 0});
    }

    queue<int> q;
    vector<bool> enter(n + 1, false);
    enter[0]= true;
    times[0]= 1;
    value[0]= 0;
    q.push(0);
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
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
}
