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

// https://www.luogu.com.cn/problem/P8775
// 往返x次，转化为x*2从头跳
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll x;

    cin >> n >> x;
    x *= 2;

    vi lst(n);
    for (int i = 0; i < n - 1; i++) {
        cin >> lst[i];
    }

    // 加入x保证不会越界
    lst[n - 1] = x;

    ll cur = lst[0];
    int ans = 0;

    // 同向双指针查询每个左端点大于x的长度
    for (int l = 0, r = 1; l < n; l++) {
        while (cur < x) {
            cur += lst[r++];
        }

        ans = max(ans, r - l);
        cur -= lst[l];
    }

    cout << ans << endl;
}