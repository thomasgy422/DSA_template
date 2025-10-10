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

i64 gcd(i64 a, i64 b) { return (b == 0) ? a : gcd(b, a % b); }

// https://www.luogu.com.cn/problem/P2371
// 每一步找到x与当前值的gcd，跑两圈去更新可以确保都更新到
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 n, l, r;
    cin >> n >> l >> r;

    vi lst(n + 1, 0);

    for (int i= 1; i <= n; i++) {
        cin >> lst[i];
    }

    sort(lst.begin(), lst.end());
    int idx= 0;
    for (int i= 0; i <= n; i++) {
        if (lst[i] == 0) idx++;
    }

    if (idx == n + 2) {
        cout << 0 << endl;
        return 0;
    }

    int x= lst[idx];
    vector<vector<ii>> g(x);

    for (int i= 0; i < x; i++) {
        for (int j= idx + 1; j <= n; j++) {
            g[i].pb({(i + lst[j]) % x, lst[j]});
        }
    }

    vector<i64> dist(x, LLONG_MAX);
    dist[0]= 0;

    for (int i= idx + 1; i <= n; i++) {
        i64 d= gcd(x, lst[i]);
        for (int k= 0; k < d; k++) {
            for (int j= k, nxt, cir= 0; cir < 2; cir+= (j == k) ? 1 : 0) {
                nxt= (j + lst[i]) % x;
                if (dist[j] != LLONG_MAX && dist[j] + lst[i] < dist[nxt]) {
                    dist[nxt]= lst[i] + dist[j];
                }
                j= nxt;
            }
        }
    }

    i64 ans= 0;
    for (int i= 0; i < x; i++) {
        if (dist[i] <= r) {
            ans+= (r - dist[i]) / x + 1;
        }

        if (dist[i] <= l - 1) {
            ans-= (l - 1 - dist[i]) / x + 1;
        }
    }

    cout << ans << endl;
    return 0;
}
/*

*/