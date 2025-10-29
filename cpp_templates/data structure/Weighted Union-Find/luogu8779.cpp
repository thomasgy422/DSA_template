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

// https://www.luogu.com.cn/problem/P8779
// 注意find里面的更新逻辑，还有dist[pi] = v + dist[j] - dist[i]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    int a, b;
    i64 s;

    vi64 dist(n + 2, 0);
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

    auto merge= [&](int i, int j, i64 v) {
        int pi= find(i);
        int pj= find(j);
        if (pi == pj) return;
        dist[pi]= dist[j] - dist[i] + v;
        par[pi]= pj;
    };

    for (int i= 1; i <= m; i++) {
        cin >> a >> b >> s;
        b++;
        merge(a, b, s);
    }

    for (int i= 1; i <= q; i++) {
        cin >> a >> b;
        b++;
        if (find(a) != find(b)) {
            cout << "UNKNOWN" << endl;
        } else {
            cout << dist[a] - dist[b] << endl;
        }
    }
    return 0;
}
/*

*/