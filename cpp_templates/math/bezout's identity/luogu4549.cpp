#include <bits/stdc++.h>
using namespace std;

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

// bezout's identity
// gcd(a, b) = gcd(abs(a), abs(b))
// ax + by = gcd(a, b) 存在整数x，y使得此式成立
// https://www.luogu.com.cn/problem/P4549

int gcd(int a, int b) { return (b == 0) ? a : gcd(b, a % b); }

int nums[21];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, num;
    cin >> n;

    for (int i= 1; i <= n; i++) {
        cin >> nums[i];
    }
    int ans= 0;
    for (int i= 1; i <= n; i++) {
        ans= gcd(abs(nums[i]), ans);
    }
    cout << ans << endl;
}