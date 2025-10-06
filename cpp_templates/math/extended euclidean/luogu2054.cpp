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
typedef long long i64;
typedef __int128 i128;
typedef vector<i64> vll;
typedef vector<vll> vvll;
typedef double ld;

// https://www.luogu.com.cn/problem/P2054
// 好规律发现 i * (2 ^ m) % (n + 1) = l
// 根据扩展欧几里得求 因为 2 ^ m 和 (n + 1) 互质， 所以可以求 x * (2 ^ m) + y *
// (n + 1) = 1 再乘l即可

i64 x, y, px, py;

i64 power(i64 a, i64 p, i64 MOD) {
    i64 res= 1;
    i64 cur= a;
    while (p > 0) {
        if (p & 1) {
            res= (i128)res * cur % MOD;
        }
        p>>= 1;
        cur= (i128)cur * cur % MOD;
    }
    return res;
}

void exgcd(i64 a, i64 b) {
    if (b == 0) {
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
    i64 n, m, l;
    cin >> n >> m >> l;
    i64 MOD= n + 1;
    exgcd(power(2, m, MOD), n + 1);
    x= (x + MOD) % MOD;
    x= (i128)x * (l % MOD) % MOD;
    cout << x << endl;
}
/*
    i * (2 ^ m) % (n + 1) = l
    i * (2 ^ m) = l mod (n + 1)
*/
