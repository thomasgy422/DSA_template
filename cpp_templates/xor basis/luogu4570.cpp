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

// https://www.luogu.com.cn/problem/P4570
ll basis[64];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(basis, 0, sizeof(basis));
    int n, num;
    cin >> n;
    vvll nums(n + 1, vll(2));
    for (int i= 1; i <= n; i++) {
        cin >> nums[i][0] >> nums[i][1];
    }

    sort(nums.begin() + 1, nums.end(),
         [](const vll& a, const vll& b) { return a[1] > b[1]; });

    int ans= 0;

    function<bool(ll)> insert= [&](ll num) -> bool {
        for (int i= 63; i >= 0; i--) {
            if (num & (1LL << i)) {
                if (basis[i] == 0) {
                    basis[i]= num;
                    return true;
                } else {
                    num^= basis[i];
                }
            }
        }
        return false;
    };

    for (int i= 1; i <= n; i++) {
        if (insert(nums[i][0])) {
            ans+= nums[i][1];
        }
    }

    cout << ans << endl;
}