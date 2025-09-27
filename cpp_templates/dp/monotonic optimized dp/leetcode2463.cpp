#include <algorithm>
#include <climits>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>

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

// https://leetcode.com/problems/minimum-total-distance-traveled/description/
const long long INF = 1e15;
class Solution {
public:
    long long minimumTotalDistance(vi& robot, vvi& fac) {
        int n = sz(robot), m = sz(fac);
        sort(robot.begin(), robot.end());
        sort(fac.begin(), fac.end());
        vvll dis(m + 1, vll(n + 1)); 
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dis[i][j] = abs(fac[i - 1][0] - robot[j - 1]);
                if (j > 1)
                    dis[i][j] += dis[i][j - 1];
            }
        }

        vvll dp(m + 1, vll(n + 1, INF));
        for (int i = 0; i <= m; i++) {
            dp[i][0] = 0;
        }

        function<ll(int i, int j)> value = [&](int i, int j) -> ll {
            return dp[i][j] - dis[i + 1][j];
        };

        for (int i = 1; i <= m; i++) {
            // int pos = fac[i][0];
            deque<int> dq;
            dq.pb(0);
            int c = fac[i - 1][1];
            for (int j = 1; j <= n; j++) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j]);
                while (!dq.empty() && value(i - 1, j) <= value(i - 1, dq.back())) {
                    dq.pop_back();
                }    
                dq.pb(j);
                while (!dq.empty() && j - dq.front() > c) {
                    dq.pop_front();
                }
                dp[i][j] = min(dp[i][j], value(i - 1, dq.front()) + dis[i][j]);
            }
        }
        ll ans = INF;
        for (int i = 1; i <= m; i++) {
            ans = min(ans, dp[i][n]);
        }
        return ans;
    }
};

/*

robot = [0,4,6], 
factory = [[2,2],[6,2]]

r   0       4   6

    0 1 2 3 4 5 6

f.      2.      6

    dp[i][j] use first i f process first j robots
    dp[i][j] = min(dp[i - 1][j], dp[i][j])
                                i process j
                    max(dp[i][k] + dis(i, k) for k [max(0, j - c[i]) : j - 1]
            
            1 2 3 4 5 6 7
            dp[5] = min(dp[2] + dis(3,i) + dis(4,i), dis(5,i),
                        dp[3] + dis(4,i), dis(5,i)
                        dp[4] + dis(5,i))
            
            dp[6] = min(dp[3] + dis(4,i) + dis(5,i), dis(6,i),
                        dp[4] + dis(5,i), dis(6,i),
                        dp[5] + dis(6,i)
            
            dp[5] = max(dp[2] - pre[2]
                        dp[3] - pre[3]
                        dp[4] + pre[4]) + pre[5]
            
            dp[6] = max(dp[3] - pre[3]
                        dp[4] - pre[4]
                        dp[5] - pre[5]) + pre[6]

*/