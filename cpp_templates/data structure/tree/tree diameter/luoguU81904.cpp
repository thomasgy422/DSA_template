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

    int n;
    int x, y, c;

    cin >> n;

    vector<vii> g(n + 1);
    for0(i, n - 1)
    {
        cin >> x >> y >> c;
        g[x].pb({y, c});
        g[y].pb({x, c});
    }

    ll ans = 0;
    function<int(int, int)> dfs = [&](int i, int p) -> int
    {
        int mx = 0;
        for (auto nxt : g[i])
        {
            int node = nxt.fi;
            int c = nxt.se;
            if (node != p)
            {
                int ret = dfs(node, i);
                ans = max(ans, (ll)mx + ret + c);
                mx = max(mx, ret + c);
            }
        }

        return max(0, mx);
    };

    dfs(1, -1);
    cout << ans << endl;
}