#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <cstring>
#include <cstdlib>

#define for0(i, n) for (int i = 0; i < (int)(n); ++i)            // 0 based indexing
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)           // 1 based indexing
#define forc(i, l, r) for (int i = (int)(l); i <= (int)(r); ++i) // closed interver from l to r r inclusive
#define forr0(i, n) for (int i = (int)(n) - 1; i >= 0; --i)      // reverse 0 based.
#define forr1(i, n) for (int i = (int)(n); i >= 1; --i)          // reverse 1 based

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

// https://leetcode.com/problems/path-with-minimum-effort/
class Leetcode1631
{
public:
    int minimumEffortPath(vector<vector<int>> &heights)
    {
        int inf = 1e9;
        int m = sz(heights);
        int n = sz(heights[0]);
        priority_queue<vi, vvi, greater<vi>> pq;

        vvi dis(m);

        for0(i, m)
        {
            vi temp(n);
            for0(j, n)
            {
                temp[j] = inf;
            }
            dis[i] = temp;
        }

        vii dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        dis[0][0] = 0;
        pq.push({0, 0, 0});
        while (!pq.empty())
        {
            vi cur = pq.top();
            int d = cur[0];
            int x = cur[1];
            int y = cur[2];
            pq.pop();

            if (x == m - 1 && y == n - 1)
            {
                return d;
            }

            if (d > dis[x][y])
                continue;

            for (auto [dx, dy] : dir)
            {
                int nx = x + dx;
                int ny = y + dy;
                if (nx < 0 || nx >= m || ny < 0 || ny >= n)
                    continue;
                int nxtd = max(d, abs(heights[nx][ny] - heights[x][y]));
                if (nxtd < dis[nx][ny])
                {
                    dis[nx][ny] = nxtd;
                    pq.push({nxtd, nx, ny});
                }
            }
        }

        return inf;
    }
};

// multilayer dijkstra.
// https://leetcode.cn/problems/DFPeFJ/description/
class LeetcodeLCP35
{
public:
    int dis[101][101];
    int electricCarPlan(vector<vector<int>> &paths, int cnt, int start, int end, vector<int> &charge)
    {
        int inf = 1e9;
        int n = sz(charge);
        vector<vvi> g(n);

        for0(i, n)
        {
            vvi temp;
            g[i] = temp;
        }

        for (auto p : paths)
        {
            g[p[0]].pb({p[1], p[2]});
            g[p[1]].pb({p[0], p[2]});
        }

        // dis[i][j] cost of arriving at city i with j power left
        vvi dis(n);
        for0(i, n)
        {
            vi temp(cnt + 1);
            for0(j, cnt + 1)
            {
                temp[j] = inf;
            }
            dis[i] = temp;
        }

        priority_queue<vi, vvi, greater<vi>> pq;
        for0(i, cnt + 1)
        {
            dis[start][i] = i * charge[start];
            pq.push({i * charge[start], i, start});
        }
        int res = inf;

        while (!pq.empty())
        {
            vi cur = pq.top();
            int d = cur[0];
            int r = cur[1];
            int node = cur[2];
            pq.pop();

            // when we arrive at end, then return
            if (node == end)
            {
                return d;
            }

            if (d > dis[node][r])
                continue;

            for (auto e : g[node])
            {
                int nxt = e[0];
                int cost = e[1];
                int temp = cost;
                while (temp <= cnt)
                {
                    int c = max(r, temp) - cost;
                    int nxtd = d + max(0, (temp - r)) * charge[node] + cost;
                    if (nxtd < dis[nxt][c])
                    {
                        dis[nxt][c] = nxtd;
                        pq.push({nxtd, c, nxt});
                    }
                    temp++;
                }
            }
        }
        return res;
    }
};