
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

const int MAXN = 500001;
const int LIMIT = 20;

int st[MAXN][LIMIT];
int deep[MAXN];
int par[MAXN];

class LCA
{
public:
    vvi adj;
    int ll;
    int mxd = 0;
    int pow;

    LCA(vvi &g, int s)
    {
        ll = sz(g);
        adj = g;
        dfs(s, -1, 1);

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
        if (sz(adj[i]) == 1 && p != -1)
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

    int dis(int a)
    {
        return deep[a] - 1;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vvi g(n + 1);

    int x, y, z;
    for0(i, n - 1)
    {
        cin >> x >> y;
        g[x].pb(y);
        g[y].pb(x);
    }

    LCA lca(g, 1);

    int a, b, c;
    for0(i, m)
    {
        cin >> a >> b >> c;
        x = lca.get(a, b);
        y = lca.get(a, c);
        z = lca.get(b, c);
        int d = lca.dis(a) + lca.dis(b) + lca.dis(c);

        // there will at 1 or 2 lca, if 2, meet at the lower one
        if (x == y && y == z)
        {
            cout << x << " " << d - 3 * lca.dis(x) << endl;
        }
        else
        {
            if (z != x)
                y = z;
            int d1 = lca.dis(x);
            int d2 = lca.dis(y);
            int meet = d1 > d2 ? x : y;
            if (d1 > d2)
            {
                cout << meet << " " << d - 2 * lca.dis(y) - (lca.dis(x)) << endl;
            }
            else
            {
                cout << meet << " " << d - lca.dis(y) - 2 * lca.dis(x) << endl;
            }
        }
    }
}

/*
    if there are k nodes, we want to find the minimum distance that connect all nodes,
    we can do dfs time stamp, and sort the list of node, and get dis between adj nodes
    in the sorted list, also the first and last. Since every path is calculate twice,
    we divide by two.

*/