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

int MOD = 376544743;
ll dp[9][1 << 16];

int get(int s, int j)
{
    return (s >> (j << 1)) & 3;
}

int setv(int s, int j, int v)
{
    s = s & (~(3 << (j << 1)));
    return s | (v << (j << 1));
}

// https://www.luogu.com.cn/problem/P2435
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(dp, -1, sizeof(dp));
    int n, m, k, num;
    cin >> n >> m >> k;

    int first = 0;
    int last = 0;
    for (int i = m - 1; i >= 0; i--)
    {
        cin >> num;
        first <<= 2;
        first |= num;
    }

    for (int i = m - 1; i >= 0; i--)
    {
        cin >> num;
        last <<= 2;
        last |= num;
    }

    int a;
    if (k == 2)
    {
        a = n - 2;
        if ((first == last) != (a % 2))
        {
            cout << 0 << endl;
        }
        else
        {
            cout << 1 << endl;
        }
    }
    else
    {
        vi prepare(1 << (2 * m), 1);

        for (int s = 0; s < (1 << (2 * m)); s++)
        {
            for (int j = 0; j < m; j++)
            {
                if (get(s, j) == get(last, j))
                {
                    prepare[s] = 0;
                }
            }
        }

        for (int i = n - 2; i >= 1; i--)
        {
            for (int s = 0; s < (1 << (2 * m)); s++)
            {
                dp[m][s] = prepare[s];
            }

            for (int j = m - 1; j >= 0; j--)
            {
                for (int s = 0; s < (1 << (2 * m)); s++)
                {
                    ll res = 0;
                    for (int p = 0; p < k; p++)
                    {

                        if (j == 0 && get(s, 0) != p)
                        {
                            if (i > 1 || (i == 1 && p != get(first, 0)))
                            {
                                res += dp[j + 1][setv(s, 0, p)];
                            }
                        }

                        if (j > 0 && get(s, j) != p && get(s, (j - 1)) != p)
                        {
                            if (i > 1 || (i == 1 && p != get(first, j)))
                            {
                                res += dp[j + 1][setv(s, j, p)];
                            }
                        }
                    }
                    res %= MOD;
                    dp[j][s] = res;
                }
            }

            for (int s = 0; s < (1 << (2 * m)); s++)
            {
                prepare[s] = dp[0][s];
            }
        }
        cout << dp[0][first] << endl;
    }

    // 未空间压缩状态过多，无法通过
    // function<ll(int, int, int)> dfs = [&](int i, int j, int s) -> ll
    // {
    //     if (i == n - 1)
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
    //     for (int p = 0; p < k; p++)
    //     {

    //         if (j == 0 && get(s, 0) != p)
    //         {
    //             if (i < n - 2 || (i == n - 2 && p != get(last, 0)))
    //             {
    //                 res += dfs(i, j + 1, setv(s, 0, p));
    //             }
    //         }

    //         if (j > 0 && get(s, j * 2) != p && get(s, (j - 1) * 2) != p)
    //         {
    //             if (i < n - 2 || (i == n - 2 && p != get(last, j * 2)))
    //             {
    //                 res += dfs(i, j + 1, setv(s, j * 2, p));
    //             }
    //         }
    //     }
    //     res %= MOD;
    //     dp[i][j][s] = res;
    //     return res;
    // };

    // ll res = dfs(1, 0, first);
    // cout << res << endl;
}