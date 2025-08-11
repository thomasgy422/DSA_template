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

// https://www.luogu.com.cn/problem/P2184
// 维护每个地雷开始和结束的位置，因为没次放置的是不同的地雷
class SegmentTree
{
public:
    ll start[400002];
    ll end[400002];
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
        start[i] = start[i << 1] + start[i << 1 | 1];
        end[i] = end[i << 1] + end[i << 1 | 1];
    }

    void buildTree(int l, int r, int i)
    {
        if (l == r)
        {
            nums[l] = 0;
            start[i] = 0;
            end[i] = 0;
        }
        else
        {
            int mid = (l + r) >> 1;
            buildTree(l, mid, i << 1);
            buildTree(mid + 1, r, i << 1 | 1);
            up(i);
        }
    }

    void update(int jobi, int f)
    {
        _update(jobi, 1, n, 1, f);
    }

    void _update(int jobi, int l, int r, int i, int f)
    {
        if (l == r && l == jobi)
        {
            if (f)
                end[i]++;
            else
                start[i]++;
        }
        else
        {
            int mid = (l + r) >> 1;
            if (jobi <= mid)
            {
                _update(jobi, l, mid, i << 1, f);
            }
            else
            {
                _update(jobi, mid + 1, r, i << 1 | 1, f);
            }
            up(i);
        }
    }

    ll query(int jobl, int jobr, int f)
    {
        return _query(jobl, jobr, 1, n, 1, f);
    }

    ll _query(int jobl, int jobr, int l, int r, int i, int f)
    {
        if (jobl <= l && jobr >= r)
        {
            if (f)
                return end[i];
            else
                return start[i];
        }

        int mid = (l + r) >> 1;
        ll ans = 0;
        if (jobl <= mid)
        {
            ans += _query(jobl, jobr, l, mid, i << 1, f);
        }
        if (jobr > mid)
        {
            ans += _query(jobl, jobr, mid + 1, r, i << 1 | 1, f);
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
    SegmentTree st(nums);

    int q, l, r;

    for0(i, m)
    {
        cin >> q >> l >> r;
        if (q == 1)
        {
            st.update(l, 0);
            st.update(r, 1);
        }
        else
        {
            if (l == 1)
            {
                cout << st.query(1, r, 0) << endl;
            }
            else
            {
                // 差分的思想，在【1，l-r】开始的 -【1，l-1】结束的
                cout << st.query(1, r, 0) - st.query(1, l - 1, 1) << endl;
            }
        }
    }

    return 0;
}