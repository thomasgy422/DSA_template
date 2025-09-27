#include <algorithm>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>

#define pb push_back
#define fi first
#define se second

#define present(c, x) ((c).find(x) != (c).end())
#define cpresent(c, x) (find(all(c), x) != (c).end())
#define sz(a) int((a).size())

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef double ld;

// https://www.luogu.com.cn/problem/P3478
// long long
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, y;
    cin >> n;

    vvi g(n + 1);
    for (int i= 0; i < n - 1; i++) {
        cin >> x >> y;
        g[x].pb(y);
        g[y].pb(x);
    }

    vi sum(n + 1);
    vll dp(n + 1);

    function<int(int, int, int)> dfs= [&](int i, int p, int d) -> int {
        int res= 1;
        dp[1]+= d;
        for (auto nxt : g[i]) {
            if (nxt != p) res+= dfs(nxt, i, d + 1);
        }
        sum[i]= res;
        return res;
    };

    dfs(1, 0, 0);
    ll mx= dp[1];
    function<void(int, int)> f= [&](int i, int p) {
        for (auto nxt : g[i]) {
            if (nxt != p) {
                dp[nxt]= dp[i] + n - 2 * sum[nxt];
                mx= max(mx, dp[nxt]);
                f(nxt, i);
            }
        }
    };

    f(1, 0);
    for (int i= 1; i <= n; i++) {
        if (dp[i] == mx) {
            cout << i << endl;
            break;
        }
    }
}
