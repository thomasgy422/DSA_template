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

// https://www.luogu.com.cn/problem/P1082
// 扩展欧几里得求同余方程，
// 费马小定理只适用于模数为质数，而此方法只需要a与b互质
// ax≡1(modb) =》 ax % b = 1，求最小的x

ll d, x, y, px, py;

void exgcd(ll a, ll b) {
    if (b == 0) {
        d= a;
        x= 1;
        y= 0;
    } else {
        exgcd(b, a % b);
        px= x;
        py= y;
        x= py;
        y= px - py * (a / b);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    exgcd(a, b);
    cout << ((x % b) + b) % b << endl;
}
