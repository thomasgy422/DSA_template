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
int dp[13][1 << 12];
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

    int ans;

    // store value for each mask, the when j == n.
    vi prepare(1 << n, 1);

    for (int i = m - 1; i >= 0; i--)
    {
        for (int s = 0; s < (1 << n); s++)
        {
            dp[n][s] = prepare[s];
        }

        for (int j = n - 1; j >= 0; j--)
        {
            for (int s = 0; s < (1 << n); s++)
            {
                ans = dp[j + 1][setv(s, j, 0)];
                if (grid[i][j] == 1 && (j == 0 || get(s, j - 1) == 0) && get(s, j) == 0)
                {
                    ans += dp[j + 1][setv(s, j, 1)];
                    ans %= MOD;
                }
                dp[j][s] = ans;
            }
        }

        for (int s = 0; s < (1 << n); s++)
        {
            prepare[s] = dp[0][s];
        }
    }

    cout << dp[0][0];
}