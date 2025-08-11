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

// mx = 2 * m * log n
const int mx = 80002;

// 动态开点线段树模版题
// https://www.luogu.com.cn/problem/P2781
class SegmentTree
{
public:
    vll sum, add;
    vi left, right;
    // 根据需要创建新节点
    int cnt = 1;
    int n;
    SegmentTree(int in)
    {
        n = in;
        sum.resize(mx);
        add.resize(mx);
        left.resize(mx);
        right.resize(mx);
    }

    void up(int i, int l, int r)
    {
        sum[i] = sum[l] + sum[r];
    }

    void lazy(int i, ll jobv, int n)
    {
        sum[i] += n * jobv;
        add[i] += jobv;
    }

    void down(int i, int ln, int rn)
    {
        if (add[i] != 0)
        {
            if (left[i] == 0)
            {
                left[i] = ++cnt;
            }

            if (right[i] == 0)
            {
                right[i] = ++cnt;
            }

            lazy(left[i], add[i], ln);
            lazy(right[i], add[i], rn);
            add[i] = 0;
        }
    }

    void _add(int jobl, int jobr, ll jobv, int l, int r, int i)
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
                if (left[i] == 0)
                {
                    left[i] = ++cnt;
                }
                _add(jobl, jobr, jobv, l, mid, left[i]);
            }

            if (jobr > mid)
            {
                if (right[i] == 0)
                {
                    right[i] = ++cnt;
                }
                _add(jobl, jobr, jobv, mid + 1, r, right[i]);
            }
            up(i, left[i], right[i]);
        }
    }

    ll query(int jobl, int jobr, int l, int r, int i)
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
            if (left[i] != 0)
            {
                ans += query(jobl, jobr, l, mid, left[i]);
            }
        }
        if (jobr > mid)
        {
            if (right[i] != 0)
            {
                ans += query(jobl, jobr, mid + 1, r, right[i]);
            }
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
    SegmentTree st(n);
    int op, l, r;
    ll k;
    for0(i, m)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> l >> r >> k;
            st._add(l, r, k, 1, n, 1);
        }
        else
        {
            cin >> l >> r;
            cout << st.query(l, r, 1, n, 1) << endl;
        }
    }
    return 0;
}