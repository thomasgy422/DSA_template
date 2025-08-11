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

// mod at most logn times, so overall n * logn * logn
// https://codeforces.com/contest/438/problem/D
class SegmentTree
{
public:
    ll sum[400002];
    ll mx[400002];
    ll nums[100002];
    int n;
    SegmentTree(vll &lst)
    {
        memset(sum, 0, sizeof(sum));
        memset(mx, 0, sizeof(mx));
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
        mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
    }

    void buildTree(int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = nums[l];
            mx[i] = nums[l];
        }
        else
        {
            int mid = (l + r) >> 1;
            buildTree(l, mid, i << 1);
            buildTree(mid + 1, r, i << 1 | 1);
            up(i);
        }
    }

    void update(int jobi, int jobv)
    {
        _update(jobi, jobv, 1, n, 1);
    }

    void _update(int jobi, int jobv, int l, int r, int i)
    {
        if (l == r && l == jobi)
        {
            nums[l] = jobv;
            sum[i] = nums[l];
            mx[i] = nums[l];
            return;
        }

        int mid = (l + r) >> 1;
        if (jobi <= mid)
        {
            _update(jobi, jobv, l, mid, i << 1);
        }
        else
        {
            _update(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }

    void mod(int jobl, int jobr, int jobv)
    {
        _mod(jobl, jobr, jobv, 1, n, 1);
    }

    void _mod(int jobl, int jobr, int jobv, int l, int r, int i)
    {
        if (mx[i] < jobv)
        {
            return;
        }
        if (l == r)
        {
            nums[l] = nums[l] % jobv;
            sum[i] = nums[l];
            mx[i] = nums[l];
            return;
        }
        int mid = (l + r) >> 1;
        if (jobr <= mid)
        {
            _mod(jobl, jobr, jobv, l, mid, i << 1);
        }
        else if (jobl >= mid + 1)
        {
            _mod(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        else
        {
            _mod(jobl, jobr, jobv, l, mid, i << 1);
            _mod(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
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
    vll nums(n);
    for0(i, n)
    {
        cin >> nums[i];
    }
    SegmentTree st(nums);

    int k, l, r, x;
    int op;
    for0(i, m)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> l >> r;
            cout << st.query(l, r) << endl;
        }
        else if (op == 2)
        {
            cin >> l >> r >> x;
            st.mod(l, r, x);
        }
        else
        {
            cin >> k >> x;
            st.update(k, x);
        }
    }
    return 0;
}

/*
    1. 2 3 4 5
    1  2 3 0 1
*/