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

/*

树的重心定义：
1. 节点的最大子树的节点数最少
2. 以此节点为根时，每个子树的节点数不超过总节点数的一半
3. 所有节点走向该节点的总边数最少

性质：
1. 最多有一个或两个重心
2. 增加或减少节点时，重心最多移动一条边
3. 连接两颗树的节点，新的重心必然在两个重心的路径上
4. 不管边权如何，到重心的总距离最小（但是到重心的最大距离不一定最小）

*/

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, y;

    cin >> n;
    vvi g(n + 1);

    for0(i, n - 1)
    {
        cin >> x >> y;
        g[x].pb(y);
        g[y].pb(x);
    }
    int center = -1;
    int best = INT_MAX;

    // 1
    function<int(int, int)> dfs1 = [&](int i, int p) -> int
    {
        int res = 1;
        int mx = 0;
        int ret;
        for (auto nxt : g[i])
        {
            if (nxt != p)
            {
                ret = dfs1(nxt, i);
                res += ret;
                mx = max(mx, ret);
            }
        }

        mx = max(mx, n - res);
        if (mx < best || (mx == best && i < center))
        {
            best = mx;
            center = i;
        }
        return res;
    };

    dfs1(1, -1);
    cout << center << endl;

    vi cnt;

    // 2
    function<int(int, int)> dfs2 = [&](int i, int p) -> int
    {
        int res = 1;
        int mx = 0;
        int ret;
        for (auto nxt : g[i])
        {
            if (nxt != p)
            {
                ret = dfs2(nxt, i);
                res += ret;
                mx = max(mx, ret);
            }
        }
        mx = max(mx, n - res);
        if (mx <= n / 2)
        {
            cnt.pb(i);
        }
        return res;
    };

    dfs2(1, -1);
    for (auto node : cnt)
    {
        cout << node << endl;
    }

    return 0;
}