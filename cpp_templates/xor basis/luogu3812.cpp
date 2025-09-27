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

// 
ll nums[51];
ll basis[51];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(basis, 0, sizeof(basis));
    int n;
    cin >> n;

    for (int i= 1; i <= n; i++) {
        cin >> nums[i];
    }

    bool f= true;
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
        f= false;
    };

    for (int i= 1; i <= n; i++) {
        insert(nums[i]);
    }

    ll ans= 0;
    for (int i= 50; i >= 0; i--) {
        if ((ans ^ basis[i]) > ans) {
            ans^= basis[i];
        }
    }

    cout << ans << endl;
}