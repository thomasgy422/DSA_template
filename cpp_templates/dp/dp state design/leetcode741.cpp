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

// https://leetcode.com/problems/cherry-pickup/
// consider two person start from 0,0 to n-1,n-1

int dp[51][51][51];
class Solution
{
public:
    int cherryPickup(vector<vector<int>> &grid)
    {
        memset(dp, -1, sizeof(dp));
        int n = sz(grid);

        function<int(int, int, int)> dfs = [&](int i, int j, int p) -> int
        {
            int q = i + j - p;
            if (i >= n || j >= n || p >= n || q >= n || grid[i][j] == -1 || grid[p][q] == -1)
            {
                return INT_MIN;
            }

            if (i == n - 1 && j == n - 1)
            {
                return grid[n - 1][n - 1];
            }

            if (dp[i][j][p] != -1)
            {
                return dp[i][j][p];
            }

            int res = grid[i][j] + (i == p ? 0 : grid[p][q]);
            int best = max(max(dfs(i + 1, j, p + 1), dfs(i + 1, j, p)), max(dfs(i, j + 1, p), dfs(i, j + 1, p + 1)));

            dp[i][j][p] = res + best;
            return dp[i][j][p];
        };

        int res = dfs(0, 0, 0);
        return max(0, res);
    }
};