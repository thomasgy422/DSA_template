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

const int MAXN = 50002;
const int LIMIT = 17;

int st[MAXN][LIMIT];
int deep[MAXN];
int par[MAXN];

// https://www.luogu.com.cn/problem/P3128
/*

树上点权差分模版
x += 1
y += 1
lca -= 1
par[lca] -= 1
最后dfs遍历一遍

*/
class LCA
{
public:
    vvi adj;
    int ll;
    int mxd = 0;
    int pow;

    LCA(vvi g, int s)
    {
        ll = sz(g);
        adj = g;
        dfs(s, 0, 1);

        pow = (int)floor(log2(mxd));
        for (int p = 1; p <= pow; p++)
        {
            for (int i = 1; i <= ll; i++)
            {
                if (st[i][p - 1] != -1)
                    st[i][p] = st[st[i][p - 1]][p - 1];
            }
        }
    }

    void dfs(int i, int p, int d)
    {
        par[i] = p;
        st[i][0] = p;
        if (d > mxd)
            mxd = d;
        deep[i] = d;
        if (sz(adj[i]) == 1 && p != 0)
            return;
        for (int nxt : adj[i])
        {
            if (nxt != p)
                dfs(nxt, i, d + 1);
        }
    }

    int get(int a, int b)
    {
        if (a == b)
        {
            return a;
        }

        if (deep[a] < deep[b])
        {
            int temp = a;
            a = b;
            b = temp;
        }

        int a1 = a;
        for (int p = pow; p >= 0; p--)
        {
            if (st[a1][p] != -1 && deep[st[a1][p]] >= deep[b])
            {
                a1 = st[a1][p];
            }
        }
        if (a1 == b)
            return a1;
        for (int p = pow; p >= 0; p--)
        {
            if (st[a1][p] != st[b][p])
            {
                a1 = st[a1][p];
                b = st[b][p];
            }
        }
        return st[a1][0];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, x, y;
    cin >> n >> k;

    vvi g(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        cin >> x >> y;
        g[x].pb(y);
        g[y].pb(x);
    }

    LCA lca(g, 1);
    vi cost(n + 1);

    int lcanode;
    for (int i = 0; i < k; i++)
    {
        cin >> x >> y;
        lcanode = lca.get(x, y);
        cost[x] += 1;
        cost[y] += 1;
        cost[lcanode] -= 1;
        cost[par[lcanode]] -= 1;
    }

    int ans = 0;
    function<int(int, int)> dfs1 = [&](int i, int p) -> int
    {
        int ret = 0;
        for (auto nxt : g[i])
        {
            if (nxt != p)
            {
                ret += dfs1(nxt, i);
            }
        }
        cost[i] += ret;
        ans = max(ans, cost[i]);
        return cost[i];
    };

    dfs1(1, 0);
    cout << ans << endl;
}