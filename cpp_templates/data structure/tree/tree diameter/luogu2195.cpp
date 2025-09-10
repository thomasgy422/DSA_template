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

    int n, m, q;
    int op, x, y;

    cin >> n >> m >> q;
    vvi g(n + 1);
    vi vis(n + 1);

    for0(i, m)
    {
        cin >> x >> y;
        g[x].pb(y);
        g[y].pb(x);
    }

    vi par(n + 1);
    int ans = 0;

    function<int(int, int, int)> dfs = [&](int i, int p, int s) -> int
    {
        vis[i] = 1;
        par[i] = s;
        int mx = 0;
        for (auto nxt : g[i])
        {
            if (nxt != p)
            {
                int ret = dfs(nxt, i, s);
                ans = max(ans, mx + ret);
                mx = max(mx, ret);
            }
        }
        return 1 + mx;
    };

    vi dia(n + 1);

    for1(i, n)
    {
        if (vis[i] == 0)
        {
            ans = 0;
            dfs(i, 0, i);
            dia[i] = ans;
        }
    }

    function<int(int)> find = [&](int i) -> int
    {
        if (i != par[i])
        {
            par[i] = find(par[i]);
        }
        return par[i];
    };

    function<void(int, int)> merge = [&](int a, int b)
    {
        int para = find(a);
        int parb = find(b);
        if (para != parb)
        {
            par[para] = parb;
        }
    };

    int p1, p2, d, d1, d2;
    for0(i, q)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> x;
            p1 = find(x);
            cout << dia[p1] << endl;
        }
        else
        {
            cin >> x >> y;
            p1 = find(x);
            p2 = find(y);
            d1 = dia[p1];
            d2 = dia[p2];
            if (p1 == p2)
                continue;
            d = max(max(d1, d2), (d1 + 1) / 2 + (d2 + 1) / 2 + 1);
            merge(p1, p2);
            dia[p2] = d;
        }
    }
}