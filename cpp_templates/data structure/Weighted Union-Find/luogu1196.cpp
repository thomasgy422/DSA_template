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
const int mx = 30002;

// https://www.luogu.com.cn/problem/P1196
// 维护size，当连接两个集团时，下面的根节点dist加上上面集团的size
void solve() {
    int t;
    cin >> t;

    vector<int> dist(mx, 0);
    vector<int> size(mx, 1);
    vi par(mx);
    for(int i = 1; i < mx; i++) {
        par[i] = i;
    }

    function<int(int)> find = [&](int i) -> int {
        if (i != par[i]) {
            int pi = par[i];
            par[i] = find(pi);
            dist[i] += dist[pi];
        }
        return par[i];
    };

    auto merge = [&](int i, int j) {
        int pi = find(i);
        int pj = find(j);
        if (pi == pj) return;
        dist[pi] += size[pj];
        size[pj] += size[pi];
        par[pi] = pj;    
    };

    char op;
    int a, b;

    for(int i = 1; i <= t; i++) {
        cin >> op >> a >> b;
        if(op == 'M') {
            merge(a, b);
        } else {
            if(find(a) != find(b)) {
                cout << -1 << endl;
            } else {
                cout << abs(dist[a] - dist[b]) - 1 << endl;   
            }
        }
    }


}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
/*
    2 - 3 - 4
    1.  1
*/