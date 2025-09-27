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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int l, s, t, m;
    cin >> l >> s >> t >> m;
    vi lst(m);

    for (int i= 0; i < m; i++) {
        cin >> lst[i];
    }

    vi lst1;
    vi f;

    lst1.pb(0);
    f.pb(0);

    for (int i= 0; i < m; i++) {
        if (lst[i] - lst[i - 1] > 1) {
            lst1.pb(lst[i] - 1);
            f.pb(0);
        }
        lst1.pb(lst[i]);
        f.pb(1);
    }

    lst1.pb(l);
    f.pb(0);
    int n= sz(lst1);
    vi dp(n, 1e5);
    dp[0]= 0;

    int left, right, low, hi;
    for (int i= 1; i < n; i++) {
        left= lst1[i] - t;
        right= lst1[i] - s;
        if (right < 0) {
            dp[i]= 1e5;
            continue;
        } else if (left < 0) {
            dp[i]= (f[i] == 1) ? 1 : 0;
            continue;
        }
        low= lower_bound(lst1.begin(), lst1.end(), left) - lst1.begin();
        hi= lower_bound(lst1.begin(), lst1.end(), right) - lst1.begin();

        for (int j= low; j <= hi; j++) {
            dp[i]= min(dp[i], dp[j] + f[i]);
        }
        // cout << lst1[i] << endl;
        // cout << left << " " << right << endl;
        // cout << lst1[low] << " " << lst1[hi] << endl;
        // cout << endl;
    }

    for (int i= 0; i < n; i++) {
        cout << lst1[i] << " " << dp[i] << endl;
    }
}

/*
    2 3


*/