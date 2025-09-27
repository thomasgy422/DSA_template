#include <algorithm>
#include <climits>
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

// https://www.luogu.com.cn/problem/P3800
int grid[4002][4002];
int dp[4002];
int ndp[4002];

void clear(deque<int> &dq) {
    while (!dq.empty()) {
        dq.pop_back();
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(grid, 0, sizeof(grid));
    memset(dp, 0, sizeof(dp));
    memset(ndp, 0, sizeof(ndp));
    int n, m, k, t, a, b, v;
    int ans= 0;
    cin >> n >> m >> k >> t;
    for (int i= 0; i < k; i++) {
        cin >> a >> b >> v;
        grid[a][b]= v;
        if (a == 1) {
            dp[b]= v;
            ans= max(ans, v);
        }
    }

    deque<int> dq;
    for (int i= 2; i <= n; i++) {
        dq.pb(1);
        for (int j= 1; j <= m; j++) {
            while (!dq.empty() && j - dq.front() > t) {
                dq.pop_front();
            }

            while (!dq.empty() && dp[j] >= dp[dq.back()]) {
                dq.pop_back();
            }
            dq.pb(j);
            ndp[j]= max(ndp[j], grid[i][j] + dp[dq.front()]);
        }
        clear(dq);
        dq.pb(m);
        for (int j= m; j >= 1; j--) {
            while (!dq.empty() && dq.front() - j > t) {
                dq.pop_front();
            }

            while (!dq.empty() && dp[j] >= dp[dq.back()]) {
                dq.pop_back();
            }
            dq.pb(j);
            ndp[j]= max(ndp[j], grid[i][j] + dp[dq.front()]);
            ans= max(ans, ndp[j]);
        }
        clear(dq);
        for (int j= 1; j <= m; j++) {
            dp[j]= ndp[j];
            ndp[j]= 0;
        }
    }
    cout << ans << endl;
}