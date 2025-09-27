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

int nums[100005];
ll dp[100005];

ll value(int i, vll &pre) { return i == 0 ? 0 : dp[i - 1] - pre[i]; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(dp, 0, sizeof(dp));
    int n, k;
    cin >> n >> k;

    for (int i= 1; i <= n; i++) {
        cin >> nums[i];
    }

    vll pre(n + 1);

    pre[0]= 0;
    for (int i= 1; i <= n; i++) {
        pre[i]= pre[i - 1] + nums[i];
    }

    deque<int> dq;
    dq.push_back(0);

    for (int i= 1; i <= n; i++) {
        while (!dq.empty() && value(i, pre) >= value(dq.back(), pre))
            dq.pop_back();
        dq.push_back(i);
        while (!dq.empty() && i - dq.front() > k) dq.pop_front();
        dp[i]= value(dq.front(), pre) + pre[i];
    }
    cout << dp[n] << endl;
}
/*

    dp定义：end 在i且一定要选i的最大和

    dp[i] = max(dp[j] + sum(j : i)) for j from [i - k: i - 1]
    j
    0 1 2
    0 1 2

    1 2 3 4 5 6 7 8

        dp[7] = max(dp[3] - 1_4,
                    dp[4] - 1_5,
                    dp[5] - 1_6)

        dp[8] = min(dp[4] - 1_5,
                    dp[5] - 1_6,
                    dp[6] - 1_7) + 1_8

*/