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
const int MAXN= 200002;
const int MAXT= MAXN * 18;

// https://www.luogu.com.cn/problem/P3834
// 单点修改，范围查询，每加入一个数构建一个新的版本
struct PersistentSegmentTree {
    vi tree;
    vi nums;
    vi left;
    vi right;
    vi root;
    int cnt, n;

    PersistentSegmentTree(vi& lst, int size) {
        tree.resize(MAXT);
        nums.resize(MAXN);
        left.resize(MAXT);
        right.resize(MAXT);
        root.resize(MAXN);
        cnt= 0;
        n= size;
        for (int i= 1; i <= size; i++) {
            nums[i]= lst[i];
        }
        root[0]= build(1, n);
    }

    int build(int l, int r) {
        int rt= ++cnt;
        if (l == r) {
            tree[rt]= nums[l];
        } else {
            int mid= (l + r) >> 1;
            left[rt]= build(l, mid);
            right[rt]= build(mid + 1, r);
        }
        return rt;
    }

    int update(int jobi, int jobv, int l, int r, int i) {
        int rt= ++cnt;
        left[rt]= left[i];
        right[rt]= right[i];
        tree[rt]= tree[i] + jobv;
        if (l < r) {
            int mid= (l + r) >> 1;
            if (jobi <= mid) {
                left[rt]= update(jobi, jobv, l, mid, left[i]);
            } else {
                right[rt]= update(jobi, jobv, mid + 1, r, right[i]);
            }
        }
        return rt;
    }

    int query(int jobk, int l, int r, int v1, int v2) {
        if (l == r) {
            return l;
        }
        int mid= (l + r) >> 1;
        int cur= tree[left[v2]] - tree[left[v1]];
        if (jobk <= cur) {
            return query(jobk, l, mid, left[v1], left[v2]);
        } else {
            return query(jobk - cur, mid + 1, r, right[v1], right[v2]);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vi arr(n + 1), nums(n + 1);
    for (int i= 1; i <= n; i++) {
        cin >> nums[i];
        arr[i]= nums[i];
    }

    sort(arr.begin() + 1, arr.begin() + n + 1);
    int size= 2;
    for (int i= 2; i <= n; i++) {
        if (arr[i] != arr[i - 1]) {
            arr[size]= arr[i];
            size++;
        }
    }
    size--;
    int idx;
    vi lst(size + 1, 0);
    PersistentSegmentTree st(lst, size);

    for (int i= 1; i <= n; i++) {
        idx= lower_bound(arr.begin() + 1, arr.begin() + size + 1, nums[i]) -
             arr.begin();
        st.root[i]= st.update(idx, 1, 1, size, st.root[i - 1]);
    }

    int l, r, k, left, right, ans, mid;
    for (int i= 1; i <= m; i++) {
        cin >> l >> r >> k;
        l--;
        ans= arr[st.query(k, 1, size, st.root[l], st.root[r])];
        cout << ans << endl;
    }
    return 0;
}
