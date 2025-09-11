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
#include <deque>

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

// https://www.luogu.com.cn/problem/P2491
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s;
    cin >> n >> s;
    vector<vii> g(n + 1);

    int x, y, c;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> x >> y >> c;
        g[x].pb({y, c});
        g[y].pb({x, c});
    }

    int dis[n + 1], last[n + 1], path[n + 1], dia[n + 1];
    int mx = 0, diam = 0, start, end;
    memset(path, 0, sizeof(path));
    memset(dis, 0, sizeof(dis));

    function<void(int, int, int)> dfs = [&](int i, int p, int d)
    {
        if (d > mx)
        {
            start = i;
            mx = d;
        }

        for (auto nxt : g[i])
        {
            int node = nxt.fi;
            int w = nxt.se;
            if (node != p)
            {
                dfs(node, i, d + w);
            }
        }
    };

    dfs(1, 0, 0);

    function<void(int, int, int)> dfs1 = [&](int i, int p, int d)
    {
        dis[i] = d;
        last[i] = p;
        if (d > diam)
        {
            diam = d;
            end = i;
        }

        for (auto nxt : g[i])
        {
            int node = nxt.fi;
            int w = nxt.se;
            if (node != p)
            {
                dfs1(node, i, d + w);
            }
        }
    };

    dfs1(start, 0, 0);

    int ans = diam;

    vi mxd(n + 1);

    function<int(int, int, int)> mxf = [&](int i, int p, int d) -> int
    {
        int res = d;
        for (auto nxt : g[i])
        {
            int node = nxt.fi;
            int w = nxt.se;
            if (path[node] == 0 && node != p)
            {
                res = max(res, mxf(node, i, d + w));
            }
        }
        return res;
    };

    vi order(n + 1);
    deque<int> dq;

    for (int i = end, j = diam; i != 0; i = last[i], j--)
    {
        path[i] = 1;
        order[i] = j;
    }

    for (int i = end; i != 0; i = last[i])
    {
        mxd[i] = mxf(i, 0, 0);
    }

    // 滑动窗口最大值
    int r = end;
    for (int i = end; i != 0; i = last[i])
    {
        // 如果当前长度超过s， 移动右端点
        while (dis[r] - dis[i] > s)
        {
            r = last[r];
        }

        while (!dq.empty() && order[dq.front()] > order[r])
        {
            dq.pop_front();
        }

        while (!dq.empty() && mxd[i] >= mxd[dq.back()])
        {
            dq.pop_back();
        }
        dq.pb(i);
        ans = min(ans, max(mxd[dq.front()], max(dis[i], diam - dis[r])));
    }

    cout << ans << endl;
}