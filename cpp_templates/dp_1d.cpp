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

// https://leetcode.com/problems/minimum-cost-for-tickets/description/
// bottom-up
class Leetcode983
{
public:
    int dp[366];
    int mincostTickets(vector<int> &days, vector<int> &costs)
    {
        int n = sz(days);
        for (int i = 1; i < 366; i++)
            dp[i] = INT_MAX;
        int time[] = {1, 7, 30};
        dp[0] = 0;
        for0(i, n)
        {
            for0(j, 3)
            {
                int cur = days[i];
                int k = i;
                while (k >= 0 && days[k] >= cur - time[j] + 1)
                {
                    k--;
                }

                dp[i + 1] = min(dp[i + 1], costs[j] + dp[k + 1]);
            }
        }
        return dp[n];
    }
};

// https://leetcode.com/problems/distinct-subsequences-ii/
class Leetcode940
{
public:
    int MOD = 1e9 + 7;
    int distinctSubseqII(string s)
    {
        ll res = 1;
        int dp[26];
        for (auto c : s)
        {
            // we need to minus the number of duplicates last time we see the same char
            ll nxt = (res - dp[c - 'a'] + MOD) % MOD;
            res = res + nxt;
            res %= MOD;
            // add the new duplicates
            dp[c - 'a'] += nxt % MOD;
        }
        return (res - 1 + MOD) % MOD;
    }
};
