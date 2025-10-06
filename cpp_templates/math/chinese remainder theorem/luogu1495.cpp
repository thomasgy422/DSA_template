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
typedef __int128_t i128;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;
typedef double ld;

ostream& operator<<(ostream& os, __int128 value) {
    if (value == 0) {
        return os << "0";
    }
    bool neg = value < 0;
    if (neg) value = -value;

    string s;
    while (value > 0) {
        s.push_back('0' + (value % 10));
        value /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    os << s;
    return os;
}

i64 d, x, y, px, py;

void exgcd(i64 a, i64 b) {
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
    } else {
        exgcd(b, a % b);
        px = x;
        py = y;
        x = py;
        y = px - (a / b) * py;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    i128 lcm = 1;
    cin >> n;
    vvi64 lst(n + 1, vi64(2));

    for(int i = 1; i <= n; i++) {
        cin >> lst[i][0] >> lst[i][1];
        lcm *= lst[i][0];
    } 

    i64 a, b;
    i128 ans = 0, c;
    for (int i = 1; i <= n; i++) {
        a = lst[i][0];
        b = lst[i][1]; 
        exgcd(lcm / a, a);
        x = (x % a + a) % a;
        c = ((b * (lcm / a) % lcm) * x) % lcm;  
        ans += c;
        ans %= lcm;
    }

    cout << ans << endl;
}


