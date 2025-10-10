#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second

#define present(c, x) ((c).find(x) != (c).end())
#define cpresent(c, x) (find(all(c), x) != (c).end())
#define sz(a) int((a).size())

typedef long long i64;
typedef double ld;
typedef __int128_t i128;
typedef pair<int, int> ii;
typedef pair<int, ld> pid;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;

const int MOD= 998244353;
const int mx= 1000002;

// https://www.luogu.com.cn/problem/P5367
i64 fac[mx];
void init() {
    fac[0]= 1;
    fac[1]= 1;
    for (int i= 2; i < mx; i++) {
        fac[i]= fac[i - 1] * i % MOD;
    }
}

class FenwickTree {
   public:
    int size;
    int tree[mx];
    FenwickTree(int n) {
        size= n;
        memset(tree, 0, sizeof(tree));
    }
    void update(int i, int v) {
        while (i <= size) {
            tree[i]+= v;
            i+= i & (-i);
        }
    }

    int query(int i) {
        int ans= 0;
        while (i > 0) {
            ans+= tree[i];
            i-= i & (-i);
        }
        return ans;
    }
};

int perm[mx];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();

    int n;
    cin >> n;

    FenwickTree ft(n);
    for (int i= 1; i <= n; i++) {
        ft.update(i, 1);
    }

    for (int i= 1; i <= n; i++) {
        cin >> perm[i];
    }

    i64 ans= 0;
    int count, cur;
    for (int i= 1; i <= n; i++) {
        cur= perm[i];
        count= ft.query(cur - 1);
        ft.update(cur, -1);
        ans+= (count * fac[n - i]);
        ans%= MOD;
    }
    cout << (ans + 1) % MOD << endl;
    return 0;
}
/*


*/