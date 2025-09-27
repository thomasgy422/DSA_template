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

ll dp[12][1 << 11];

int get(int s, int j)
{
    return (s >> j) & 1;
}

int setv(int s, int j, int v)
{
    return (v == 0) ? (s & (~(1 << j))) : (s | (1 << j));
}

// http://poj.org/problem?id=2411
// 对于mask，如果有一位是1，表示前一行的此位置有一块竖摆的砖
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (true)
    {
        memset(dp, -1, sizeof(dp));
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;

        vll prepare(1 << m, 1);

        for (int i = n - 1; i >= 0; i--)
        {
            for (int s = 0; s < (1 << m); s++)
            {
                dp[m][s] = prepare[s];
            }

            for (int j = m - 1; j >= 0; j--)
            {
                for (int s = 0; s < (1 << m); s++)
                {
                    ll ans = 0;
                    if (get(s, j) != 1)
                    {
                        if (j + 1 < m && get(s, j + 1) == 0)
                        {
                            ans += dp[j + 2][s];
                        }
                        if (i + 1 < n)
                        {
                            ans += dp[j + 1][setv(s, j, 1)];
                        }
                    }
                    else
                    {
                        ans += dp[j + 1][setv(s, j, 0)];
                    }
                    dp[j][s] = ans;
                }
            }

            for (int s = 0; s < (1 << m); s++)
            {
                prepare[s] = dp[0][s];
            }
        }
        cout << dp[0][0] << endl;

        // function<ll(int, int, int)> dfs = [&](int i, int j, int s) -> ll
        // {
        //     if (i == n)
        //     {
        //         return 1;
        //     }

        //     if (j == m)
        //     {
        //         return dfs(i + 1, 0, s);
        //     }

        //     if (dp[i][j][s] != -1)
        //     {
        //         return dp[i][j][s];
        //     }

        //     ll res = 0;
        //     if (get(s, j) != 1)
        //     {
        //         if (j + 1 < m && get(s, j + 1) == 0)
        //         {
        //             res += dfs(i, j + 2, s);
        //         }

        //         if (i + 1 < n)
        //         {
        //             res += dfs(i, j + 1, setv(s, j, 1));
        //         }
        //     }
        //     else
        //     {
        //         res += dfs(i, j + 1, setv(s, j, 0));
        //     }
        //     dp[i][j][s] = res;
        //     return res;
        // };

        // ll ans = dfs(0, 0, 0);
        // cout << ans << endl;
    }
}
