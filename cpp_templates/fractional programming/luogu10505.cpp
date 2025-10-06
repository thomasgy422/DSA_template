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

// https://www.luogu.com.cn/problem/P10505

ld sml= 1e-6;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    while (true) {
        cin >> n >> k;
        if (n == 0 && k == 0) {
            break;
        }
        vvi lst(n + 1, vi(2));
        ld ans= 0;
        ld left= 0, right= 0;
        int r= n - k;

        for (int i= 1; i <= n; i++) {
            cin >> lst[i][0];
            right+= lst[i][0];
        }

        for (int i= 1; i <= n; i++) {
            cin >> lst[i][1];
        }

        function<bool(ld)> check= [&](ld mid) -> bool {
            ld cur, res= 0;
            vector<ld> arr;
            priority_queue<ld> pq;
            for (int i= 1; i <= n; i++) {
                cur= lst[i][0] - mid * lst[i][1];
                arr.pb(cur);
            }
            sort(arr.begin(), arr.end(), greater<ld>());
            for (int i= 0; i < r; i++) {
                res+= arr[i];
            }
            return res >= 0;
        };

        while (left < right && right - left >= sml) {
            ld mid= (left + right) / 2;
            if (check(mid)) {
                ans= mid;
                left= mid + sml;
            } else {
                right= mid - sml;
            }
        }
        cout << round(ans * 100) << endl;
    }
}