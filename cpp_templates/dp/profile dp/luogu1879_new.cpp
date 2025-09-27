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

int MOD = 1e8;
int dp[13][13][1 << 12];
int grid[13][13];

int get(int s, int i)
{
    return (s >> i) & 1;
}

int setv(int s, int i, int v)
{
    return v == 0 ? (s & (~(1 << i))) : (s | (1 << i));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(dp, -1, sizeof(dp));
    int m, n;
    cin >> m >> n;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> grid[i][j];
        }
    }

    function<int(int, int, int)> dfs = [&](int i, int j, int prev) -> int
    {
        if (i == m)
        {
            return 1;
        }

        if (j == n)
        {
            return dfs(i + 1, 0, prev);
        }

        if (dp[i][j][prev] != -1)
        {
            return dp[i][j][prev];
        }

        ll res = dfs(i, j + 1, setv(prev, j, 0));
        if (grid[i][j] == 1)
        {
            if (j == 0 || (j > 0 && get(prev, j - 1) == 0))
            {
                if (get(prev, j) == 0)
                {
                    res += dfs(i, j + 1, setv(prev, j, 1));
                    res %= MOD;
                }
            }
        }
        dp[i][j][prev] = res;
        return res;
    };

    int res = dfs(0, 0, 0);
    cout << res << endl;
}