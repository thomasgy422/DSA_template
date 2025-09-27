#include <algorithm>
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

int get(int num, int j) { return (num >> j) & 1; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vi nums(n);

    for (int i= 0; i < n; i++) {
        cin >> nums[i];
    }

    int dp[32];

    memset(dp, 0, sizeof(dp));

    for (auto num : nums) {
        int cur= 1;
        for (int j= 0; j < 31; j++) {
            if (get(num, j) == 1) {
                cur= max(cur, dp[j] + 1);
            }
        }

        for (int j= 0; j < 31; j++) {
            if (get(num, j) == 1) {
                dp[j]= max(dp[j], cur);
            }
        }
    }

    int ans= 1;
    for (auto num : dp) {
        ans= max(ans, num);
    }
    cout << ans << endl;
}

/*
 */