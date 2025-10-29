#include <bits/stdc++.h>

#include <numeric>
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

// https://www.luogu.com.cn/problem/P2801
// 分块模版，区间更新，懒更新直接清空
struct SQRT {
    int n, bs;
    vi nums;
    vi nums1;
    vi bl, br;
    vi lazy;

    SQRT(int size, const vi& lst) {
        nums= lst;
        n= size;
        bs= (int)sqrt(n) + 1;

        for (int i= 0; i < n; i+= bs) {
            bl.push_back(i);
            br.push_back(min(i + bs - 1, n - 1));
            lazy.pb(0);
        }

        nums1= nums;
        for (int i= 0; i < (int)bl.size(); i++) {
            sort(nums1.begin() + bl[i], nums1.begin() + br[i] + 1);
        }
    }

    // given i, which block it's in
    int get(int i) { return i / bs; }

    // count how many nums greater or equal to t in block idx
    int countg(int idx, int t) {
        int l= bl[idx], r= br[idx];
        auto it= lower_bound(nums1.begin() + l, nums1.begin() + r + 1,
                             t - lazy[idx]);
        return (r - l + 1) - (it - (nums1.begin() + l));
    }

    // add t to block from index l to r
    void add(int b, int l, int r, int t) {
        for (int i= l; i <= r; i++) {
            nums[i]+= t;
        }
        vi temp;
        for (int i= bl[b]; i <= br[b]; i++) {
            temp.pb(nums[i]);
        }
        sort(temp.begin(), temp.end());
        for (int i= bl[b]; i <= br[b]; i++) {
            nums1[i]= temp[i - bl[b]];
        }
    }

    // from index l to r, all the number add t
    void update(int l, int r, int t) {
        int lb= get(l);
        int rb= get(r);
        if (lb == rb) {
            if (lazy[lb] > 0) {
                for (int i= bl[lb]; i <= br[lb]; i++) {
                    nums[i]+= lazy[lb];
                }
                lazy[lb]= 0;
            }
            add(lb, l, r, t);
        } else {
            for (int i= lb + 1; i <= rb - 1; i++) {
                lazy[i]+= t;
            }
            if (lazy[lb] > 0) {
                for (int i= bl[lb]; i <= br[lb]; i++) {
                    nums[i]+= lazy[lb];
                }
                lazy[lb]= 0;
            }
            add(lb, l, br[lb], t);
            if (lazy[rb] > 0) {
                for (int i= bl[rb]; i <= br[rb]; i++) {
                    nums[i]+= lazy[rb];
                }
                lazy[rb]= 0;
            }
            add(rb, bl[rb], r, t);
        }
    }

    // find from l to r, how many numbers greater than or equal to t
    int query(int l, int r, int t) {
        int lb= get(l), rb= get(r), ans= 0;
        if (lb == rb) {
            for (int i= l; i <= r; i++)
                if (nums[i] >= t - lazy[lb]) ans++;
            return ans;
        }
        for (int i= l; i <= br[lb]; i++)
            if (nums[i] >= t - lazy[lb]) ans++;
        for (int j= lb + 1; j < rb; j++) ans+= countg(j, t);
        for (int i= bl[rb]; i <= r; i++)
            if (nums[i] >= t - lazy[rb]) ans++;
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vi nums(n);
    for (int i= 0; i < n; i++) cin >> nums[i];

    SQRT sq(n, nums);

    int l, r, w, c;
    while (q--) {
        char op;
        cin >> op;
        if (op == 'A') {
            cin >> l >> r >> c;
            cout << sq.query(l - 1, r - 1, c) << "\n";
        } else {
            cin >> l >> r >> w;
            sq.update(l - 1, r - 1, w);
        }
    }
    return 0;
}
