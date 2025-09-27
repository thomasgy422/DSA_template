#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <list>
#include <cstring>
#include <functional>

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

// https://www.luogu.com.cn/problem/P1879
int MOD = 1e8;
int dp[12][1 << 12];
int grid[12][12];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(dp, -1, sizeof(dp));
    int m, n, a;
    cin >> m >> n;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> grid[i][j];
        }
    }

    vvi lst(m);
    bool f;
    for (int i = 0; i < m; i++)
    {
        for (int mask = 0; mask < (1 << n); mask++)
        {
            f = true;
            for (int j = 0; j < n; j++)
            {
                if ((((mask >> j) & 1) == 1 && grid[i][j] == 0) || (j > 0 && ((mask >> (j - 1)) & 1) == 1 && ((mask >> j) & 1) == 1))
                {
                    f = false;
                    break;
                }
            }

            if (f)
            {
                lst[i].pb(mask);
            }
        }
    }

    function<ll(int, int)> dfs = [&](int i, int prev) -> ll
    {
        if (i == m)
        {
            return 1;
        }

        if (dp[i][prev] != -1)
        {
            return dp[i][prev];
        }
        ll res = 0;
        for (auto nxt : lst[i])
        {
            if ((nxt & prev) == 0)
            {
                res += dfs(i + 1, nxt);
                res %= MOD;
            }
        }
        res %= MOD;
        dp[i][prev] = res;
        return res;
    };

    ll ans = dfs(0, 0);
    cout << ans % MOD << endl;
}