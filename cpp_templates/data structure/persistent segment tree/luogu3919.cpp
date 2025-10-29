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
const int MAXN= 1000002;
const int MAXT= MAXN * 23;

int tree[MAXT], leftChild[MAXT], rightChild[MAXT], root[MAXN];
int cnt;

int build(vector<int>& nums, int l, int r) {
    int rt= ++cnt;
    if (l == r) {
        tree[rt]= nums[l];
        return rt;
    }
    int mid= (l + r) / 2;
    leftChild[rt]= build(nums, l, mid);
    rightChild[rt]= build(nums, mid + 1, r);
    return rt;
}

int update(int pos, int val, int l, int r, int pre) {
    int rt= ++cnt;
    leftChild[rt]= leftChild[pre];
    rightChild[rt]= rightChild[pre];
    tree[rt]= tree[pre];
    if (l == r) {
        tree[rt]= val;
        return rt;
    }
    int mid= (l + r) / 2;
    if (pos <= mid)
        leftChild[rt]= update(pos, val, l, mid, leftChild[rt]);
    else
        rightChild[rt]= update(pos, val, mid + 1, r, rightChild[rt]);
    return rt;
}

int query(int pos, int l, int r, int rt) {
    if (l == r) return tree[rt];
    int mid= (l + r) / 2;
    if (pos <= mid)
        return query(pos, l, mid, leftChild[rt]);
    else
        return query(pos, mid + 1, r, rightChild[rt]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> nums(n + 1);
    for (int i= 1; i <= n; i++) cin >> nums[i];

    cnt= 0;
    root[0]= build(nums, 1, n);

    for (int i= 1; i <= m; i++) {
        int v, op;
        cin >> v >> op;
        if (op == 1) {
            int p, c;
            cin >> p >> c;
            root[i]= update(p, c, 1, n, root[v]);
        } else {
            int p;
            cin >> p;
            root[i]= root[v];
            cout << query(p, 1, n, root[v]) << '\n';
        }
    }
}
