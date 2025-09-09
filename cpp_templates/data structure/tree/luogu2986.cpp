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
#include <climits>
#include <functional>

#define for0(i, n) for (int i = 0; i < (int)(n); ++i)            // 0 based indexing
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)           // 1 based indexing
#define forc(i, l, r) for (int i = (int)(l); i <= (int)(r); ++i) // closed interval from l to r inclusive

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

    int n, total = 0;
    cin >> n;
    vi cost(n + 1);
    vi size(n + 1);

    for1(i, n)
    {
        cin >> cost[i];
        size[i] = cost[i];
        total += cost[i];
    }

    vector<vii> g(n + 1);

    int x, y, d;
    for0(i, n - 1)
    {
        cin >> x >> y >> d;
        g[x].pb({y, d});
        g[y].pb({x, d});
    }

    int center = -1;
    int best = INT_MAX;
    function<int(int, int)> dfs = [&](int i, int p) -> int
    {
        int mx = 0;
        for (auto nxt : g[i])
        {
            int node = nxt.fi;
            if (node != p)
            {
                size[node] = dfs(node, i);
                size[i] += size[node];
                mx = max(mx, size[node]);
            }
        }
        mx = max(mx, total - size[i]);
        if (mx < best)
        {
            best = mx;
            center = i;
        }

        return size[i];
    };

    dfs(1, -1);

    ll ans = 0;

    function<void(int, int, int)> dfs1 = [&](int i, int p, int d)
    {
        ll t = (ll)d * cost[i];
        ans += t;
        for (auto nxt : g[i])
        {
            int node = nxt.fi;
            int dis = nxt.se;
            if (node != p)
            {
                dfs1(node, i, d + dis);
            }
        }
    };

    dfs1(center, -1, 0);
    cout << ans << endl;
}