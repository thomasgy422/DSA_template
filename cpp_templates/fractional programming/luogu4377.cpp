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

// https://www.luogu.com.cn/problem/P4377

ld sml= 1e-6;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, w;
    cin >> n >> w;

    vvi lst(n + 1, vi(2));
    ld ans= 0;
    ld left= 0, right= 0;
    for (int i= 1; i <= n; i++) {
        cin >> lst[i][0] >> lst[i][1];
        right+= lst[i][1];
    }

    auto check= [&](ld mid) -> bool {
        ld cur;
        vector<ld> arr;
        for (int i= 1; i <= n; i++) {
            cur= lst[i][1] - mid * lst[i][0];
            arr.pb(cur);
        }
        vector<vector<ld>> dp(n + 1, vector<ld>(w + 1, -1));
        function<ld(int, int)> dfs= [&](int i, int j) -> ld {
            if (i == n) return j == w ? 0 : INT_MIN;
            if (dp[i][j] != -1) {
                return dp[i][j];
            }
            ld res= INT_MIN;
            res= max(res, dfs(i + 1, j));
            if (j + lst[i + 1][0] <= w) {
                res= max(res, dfs(i + 1, j + lst[i + 1][0]) + arr[i]);
            } else {
                res= max(res, dfs(i + 1, w) + arr[i]);
            }
            dp[i][j]= res;
            return dp[i][j];
        };
        return dfs(0, 0) >= 0;
    };

    while (left + sml <= right) {
        ld mid= (left + right) / 2;
        if (check(mid)) {
            ans= mid;
            left= mid + sml;
        } else {
            right= mid - sml;
        }
    }

    cout << (int)floor(1000 * ans) << endl;
}
