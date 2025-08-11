#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <cstring>
#include <cstdlib>

#define for0(i, n) for (int i = 0; i < (int)(n); ++i)            // 0 based indexing
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)           // 1 based indexing
#define forc(i, l, r) for (int i = (int)(l); i <= (int)(r); ++i) // closed interver from l to r r inclusive
#define forr0(i, n) for (int i = (int)(n) - 1; i >= 0; --i)      // reverse 0 based.
#define forr1(i, n) for (int i = (int)(n); i >= 1; --i)          // reverse 1 based

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

// lazy propagation segment tree
// https://www.luogu.com.cn/problem/P3372
class SegmentTree
{
public:
    ll sum[500002];
    ll add[500002];
    ll nums[100002];
    int size;

    SegmentTree(vll &lst)
    {
        memset(sum, 0, sizeof(sum));
        memset(add, 0, sizeof(add));
        size = sz(lst);
        for1(i, size)
        {
            nums[i] = lst[i - 1];
        }
        buildTree(1, size, 1);
    }

    // 当前节点add信息更新到child，并清空当前节点
    void down(int i, int ln, int rn)
    {
        if (add[i])
        {
            lazy(i << 1, add[i], ln);
            lazy(i << 1 | 1, add[i], rn);
            add[i] = 0;
        }
    }

    void lazy(int i, ll v, int n)
    {
        sum[i] += v * n;
        add[i] += v;
    }

    void maintain(int i)
    {
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }

    void buildTree(int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = nums[l];
        }
        else
        {
            int mid = (l + r) >> 1;
            buildTree(l, mid, i << 1);
            buildTree(mid + 1, r, i << 1 | 1);
            maintain(i);
        }
        add[i] = 0;
    }

    void update(int jobl, int jobr, ll jobv)
    {
        return _update(jobl, jobr, jobv, 1, size, 1);
    }

    void _update(int jobl, int jobr, ll jobv, int l, int r, int i)
    {
        if (jobl <= l && jobr >= r)
        {
            lazy(i, jobv, r - l + 1);
        }
        else
        {
            int mid = (l + r) >> 1;
            down(i, mid - l + 1, r - mid);
            if (jobl <= mid)
            {
                _update(jobl, jobr, jobv, l, mid, i << 1);
            }
            if (jobr > mid)
            {
                _update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }
            maintain(i);
        }
    }

    ll query(int jobl, int jobr)
    {
        return _query(jobl, jobr, 1, size, 1);
    }

    ll _query(int jobl, int jobr, int l, int r, int i)
    {
        if (jobl <= l && jobr >= r)
        {
            return sum[i];
        }
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        ll ans = 0;
        if (jobl <= mid)
        {
            ans += _query(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid)
        {
            ans += _query(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        return ans;
    }
};

// binary search
class SegmentTree1
{
public:
    ll sum[400002];
    ll nums[100002];
    int size;

    SegmentTree1(vi &lst)
    {
        memset(sum, 0, sizeof(sum));
        size = sz(lst);
        for1(i, size)
        {
            nums[i] = lst[i - 1];
        }
        buildTree(1, size, 1);
    }

    void maintain(int i)
    {
        sum[i] = max(sum[i << 1], sum[i << 1 | 1]);
    }

    void buildTree(int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = nums[l];
        }
        else
        {
            int mid = (l + r) >> 1;
            buildTree(l, mid, i << 1);
            buildTree(mid + 1, r, i << 1 | 1);
            maintain(i);
        }
    }

    int query(int jobv)
    {
        return _query(jobv, 1, size, 1);
    }

    // find the leftmost that satisfy the constraint
    int _query(int jobv, int l, int r, int i)
    {
        if (sum[i] < jobv)
            return -1;
        if (l == r)
        {
            sum[i] = -1;
            return l;
        }
        int mid = (l + r) >> 1;
        int ret = _query(jobv, l, mid, i << 1);
        if (ret == -1)
        {
            ret = _query(jobv, mid + 1, r, i << 1 | 1);
        }
        maintain(i);
        return ret;
    }
};

// https://leetcode.com/problems/fruits-into-baskets-iii/description/
class Leetcode3479
{
public:
    int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets)
    {
        SegmentTree1 st(baskets);
        int n = sz(fruits);
        int ans = 0;
        for0(i, n)
        {
            if (st.query(fruits[i]) == -1)
                ans++;
        }
        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vll nums(n);
    for0(i, n)
    {
        cin >> nums[i];
    }
    SegmentTree st(nums);
    int x, y;
    ll k;
    int op;
    for0(i, m)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> x >> y >> k;
            st.update(x, y, k);
        }
        else
        {
            cin >> x >> y;
            cout << st.query(x, y) << endl;
        }
    }
    return 0;
}