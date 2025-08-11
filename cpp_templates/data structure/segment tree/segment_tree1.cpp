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

// https://www.luogu.com.cn/problem/P4145
// 有些信息看似不能用线段树维护，但此题的开平方对于每个数最多6次
// 可以维护当前区间最大值
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

    void update(int jobl, int jobr)
    {
        _update(jobl, jobr, 1, n, 1);
    }

    void _update(int jobl, int jobr, int l, int r, int i)
    {
        if (mx[i] == 1)
        {
            return;
        }
        if (l == r)
        {
            nums[l] = (ll)sqrt(nums[l]);
            sum[i] = nums[l];
            mx[i] = nums[l];
            return;
        }
        int mid = (l + r) >> 1;
        if (jobr <= mid)
        {
            _update(jobl, jobr, l, mid, i << 1);
        }
        else if (jobl >= mid + 1)
        {
            _update(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        else
        {
            _update(jobl, jobr, l, mid, i << 1);
            _update(jobl, jobr, mid + 1, r, i << 1 | 1);
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
    cin >> n;
    vll nums(n);
    for0(i, n)
    {
        cin >> nums[i];
    }
    SegmentTree st(nums);

    cin >> m;
    int k, l, r;
    int temp;
    for0(i, m)
    {
        cin >> k >> l >> r;
        if (l > r)
        {
            temp = l;
            l = r;
            r = temp;
        }
        if (k == 0)
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