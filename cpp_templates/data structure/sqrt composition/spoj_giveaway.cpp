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

// https://www.spoj.com/problems/GIVEAWAY/
// 分块单点更新模版
struct SQRT {
    int n, bs;
    vi nums;
    vi nums1;
    vi blkl, blkr;

    SQRT(int size, const vi& lst) {
        nums= lst;
        n= size;
        bs= (int)sqrt(n) + 1;

        for (int i= 0; i < n; i+= bs) {
            blkl.push_back(i);
            blkr.push_back(min(i + bs - 1, n - 1));
        }

        nums1= nums;
        for (int i= 0; i < (int)blkl.size(); i++) {
            sort(nums1.begin() + blkl[i], nums1.begin() + blkr[i] + 1);
        }
    }

    int get(int i) { return i / bs; }

    int countg(int idx, int t) {
        int l= blkl[idx], r= blkr[idx];
        auto it= lower_bound(nums1.begin() + l, nums1.begin() + r + 1, t);
        return (r - l + 1) - (it - (nums1.begin() + l));
    }

    void update(int i, int t) {
        nums[i]= t;
        int idx= get(i);
        int l= blkl[idx];
        int r= blkr[idx];
        vi temp;
        for (int i= l; i <= r; i++) {
            temp.pb(nums[i]);
        }
        sort(temp.begin(), temp.end());
        for (int i= l; i <= r; i++) {
            nums1[i]= temp[i - l];
        }
    }

    int query(int l, int r, int t) {
        int lb= get(l), rb= get(r), ans= 0;
        if (lb == rb) {
            for (int i= l; i <= r; i++)
                if (nums[i] >= t) ans++;
            return ans;
        }
        for (int i= l; i <= blkr[lb]; i++)
            if (nums[i] >= t) ans++;
        for (int j= lb + 1; j < rb; j++) ans+= countg(j, t);
        for (int i= blkl[rb]; i <= r; i++)
            if (nums[i] >= t) ans++;
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vi nums(n);
    for (int i= 0; i < n; i++) cin >> nums[i];

    SQRT sq(n, nums);

    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 0) {
            int a, b, c;
            cin >> a >> b >> c;
            cout << sq.query(a - 1, b - 1, c) << "\n";
        } else {
            int idx, c;
            cin >> idx >> c;
            sq.update(idx - 1, c);
        }
    }
    return 0;
}
