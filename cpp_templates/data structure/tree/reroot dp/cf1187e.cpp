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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, y;
    cin >> n;
    vvi g(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        cin >> x >> y;
        g[x].pb(y);
        g[y].pb(x);
    }

    vi sum(n + 1);
    vll dp(n + 1);

    function<int(int, int)> dfs = [&](int i, int p) -> int
    {
        int res = 1;
        for (auto nxt : g[i])
        {
            if (nxt != p)
            {
                res += dfs(nxt, i);
            }
        }
        sum[i] = res;
        dp[1] += res;
        return res;
    };

    dfs(1, 0);
    ll ans = dp[1];
    function<void(int, int)> f = [&](int i, int p) -> void
    {
        for (auto nxt : g[i])
        {
            if (nxt != p)
            {
                dp[nxt] = dp[i] - sum[nxt] + n - sum[nxt];
                ans = max(ans, dp[nxt]);
                f(nxt, i);
            }
        }
    };

    f(1, 0);
    cout << ans << endl;
}