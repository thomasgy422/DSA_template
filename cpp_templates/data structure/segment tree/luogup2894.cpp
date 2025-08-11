#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <stack>
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

const int mx = 50002;

// https://www.luogu.com.cn/problem/P2894
class SegmentTree
{
public:
    vi nums, len, pre, suf, change;
    vector<bool> upd;
    int n;
    SegmentTree(vi &lst)
    {
        n = sz(lst);
        nums.resize(mx);
        len.resize(mx << 2);
        pre.resize(mx << 2);
        suf.resize(mx << 2);
        upd.resize(mx << 2);
        change.resize(mx << 2);
        for0(i, n)
        {
            nums[i + 1] = lst[i];
        }
        buildTree(1, n, 1);
    }

    void up(int i, int ln, int rn)
    {
        int l = i << 1;
        int r = i << 1 | 1;
        len[i] = max(max(len[l], len[r]), suf[l] + pre[r]);
        pre[i] = (len[l] < ln) ? pre[l] : (pre[l] + pre[r]);
        suf[i] = (len[r] < rn) ? suf[r] : (suf[l] + suf[r]);
    }

    void lazy(int i, int jobv, int n)
    {
        len[i] = pre[i] = suf[i] = (jobv == 1) ? 0 : n;
        change[i] = jobv;
        upd[i] = true;
    }

    void down(int i, int ln, int rn)
    {
        if (upd[i])
        {
            lazy(i << 1, change[i], ln);
            lazy(i << 1 | 1, change[i], rn);
        }
        upd[i] = false;
    }

    void buildTree(int l, int r, int i)
    {
        if (l == r)
        {
            len[i] = pre[i] = suf[i] = 1;
        }
        else
        {
            int mid = (l + r) >> 1;
            buildTree(l, mid, i << 1);
            buildTree(mid + 1, r, i << 1 | 1);
            up(i, mid - l + 1, r - mid);
        }
        upd[i] = false;
    }

    void update(int jobl, int jobr, int jobv, int l, int r, int i)
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
                update(jobl, jobr, jobv, l, mid, i << 1);
            }
            if (jobr > mid)
            {
                update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }
            up(i, mid - l + 1, r - mid);
        }
    }

    int query(int jobv, int l, int r, int i)
    {
        if (l == r)
        {
            return l;
        }
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (len[i << 1] >= jobv)
        {
            return query(jobv, l, mid, i << 1);
        }

        if (suf[i << 1] + pre[i << 1 | 1] >= jobv)
        {
            return mid - suf[i << 1] + 1;
        }

        return query(jobv, mid + 1, r, i << 1 | 1);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vi nums(n);
    SegmentTree st(nums);
    int op, l, r, x;
    for0(i, m)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> x;
            if (st.len[1] < x)
            {
                cout << 0 << endl;
                continue;
            }
            l = st.query(x, 1, n, 1);
            st.update(l, l + x - 1, 1, 1, n, 1);
            cout << l << endl;
        }
        else
        {
            cin >> l >> r;
            st.update(l, min(n, l + r - 1), 0, 1, n, 1);
        }
    }
    return 0;
}

/*
    1 1 1 0 1 1 1 1
*/
