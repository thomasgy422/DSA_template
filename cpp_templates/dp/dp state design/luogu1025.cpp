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

// https://www.luogu.com.cn/problem/P1025
int dp[201][7];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(dp, -1, sizeof(dp));

    int n, k;
    cin >> n >> k;
    n-= k;
    function<ll(int, int)> dfs= [&](int i, int j) -> ll {
        if (i < 0) {
            return 0;
        }
        if (j == 0) {
            return i > 0 ? 0 : 1;
        }
        if (i == 0) {
            return 1;
        }
        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        // 
        ll res= dfs(i, j - 1) + dfs(i - j, j);
        dp[i][j]= res;
        return res;
    };

    ll res= dfs(n, k);
    cout << res << endl;
}
