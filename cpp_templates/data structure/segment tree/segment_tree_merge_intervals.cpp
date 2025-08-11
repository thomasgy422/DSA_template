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

const int mx = 100002;

// 合并区间模版题
// https://www.luogu.com.cn/problem/P2572
class SegmentTree
{
public:
    vector<int> nums, sum, len0, pre0, suf0, len1, pre1, suf1, change;
    vector<bool> reverse, update;
    int n;
    SegmentTree(vi &lst)
    {
        n = sz(lst);
        nums.resize(mx);
        sum.resize(mx << 2);
        len0.resize(mx << 2);
        pre0.resize(mx << 2);
        suf0.resize(mx << 2);
        len1.resize(mx << 2);
        pre1.resize(mx << 2);
        suf1.resize(mx << 2);
        reverse.resize(mx << 2);
        update.resize(mx << 2);
        change.resize(mx << 2);
        for0(i, n)
        {
            nums[i + 1] = lst[i];
        }
        buildTree(1, n, 1);
    }

    void lazyupdate(int i, int v, int len)
    {
        sum[i] = v * len;
        len0[i] = pre0[i] = suf0[i] = (v == 0) ? len : 0;
        len1[i] = pre1[i] = suf1[i] = (v == 1) ? len : 0;
        change[i] = v;
        update[i] = true;
        reverse[i] = false;
    }

    void lazyreverse(int i, int len)
    {
        sum[i] = len - sum[i];
        int tmp;
        tmp = len0[i];
        len0[i] = len1[i];
        len1[i] = tmp;
        tmp = pre0[i];
        pre0[i] = pre1[i];
        pre1[i] = tmp;
        tmp = suf0[i];
        suf0[i] = suf1[i];
        suf1[i] = tmp;
        reverse[i] = !reverse[i];
    }

    void down(int i, int ln, int rn)
    {
        // 先更新update，因为会覆盖所有之前未处理的reverse操作
        // 清空当前节点update并传给孩子
        if (update[i])
        {
            lazyupdate(i << 1, change[i], ln);
            lazyupdate(i << 1 | 1, change[i], rn);
            update[i] = false;
        }
        if (reverse[i])
        {
            lazyreverse(i << 1, ln);
            lazyreverse(i << 1 | 1, rn);
            reverse[i] = false;
        }
    }

    // 维护左右的最长，前缀，后缀，子数组和
    void up(int i, int ln, int rn)
    {
        int l = i << 1;
        int r = i << 1 | 1;
        sum[i] = sum[l] + sum[r];
        len0[i] = max(max(len0[l], len0[r]), suf0[l] + pre0[r]);
        pre0[i] = (len0[l] < ln) ? pre0[l] : (pre0[l] + pre0[r]);
        suf0[i] = (len0[r] < rn) ? suf0[r] : (suf0[l] + suf0[r]);
        len1[i] = max(max(len1[l], len1[r]), suf1[l] + pre1[r]);
        pre1[i] = (len1[l] < ln) ? pre1[l] : (pre1[l] + pre1[r]);
        suf1[i] = (len1[r] < rn) ? suf1[r] : (suf1[l] + suf1[r]);
    }

    void buildTree(int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = nums[l];
            len0[i] = pre0[i] = suf0[i] = (nums[l] == 0) ? 1 : 0;
            len1[i] = pre1[i] = suf1[i] = (nums[l] == 1) ? 1 : 0;
        }
        else
        {
            int mid = (l + r) >> 1;
            buildTree(l, mid, i << 1);
            buildTree(mid + 1, r, i << 1 | 1);
            up(i, mid - l + 1, r - mid);
        }
        reverse[i] = false;
        update[i] = false;
    }

    void _update(int jobl, int jobr, int jobv, int l, int r, int i)
    {
        if (jobl <= l && jobr >= r)
        {
            lazyupdate(i, jobv, r - l + 1);
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
            up(i, mid - l + 1, r - mid);
        }
    }

    void _reverse(int jobl, int jobr, int l, int r, int i)
    {
        if (jobl <= l && jobr >= r)
        {
            lazyreverse(i, r - l + 1);
        }
        else
        {
            int mid = (l + r) >> 1;
            down(i, mid - l + 1, r - mid);
            if (jobl <= mid)
            {
                _reverse(jobl, jobr, l, mid, i << 1);
            }

            if (jobr > mid)
            {
                _reverse(jobl, jobr, mid + 1, r, i << 1 | 1);
            }
            up(i, mid - l + 1, r - mid);
        }
    }

    int querysum(int jobl, int jobr, int l, int r, int i)
    {
        if (jobl <= l && jobr >= r)
        {
            return sum[i];
        }

        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        int ans = 0;
        if (jobl <= mid)
        {
            ans += querysum(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid)
        {
            ans += querysum(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        return ans;
    }

    vi query(int jobl, int jobr, int l, int r, int i)
    {
        if (jobl <= l && jobr >= r)
        {
            return {len1[i], pre1[i], suf1[i]};
        }
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        int ans = 0;
        if (jobr <= mid)
        {
            return query(jobl, jobr, l, mid, i << 1);
        }

        if (jobl > mid)
        {
            return query(jobl, jobr, mid + 1, r, i << 1 | 1);
        }

        vi lr = query(jobl, jobr, l, mid, i << 1);
        vi rr = query(jobl, jobr, mid + 1, r, i << 1 | 1);
        int lenl = lr[0];
        int prel = lr[1];
        int sufl = lr[2];
        int lenr = rr[0];
        int prer = rr[1];
        int sufr = rr[2];
        int lenret = max(max(lenl, lenr), sufl + prer);
        int preret = (lenl < mid - max(l, jobl) + 1) ? prel : (prel + prer);
        int sufret = (lenr < min(r, jobr) - mid) ? sufr : (sufl + sufr);
        return {lenret, preret, sufret};
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vi nums(n);
    for0(i, n)
    {
        cin >> nums[i];
    }
    SegmentTree st(nums);
    int op, l, r;
    for0(i, m)
    {
        cin >> op >> l >> r;
        l++;
        r++;
        if (op == 0)
        {
            st._update(l, r, 0, 1, n, 1);
        }
        else if (op == 1)
        {
            st._update(l, r, 1, 1, n, 1);
        }
        else if (op == 2)
        {
            st._reverse(l, r, 1, n, 1);
        }
        else if (op == 3)
        {
            cout << st.querysum(l, r, 1, n, 1) << endl;
        }
        else
        {
            vi ret = st.query(l, r, 1, n, 1);
            cout << ret[0] << endl;
        }
    }
    return 0;
}
