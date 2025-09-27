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

// https://www.luogu.com.cn/problem/P3857
const int MOD= 2008;
ll nums[51];
ll basis[51];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    ll cur;
    string s;
    cin >> n >> m;

    for (int i= 1; i <= m; i++) {
        cur= 0;
        cin >> s;
        for (int j= 0; j <= n; j++) {
            if (s[j] == 'O') {
                cur|= (1LL << j);
            }
        }
        nums[i]= cur;
    }

    function<void(ll)> insert= [&](ll num) -> void {
        for (int i= 50; i >= 0; i--) {
            if (num & (1LL << i)) {
                if (basis[i] == 0) {
                    basis[i]= num;
                    return;
                } else {
                    num^= basis[i];
                }
            }
        }
    };

    for (int i= 1; i <= m; i++) {
        insert(nums[i]);
    }

    ll ans= 1;
    for (int i= 0; i <= 50; i++) {
        if (basis[i] > 0) ans*= 2;
        ans%= MOD;
    }
    cout << ans << endl;
}

/*

11

10

01

*/