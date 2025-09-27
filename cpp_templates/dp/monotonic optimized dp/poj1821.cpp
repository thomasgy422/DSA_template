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

struct Comp {
    bool operator()(const vi& a, const vi& b) const { return a[2] < b[2]; }
};

int dp[102][16002];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    memset(dp, 0, sizeof(dp));

    int n, k, l, p, s;
    cin >> n >> k;

    vvi w(k + 1, vi(3));

    for (int i= 1; i <= k; i++) {
        cin >> w[i][0] >> w[i][1] >> w[i][2];
    }

    deque<int> dq;
    sort(w.begin() + 1, w.end(), Comp());

    for (int i= 1; i <= k; i++) {
        l= w[i][0];
        p= w[i][1];
        s= w[i][2];
        dq.clear();

        for (int t= max(0, s - l); t < s; t++) {
            while (!dq.empty() && dp[i - 1][t] - t * p >=
                                      dp[i - 1][dq.back()] - dq.back() * p) {
                dq.pop_back();
            }
            dq.push_back(t);
        }

        for (int j= 1; j <= n; j++) {
            dp[i][j]= max(dp[i - 1][j], dp[i][j - 1]);

            if (j >= s) {
                while (!dq.empty() && j - dq.front() > l) dq.pop_front();

                if (!dq.empty()) {
                    dp[i][j]= max(dp[i][j], dp[i - 1][dq.front()] -
                                                dq.front() * p + j * p);
                }
            }
        }
    }

    cout << dp[k][n] << endl;
}

/*

    1 2 3 4 5 6 7 8
      2 3.  5   7

    sort
    dp[i][prev]

    3 4 5  6
    2 3 4

    dp[i][j] = max(dp[i-1][j] + dp[i][j - 1])

    4 3 8

    1 2 3 4 5 6 7 8 9 10

    dp[i][8] = max(dp[i - 1][5] + 3 * 3
                   dp[i - 1][6] + 2 * 3
                   dp[i - 1][7] + 1 * 3)

    dp[i][9] = max(dp[i - 1][6] + 3 * 3
                   dp[i - 1][7] + 2 * 3)

    dp[i][8] = max(dp[i - 1][5] - 5 * 3
                   dp[i - 1][6] - 6 * 3
                   dp[i - 1][7] - 7 * 3)

    dp[i][9] = max(dp[i - 1][6] + 3 * 3
                   dp[i - 1][7] + 2 * 3)
             = max( dp[i - 1][6] - 6 * 3
                   dp[i - 1][7] - 7 * 3) + 9 * 3  after pop the unvalid ones


*/