#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <cmath>

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

// https://www.luogu.com.cn/problem/P3870
class SegmentTree
{
public:
    ll sum[400002];
    // 表示当前区间是否被反转
    ll reverse[400002];
    ll nums[100002];
    int n;
    SegmentTree(vll &lst)
    {
        n = sz(lst);
        nums[0] = 0;
        for0(i, n)
        {
            nums[i + 1] = lst[i];
        }
        buildTree(1, n, 1);
    }

    void up(int i)
    {
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }

    void down(int i, int ln, int rn)
    {
        if (reverse[i])
        {
            lazy(i << 1, ln);
            lazy(i << 1 | 1, rn);
            reverse[i] = 0;
        }
    }

    void lazy(int i, ll len)
    {
        sum[i] = len - sum[i];
        reverse[i] ^= 1;
    }

    void buildTree(int l, int r, int i)
    {
        if (l == r)
        {
            nums[l] = 0;
        }
        else
        {
            int mid = (l + r) >> 1;
            buildTree(l, mid, i << 1);
            buildTree(mid + 1, r, i << 1 | 1);
            up(i);
        }
        reverse[i] = 0;
    }

    void update(int jobl, int jobr)
    {
        _update(jobl, jobr, 1, n, 1);
    }

    void _update(int jobl, int jobr, int l, int r, int i)
    {
        if (jobl <= l && jobr >= r)
        {
            lazy(i, r - l + 1);
        }
        else
        {
            int mid = (l + r) >> 1;
            down(i, mid - l + 1, r - mid);
            if (jobl <= mid)
            {
                _update(jobl, jobr, l, mid, i << 1);
            }
            if (jobr > mid)
            {
                _update(jobl, jobr, mid + 1, r, i << 1 | 1);
            }
            up(i);
        }
    }

    ll query(int jobl, int jobr)
    {
        return _query(jobl, jobr, 1, n, 1);
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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    int op, l, r;
    vll nums(n);

    SegmentTree st(nums);
    for0(i, m)
    {
        cin >> op >> l >> r;
        if (op == 0)
        {
            st.update(l, r);
        }
        else
        {
            cout << st.query(l, r) << endl;
        }
    }
    return 0;
}

/*
 */
