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

    set<ii> hs;
    int n, x, y;
    cin >> n;
    vvi g(n + 1);

    for (int i = 0; i < n - 1; i++)
    {
        cin >> x >> y;
        g[x].pb(y);
        g[y].pb(x);
        hs.insert({x, y});
    }

    vi dp(n + 1);
    function<void(int, int)> dfs = [&](int i, int p) -> void
    {
        for (auto nxt : g[i])
        {
            if (nxt != p)
            {
                ii temp = {i, nxt};
                if (!present(hs, temp))
                {
                    dp[1] += 1;
                }
                dfs(nxt, i);
            }
        }
    };

    dfs(1, 0);

    int mn = dp[1];
    function<void(int, int)> f = [&](int i, int p) -> void
    {
        for (auto nxt : g[i])
        {
            if (nxt != p)
            {
                ii temp = {i, nxt};
                if (!present(hs, temp))
                {
                    dp[nxt] = dp[i] - 1;
                }
                else
                {
                    dp[nxt] = dp[i] + 1;
                }
                mn = min(mn, dp[nxt]);
                f(nxt, i);
            }
        }
    };

    f(1, 0);
    cout << mn << endl;
    for (int i = 1; i <= n; i++)
    {
        if (dp[i] == mn)
            cout << i << " ";
    }
}