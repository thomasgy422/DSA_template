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

// https://www.luogu.com.cn/problem/P2294
// 找矛盾：如果当前两个点已经属于一组，查看距离是否与给的值相等，否则合并
void solve() {
    int n, m, s, t, v;
    cin >> n >> m;

    vector<int> dist(n + 2, 0);
    vi par(n + 2);
    for (int i= 1; i <= n + 1; i++) {
        par[i]= i;
    }

    function<int(int)> find= [&](int i) -> int {
        if (i != par[i]) {
            int pi= par[i];
            par[i]= find(pi);
            dist[i]+= dist[pi];
        }
        return par[i];
    };

    auto merge= [&](int i, int j, int v) {
        int pi= find(i);
        int pj= find(j);
        if (pi == pj) return;
        dist[pi]= dist[j] - dist[i] + v;
        par[pi]= pj;
    };

    for (int i= 1; i <= m; i++) {
        cin >> s >> t >> v;
        t++;
        if (find(s) == find(t)) {
            if (dist[s] - dist[t] != v) {
                cout << "false" << endl;
                return;
            }
        } else {
            merge(s, t, v);
        }
    }
    cout << "true" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int w;
    cin >> w;
    while (w--) {
        solve();
    }
    return 0;
}
/*

*/