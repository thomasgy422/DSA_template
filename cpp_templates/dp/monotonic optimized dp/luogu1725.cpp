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

int nums[200005];
int dp[200005];

// https://www.luogu.com.cn/problem/P1725
// 单调队列优化dp，注意更新dp值的限制条件
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    deque<int> dq;
    int n, l, r;
    int ans= INT_MIN;
    cin >> n >> l >> r;
    for (int i= 0; i <= n; i++) {
        dp[i]= INT_MIN;
    }

    for (int i= 0; i <= n; i++) {
        cin >> nums[i];
    }

    dp[0]= nums[0];
    dq.pb(0);

    int j;
    for (int i= 1; i <= n; i++) {
        while (!dq.empty() && i - dq.front() > r) {
            dq.pop_front();
        }
        j= i - l;
        if (j >= 0) {
            while (!dq.empty() && dp[j] >= dp[dq.back()]) {
                dq.pop_back();
            }
            dq.pb(j);
        }
        if (i - dq.front() >= l) dp[i]= dp[dq.front()] + nums[i];
        if (i + r > n) {
            ans= max(ans, dp[i]);
        }
    }
    cout << ans << endl;
}