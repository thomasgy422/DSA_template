#include <bits/stdc++.h>

#include <numeric>
using namespace std;

#define pb push_back
#define fi first
#define se second

#define present(c, x) ((c).find(x) != (c).end())
#define cpresent(c, x) (find(all(c), x) != (c).end())
#define sz(a) int((a).size())

typedef long long i64;
typedef double ld;
typedef __int128_t i128;
typedef pair<int, int> ii;
typedef pair<int, ld> pid;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;

// 树链剖分模版题： https://www.luogu.com.cn/problem/P3384
// 分析过程：
// dfs1 处理节点的父亲，大小，深度，重孩子
// dfs2 处理dfn序，反dfn序，每条重链的头节点top
// 每一条路径的更新或求和可以拆分成，多条链的更新或求和，而这些链的dfn序又是连续的
// 因此可以用线段树来维护区间的更新和查询
// 细节：查询x，y是要看那条所处的链dep更低，则先处理哪条，并更新节点为fa【top】，
// 如果两个节点处在一条链上了，则判断高低在更新即可

struct SegmentTree {
    i64 mod;
    int n;
    vi nums;
    vi64 sums;
    vi64 value;

    SegmentTree(vi& lst, i64 p) {
        mod= p;
        n= sz(lst) - 1;
        nums= lst;
        sums.resize(n << 2);
        value.resize(n << 2);
        build(1, n, 1);
    }

    void up(int i) { sums[i]= (sums[i << 1] + sums[i << 1 | 1]) % mod; }

    void down(int i, int ln, int rn) {
        if (value[i] != 0) {
            lazy(i << 1, ln, value[i]);
            lazy(i << 1 | 1, rn, value[i]);
            value[i]= 0;
        }
    }

    void lazy(int i, int len, i64 v) {
        sums[i]+= len * v;
        sums[i]%= mod;
        value[i]+= v;
        value[i]%= mod;
    }

    void build(int l, int r, int i) {
        if (l == r) {
            sums[i]= (i64)nums[l] % mod;
        } else {
            int mid= (l + r) >> 1;
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);
            up(i);
        }
    }

    void update(int jobl, int jobr, int jobv) {
        _update(jobl, jobr, jobv, 1, n, 1);
    }

    void _update(int jobl, int jobr, int jobv, int l, int r, int i) {
        if (jobl <= l && r <= jobr) {
            lazy(i, r - l + 1, jobv);
        } else {
            int mid= (l + r) >> 1;
            down(i, mid - l + 1, r - mid);
            if (jobl <= mid) _update(jobl, jobr, jobv, l, mid, i << 1);
            if (jobr > mid) _update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            up(i);
        }
    }

    i64 query(int jobl, int jobr) { return _query(jobl, jobr, 1, n, 1); }

    i64 _query(int jobl, int jobr, int l, int r, int i) {
        i64 ans= 0;
        if (jobl <= l && r <= jobr) {
            ans+= sums[i];
            ans%= mod;
        } else {
            int mid= (l + r) >> 1;
            down(i, mid - l + 1, r - mid);
            if (jobl <= mid) {
                ans+= _query(jobl, jobr, l, mid, i << 1);
                ans%= mod;
            }
            if (jobr > mid) {
                ans+= _query(jobl, jobr, mid + 1, r, i << 1 | 1);
                ans%= mod;
            }
        }
        return ans;
    }
};

void solve() {
    int n, m, r, v, x, y, z, op;
    i64 p;
    cin >> n >> m >> r >> p;
    vi value(n + 1);
    for (int i= 1; i <= n; i++) {
        cin >> value[i];
    }

    vvi g(n + 1);
    for (int i= 0; i < n - 1; i++) {
        cin >> x >> y;
        g[x].pb(y);
        g[y].pb(x);
    }

    vi dep(n + 1);
    vi fa(n + 1);
    vi son(n + 1);
    vi size(n + 1);

    function<void(int, int, int)> dfs1= [&](int i, int par, int d) {
        int cursize= 0;
        int s= 0;
        int total= 1;
        dep[i]= d;
        fa[i]= par;
        for (auto nxt : g[i]) {
            if (nxt != par) {
                dfs1(nxt, i, d + 1);
                total+= size[nxt];
                if (size[nxt] > cursize) {
                    s= nxt;
                    cursize= size[nxt];
                }
            }
        }
        son[i]= s;
        size[i]= total;
    };

    dfs1(r, r, 1);

    int clock= 0;
    vi dfn(n + 1);
    vi top(n + 1);
    // dfn order -> node
    vi seg(n + 1);

    function<void(int, int)> dfs2= [&](int i, int t) {
        clock++;
        top[i]= t;
        dfn[i]= clock;
        if (son[i] == 0) return;
        dfs2(son[i], t);
        for (auto nxt : g[i]) {
            if (nxt != son[i] && nxt != fa[i]) {
                dfs2(nxt, nxt);
            }
        }
    };

    dfs2(r, r);

    for (int i= 1; i <= n; i++) {
        seg[dfn[i]]= i;
    }

    vi input(n + 1);
    for (int i= 1; i <= n; i++) {
        input[i]= value[seg[i]];
    }
    
    SegmentTree st(input, p);

    int tx, ty;
    i64 res;
    for (int i= 1; i <= m; i++) {
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> z;
            while (top[x] != top[y]) {
                if (dep[top[x]] <= dep[top[y]]) {
                    st.update(dfn[top[y]], dfn[y], z);
                    y= fa[top[y]];
                } else {
                    st.update(dfn[top[x]], dfn[x], z);
                    x= fa[top[x]];
                }
            }
            if (dfn[x] <= dfn[y]) {
                st.update(dfn[x], dfn[y], z);
            } else {
                st.update(dfn[y], dfn[x], z);
            }
        } else if (op == 2) {
            res= 0;
            cin >> x >> y;
            while (top[x] != top[y]) {
                if (dep[top[x]] <= dep[top[y]]) {
                    res+= st.query(dfn[top[y]], dfn[y]);
                    y= fa[top[y]];
                } else {
                    res+= st.query(dfn[top[x]], dfn[x]);
                    x= fa[top[x]];
                }
            }
            if (dfn[x] <= dfn[y]) {
                res+= st.query(dfn[x], dfn[y]);
            } else {
                res+= st.query(dfn[y], dfn[x]);
            }
            cout << res % p << endl;
        } else if (op == 3) {
            cin >> x >> z;
            int end= dfn[x] + size[x] - 1;
            st.update(dfn[x], end, z);
        } else {
            cin >> x;
            int end= dfn[x] + size[x] - 1;
            cout << st.query(dfn[x], end) % p << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // int t;
    // cin >> t;
    // while(t--)
    //         solve();
    solve();
    return 0;
}

/*
 */