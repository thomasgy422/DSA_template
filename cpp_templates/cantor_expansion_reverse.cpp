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

const int mx= 100002;

template <typename T>
class FenwickTree {
   public:
    int size;
    vector<T> tree;

    FenwickTree(int n) {
        size= n;
        tree.assign(n + 1, 0);
    }

    void update(int i, T v) {
        while (i <= size) {
            tree[i]+= v;
            i+= i & -i;
        }
    }

    T query(int i) const {
        T ans= 0;
        while (i > 0) {
            ans+= tree[i];
            i-= i & -i;
        }
        return ans;
    }

    T rangeQuery(int l, int r) const { return query(r) - query(l - 1); }
};

class SegmentTree {
   public:
    int size;
    vi sum;

    SegmentTree(int n) {
        size= n;
        sum.assign(mx << 2, 0);
        buildTree(1, 1, n);
    }

    void buildTree(int i, int l, int r) {
        if (l == r) {
            sum[i]= 1;
            return;
        }
        int mid= (l + r) >> 1;
        buildTree(i << 1, l, mid);
        buildTree(i << 1 | 1, mid + 1, r);
        sum[i]= sum[i << 1] + sum[i << 1 | 1];
    }

    void update(int jobi, int jobv, int l, int r, int i) {
        if (l == r) {
            sum[i]+= jobv;
            return;
        }
        int mid= (l + r) >> 1;
        if (jobi <= mid) {
            update(jobi, jobv, l, mid, i << 1);
        } else {
            update(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
        sum[i]= sum[i << 1] + sum[i << 1 | 1];
    }

    int getAndDelete(int jobv, int l, int r, int i) {
        int ans;
        if (l == r) {
            sum[i]--;
            ans= l;
        } else {
            int mid= (l + r) >> 1;
            if (sum[i << 1] >= jobv) {
                ans= getAndDelete(jobv, l, mid, i << 1);
            } else {
                ans= getAndDelete(jobv - sum[i << 1], mid + 1, r, i << 1 | 1);
            }
            sum[i]= sum[i << 1] + sum[i << 1 | 1];
        }
        return ans;
    }
};

// https://www.luogu.com.cn/problem/U72177
// 计算每一位右侧比当前小的数的个数，阶乘进制
// 再用线段树从左到右确定每一位的数
int perm[mx];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    i64 m;
    cin >> m;

    FenwickTree<int> ft(n);
    for (int i= 1; i <= n; i++) {
        cin >> perm[i];
    }

    vi count(n + 1);
    for (int i= n; i > 0; i--) {
        ft.update(perm[i], 1);
        count[i]= ft.query(perm[i] - 1);
    }

    i64 cur= m, nxt;
    int mod= 1;
    for (int i= n; i > 0; i--) {
        nxt= (count[i] + cur) / mod;
        count[i]= (count[i] + cur) % mod;
        cur= nxt;
        if (cur == 0) break;
        mod++;
    }

    SegmentTree st(n);
    for (int i= 1; i <= n; i++) {
        int ord= count[i] + 1;
        count[i]= st.getAndDelete(ord, 1, n, 1);
    }

    for (int i= 1; i <= n; i++) {
        cout << count[i] << " ";
    }
    return 0;
}
/*

[0, 0, 0, 0, 0]
 4! 3! 2! 1! 0]

*/