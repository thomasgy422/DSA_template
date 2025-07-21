#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

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

// https://leetcode.com/problems/stickers-to-spell-word/description/
// check the string we can get 1 step, 2 step..., until we see empty string.
// can also be solved with bitmask dp;
class Leetcode691
{
public:
    int minStickers(vector<string> &st, string target)
    {
        int n = sz(st);
        int m = sz(target);
        sort(target.begin(), target.end());
        vvi counter;
        for0(i, n)
        {
            sort(st[i].begin(), st[i].end());
            vi temp(26);
            for0(j, sz(st[i]))
            {
                temp[st[i][j] - 'a']++;
            }
            counter.pb(temp);
        }

        set<string> hs;
        deque<pair<string, int>> q;

        q.push_back({target, 0});
        while (!q.empty())
        {
            auto [cur, dis] = q.front();
            if (cur == "")
            {
                return dis;
            }
            q.pop_front();
            vi count(26);
            for0(i, sz(cur))
            {
                count[cur[i] - 'a']++;
            }
            for0(i, n)
            {
                string s = st[i];
                vi mp(26);
                for0(j, 26)
                {
                    mp[j] = max(0, count[j] - counter[i][j]);
                }
                string ns = "";
                for0(j, 26)
                {
                    for0(k, mp[j])
                        ns += 'a' + j;
                }
                if (!present(hs, ns))
                {
                    q.push_back({ns, dis + 1});
                    hs.insert(ns);
                }
            }
        }
        return -1;
    }
};

// 01BFS, can be solved with dijkstra as well
// https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/
class Leetcode2290
{
public:
    int minimumObstacles(vector<vector<int>> &grid)
    {
        int inf = 1e9;
        int m = sz(grid);
        int n = sz(grid[0]);
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

        deque<vi> deq;
        if (grid[0][0] == 0)
        {
            dis[0][0] = 0;
            deq.pb({0, 0, 0});
        }
        else
        {
            dis[0][0] = 1;
            deq.pb({0, 0, 1});
        }
        vii dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!deq.empty())
        {
            vi cur = deq.front();
            deq.pop_front();
            int x = cur[0];
            int y = cur[1];
            int d = cur[2];
            if (x == m - 1 && y == n - 1)
            {
                return d;
            }

            for (auto [dx, dy] : dir)
            {
                int nx = x + dx;
                int ny = y + dy;
                if (nx < 0 || nx >= m || ny < 0 || ny >= n)
                    continue;
                int nxt = (grid[nx][ny] == 1) ? 1 : 0;
                if (d + nxt < dis[nx][ny])
                {
                    dis[nx][ny] = d + nxt;
                    if (nxt == 0)
                    {
                        deq.push_front({nx, ny, d});
                    }
                    else
                    {
                        deq.pb({nx, ny, d + 1});
                    }
                }
            }
        }
        return inf;
    }
};

// https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/description/
class Leetcode1368
{
public:
    int minCost(vector<vector<int>> &grid)
    {
        int inf = 1e9;
        int m = sz(grid);
        int n = sz(grid[0]);
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

        deque<vi> dq;
        dis[0][0] = 0;

        dq.pb({0, 0, 0});

        while (!dq.empty())
        {
            vi cur = dq.front();
            int x = cur[0];
            int y = cur[1];
            int d = cur[2];
            if (x == m - 1 && y == n - 1)
            {
                return d;
            }
            dq.pop_front();

            for (auto [dx, dy] : dir)
            {
                int nx = x + dx;
                int ny = y + dy;
                if (nx < 0 || nx >= m || ny < 0 || ny >= n)
                {
                    continue;
                }
                if ((dx == 1 && grid[x][y] == 3) || (dx == -1 && grid[x][y] == 4) || (dy == 1 && grid[x][y] == 1) || (dy == -1 && grid[x][y] == 2))
                {
                    if (d < dis[nx][ny])
                    {
                        dis[nx][ny] = d;
                        dq.push_front({nx, ny, d});
                    }
                }
                else
                {
                    if (d + 1 < dis[nx][ny])
                    {
                        dis[nx][ny] = d + 1;
                        dq.pb({nx, ny, d + 1});
                    }
                }
            }
        }
        return inf;
    }
};

// https://leetcode.com/problems/trapping-rain-water-ii/description/
// BFS with priority queue
class Leetcode407
{
public:
    int trapRainWater(vector<vector<int>> &hm)
    {
        int m = sz(hm);
        int n = sz(hm[0]);
        vvi vis(m);

        for0(i, m)
        {
            vi temp(n);
            vis[i] = temp;
        }
        vii dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        priority_queue<vi, vvi, greater<vi>> pq;
        for0(i, m)
        {
            for0(j, n)
            {
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1)
                {
                    pq.push({hm[i][j], i, j});
                    vis[i][j] = 1;
                }
            }
        }
        int ans = 0;
        while (!pq.empty())
        {
            vi cur = pq.top();
            pq.pop();
            int h = cur[0];
            int x = cur[1];
            int y = cur[2];

            for (auto [dx, dy] : dir)
            {
                int nx = x + dx;
                int ny = y + dy;
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || vis[nx][ny] == 1)
                    continue;
                // The cell will be height of maximum of its height, or the height that explored it.
                ans += max(0, h - hm[nx][ny]);
                pq.push({max(h, hm[nx][ny]), nx, ny});
                vis[nx][ny] = 1;
            }
        }

        return ans;
    }
};