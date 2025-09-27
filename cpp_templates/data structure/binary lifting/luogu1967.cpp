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

const int MAXN = 10001;
const int LIMIT = 20;

int st[MAXN][LIMIT];
int deep[MAXN];
int par[MAXN];

class LCA
{
public:
    vector<vii> adj;
    vi distance;
    int ll;
    int mxd = 0;
    int pow;
    int source;
    int num;

    LCA(vvi &g, int n, int s)
    {
        int x, y, c;
        num = n;
        source = s;
        adj.resize(n + 1);
        for0(i, sz(g))
        {
            x = g[i][0];
            y = g[i][1];
            c = g[i][2];
            adj[x].pb({y, c});
            adj[y].pb({x, c});
        }
        ll = sz(g);
        distance.resize(n + 1);
        distance[s] = 0;
        dfs(s, -1, 1000001, 1);

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

    void dfs(int i, int p, int d, int level)
    {
        par[i] = p;
        st[i][0] = p;
        deep[i] = level;
        if (level > mxd)
            mxd = level;
        if (i != source)
            distance[i] = d;
        if (sz(adj[i]) == 1 && p != -1)
            return;
        for (auto nxt : adj[i])
        {
            int node = nxt.fi;
            int c = nxt.se;
            if (node != p)
                dfs(node, i, min(d, c), level + 1);
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

    int dis(int a, int b)
    {
        return distance[a] + distance[b] - distance[get(a, b)];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vii> g(n + 1);
    vvi edges;
    int x, y, c;
    for0(i, m)
    {
        cin >> x >> y >> c;
        g[x].pb({y, c});
        g[y].pb({x, c});
        edges.pb({x, y, c});
    }

    int vis[n + 1];
    memset(vis, 0, sizeof(vis));
    vi par(n + 1);
    vvi group(n + 1);

    function<void(int, int)> dfs = [&](int i, int p)
    {
        par[i] = p;
        vis[i] = 1;
        group[p].pb(i);
        for (auto nxt : g[i])
        {
            int node = nxt.fi;
            if (vis[node] == 0)
            {
                dfs(node, p);
            }
        }
    };

    for1(i, n)
    {
        if (vis[i] == 0)
        {
            dfs(i, i);
        }
    }

    vector<vvi> eg(n + 1);
    for (auto e : edges)
    {
        int curp = par[e[0]];
        eg[curp].pb(e);
    }

    int fa[n + 1];
    int rank[n + 1];
    for0(i, n + 1)
    {
        fa[i] = i;
        rank[i] = 1;
    }

    vector<LCA> lcas;
    lcas.reserve(n + 1);
    for1(i, n)
    {
        if (sz(eg[i]) == 0)
            continue;
        vvi &lst = eg[i];
        sort(lst.begin(), lst.end(), [](const vi &a, const vi &b)
             { return a[2] > b[2]; });

        function<int(int)> find = [&](int i)
        {
            if (i != fa[i])
            {
                fa[i] = find(fa[i]);
            }
            return fa[i];
        };

        function<void(int, int)> merge = [&](int a, int b)
        {
            int para = find(a);
            int parb = find(b);
            if (para == parb)
                return;
            if (rank[para] >= rank[parb])
            {
                fa[parb] = para;
                rank[para] += rank[parb];
            }
            else
            {
                fa[para] = parb;
                rank[parb] += rank[para];
            }
        };
        vvi used;
        for (auto e : lst)
        {
            if (find(e[0]) != find(e[1]))
            {
                used.pb(e);
                merge(e[0], e[1]);
            }
        }

        LCA lca(used, n, i);
        lcas[i] = lca;
    }

    int q, a, b;
    cin >> q;
    for0(i, m)
    {
        cin >> a >> b;
        if (par[a] != par[b])
        {
            cout << -1 << endl;
        }
        else
        {
            int pa = par[a];
            LCA &lca = lcas[pa];
            cout << lca.dis(a, b) << endl;
        }
    }
}