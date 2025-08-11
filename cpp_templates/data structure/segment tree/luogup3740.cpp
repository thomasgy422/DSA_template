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

// https://www.luogu.com.cn/problem/P3740
class SegmentTree
{
public:
    ll mx[20000];
    ll add[20000];
    ll nums[5000];
    int n;
    SegmentTree(vll &lst)
    {
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
        mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
    }

    void down(int i)
    {
        if (add[i])
        {
            lazy(i << 1, add[i]);
            lazy(i << 1 | 1, add[i]);
            add[i] = 0;
        }
    }

    void lazy(int i, ll v)
    {
        mx[i] = max(mx[i], v);
        add[i] = max(add[i], v);
    }

    void buildTree(int l, int r, int i)
    {
        if (l == r)
        {
            mx[i] = nums[l];
        }
        else
        {
            int mid = (l + r) >> 1;
            buildTree(l, mid, i << 1);
            buildTree(mid + 1, r, i << 1 | 1);
            up(i);
        }
        add[i] = 0;
    }

    void update(int jobl, int jobr, int jobv)
    {
        _update(jobl, jobr, jobv, 1, n, 1);
    }

    void _update(int jobl, int jobr, int jobv, int l, int r, int i)
    {
        if (jobl <= l && jobr >= r)
        {
            lazy(i, jobv);
        }
        else
        {
            int mid = (l + r) >> 1;
            down(i);
            if (jobl <= mid)
            {
                _update(jobl, jobr, jobv, l, mid, i << 1);
            }
            if (jobr > mid)
            {
                _update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
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
            return mx[i];
        }

        int mid = (l + r) >> 1;
        down(i);
        ll ans = 0;
        if (jobl <= mid)
        {
            ans = max(ans, _query(jobl, jobr, l, mid, i << 1));
        }
        if (jobr > mid)
        {
            ans = max(ans, _query(jobl, jobr, mid + 1, r, i << 1 | 1));
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
    vvll p;
    ll l, r;
    vll nums;
    for1(i, m)
    {
        cin >> l >> r;
        if (l > n)
            continue;
        if (r > n)
            r = n;
        nums.pb(l);
        nums.pb(r);
        p.pb({l, r, i});
    }
    nums.pb(n);

    sort(nums.begin(), nums.end());
    int size = 1;
    for1(i, sz(nums) - 1)
    {
        if (nums[i] == nums[i - 1])
            continue;
        nums[size++] = nums[i];
    }

    vll idx;
    for (int i = 0; i < size; i++)
    {
        if (i + 1 < size && nums[i] + 1 < nums[i + 1])
        {
            idx.pb(nums[i]);
            idx.pb(nums[i] + 1);
        }
        else
        {
            idx.pb(nums[i]);
        }
    }

    // for0(i, sz(idx)) {
    //     cout << idx[i] << endl;
    // }

    size = sz(idx);
    vll lst(size);
    SegmentTree st(lst);

    int lid, mid, rid;
    for (auto cur : p)
    {
        // cout << cur[0] << " " << cur[1] << endl;
        lid = lower_bound(idx.begin(), idx.begin() + size, cur[0]) - idx.begin() + 1;
        rid = lower_bound(idx.begin(), idx.begin() + size, cur[1]) - idx.begin() + 1;

        st.update(lid, rid, cur[2]);
    }

    ll ans;
    vll res(m + 1);
    for1(i, size)
    {
        ans = st.query(i, i);
        // cout << i << " " << ans << endl;
        if (ans > 0)
            res[ans]++;
    }
    int ret = 0;
    for1(i, m)
    {
        if (res[i] > 0)
            ret++;
    }
    cout << ret << endl;
    return 0;
}

/*
    1 2 3 4 6 7 8 10
    1 2 4 4 2 5 5 5
*/
