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

    int n, x, y, c;
    cin >> n;
    vector<vii> g(n + 1);

    for0(i, n - 1)
    {
        cin >> x >> y >> c;
        g[x].pb({y, c});
        g[y].pb({x, c});
    }

    vi last(n + 1);
    vll dis(n + 1);
    int start, end;
    ll mx = 0, dia = 0;

    function<void(int, int, ll)> dfs = [&](int i, int p, ll d)
    {
        if (d > mx)
        {
            mx = d;
            start = i;
        }

        for (auto nxt : g[i])
        {
            int node = nxt.fi;
            int c = nxt.se;

            if (node != p)
            {
                dfs(node, i, d + c);
            }
        }
    };

    dfs(1, 0, 0);

    function<void(int, int, ll)> dfs1 = [&](int i, int p, ll d)
    {
        dis[i] = d;
        if (d > dia)
        {
            dia = d;
        }
        last[i] = p;
        for (auto nxt : g[i])
        {
            int node = nxt.fi;
            int c = nxt.se;

            if (node != p)
            {
                dfs1(node, i, d + c);
            }
        }
    };

    dfs1(start, 0, 0);
    for1(i, n)
    {
        if (dis[i] == dia)
        {
            end = i;
            break;
        }
    }

    vi path(n + 1, 0);
    for (int i = end; i != 0; i = last[i])
    {
        path[i] = 1;
    }

    function<ll(int, int, ll)> f = [&](int i, int p, ll d) -> ll
    {
        ll res = d;
        for (auto nxt : g[i])
        {
            int node = nxt.fi;
            int c = nxt.se;
            if (p != node && path[node] == 0)
            {
                res = max(res, f(node, i, d + c));
            }
        }
        return res;
    };

    int r = end;
    int l = start;
    ll mp;
    for (int i = end; i != start; i = last[i])
    {
        // mp is the longest path that doesn't use any of the nodes that are already in the diameter

        mp = f(i, 0, 0);
        // find the furtherest from end
        if (mp == dia - dis[i])
        {
            r = i;
        }
        // find the first that has the same dis from start, it would be the start of intersection
        if (mp == dis[i] && l == start)
        {
            l = i;
        }
    }

    cout << dia << endl;
    if (l == r)
    {
        cout << 0 << endl;
    }
    else
    {
        int res = 0;
        while (r != l)
        {
            r = last[r];
            res++;
        }
        cout << res << endl;
    }
}