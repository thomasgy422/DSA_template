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

// https://www.luogu.com.cn/problem/P1503
class SegmentTree
{
public:
    vector<int> nums, len, pre, suf;
    int n;
    SegmentTree(vi &lst)
    {
        n = sz(lst);
        nums.resize(mx);
        len.resize(mx << 2);
        pre.resize(mx << 2);
        suf.resize(mx << 2);
        for0(i, n)
        {
            nums[i + 1] = lst[i];
        }
        buildTree(1, n, 1);
    }

    void up(int i, int ln, int rn, int mid)
    {
        int l = i << 1;
        int r = i << 1 | 1;
        bool f = false;
        if (nums[mid] == 1 && nums[mid] == nums[mid + 1])
            f = true;
        if (f)
        {
            len[i] = max(max(len[l], len[r]), (suf[l] + pre[r]));
            pre[i] = (len[l] < ln) ? pre[l] : (pre[l] + pre[r]);
            suf[i] = (len[r] < rn) ? suf[r] : (suf[l] + suf[r]);
        }
        else
        {
            len[i] = max(len[l], len[r]);
            pre[i] = pre[l];
            suf[i] = suf[r];
        }
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
            up(i, mid - l + 1, r - mid, mid);
        }
    }

    void _update(int jobi, int jobv, int l, int r, int i)
    {
        if (l == r && l == jobi)
        {
            nums[l] = jobv;
            if (jobv == 1)
            {
                len[i] = pre[i] = suf[i] = 1;
            }
            else
            {
                len[i] = pre[i] = suf[i] = 0;
            }
        }
        else
        {
            int mid = (l + r) >> 1;
            if (jobi <= mid)
            {
                _update(jobi, jobv, l, mid, i << 1);
            }
            else
            {
                _update(jobi, jobv, mid + 1, r, i << 1 | 1);
            }
            up(i, mid - l + 1, r - mid, mid);
        }
    }

    vi query(int jobl, int jobr, int l, int r, int i)
    {
        if (jobl <= l && jobr >= r)
        {
            return {len[i], pre[i], suf[i]};
        }
        int mid = (l + r) >> 1;
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
        bool f = false;
        if (nums[mid] == 1 && nums[mid] == nums[mid + 1])
            f = true;
        int lenret, preret, sufret;
        if (f)
        {
            lenret = max(max(lenl, lenr), sufl + prer);
            preret = (lenl < mid - max(l, jobl) + 1) ? prel : (prel + prer);
            sufret = (lenr < min(r, jobr) - mid) ? sufr : (sufl + sufr);
        }
        else
        {
            lenret = max(lenl, lenr);
            preret = prel;
            sufret = sufr;
        }

        return {lenret, preret, sufret};
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vi nums(n, 1);
    SegmentTree st(nums);
    int idx;
    char op;
    stack<int> stack;
    for0(i, m)
    {
        cin >> op;
        if (op == 'D')
        {
            cin >> idx;
            st._update(idx, 0, 1, n, 1);
            stack.push(idx);
        }
        else if (op == 'R')
        {
            if (!stack.empty())
            {
                idx = stack.top();
                stack.pop();
                st._update(idx, 1, 1, n, 1);
            }
        }
        else
        {
            cin >> idx;
            vi ret1 = st.query(1, idx, 1, n, 1);
            vi ret2 = st.query(idx, n, 1, n, 1);
            // 找到当前节点最长连续1，等同与找（1-idx最长后缀 + idx-n最长前缀 - 1）
            cout << max(0, ret1[2] + ret2[1] - 1) << endl;
        }
    }
    return 0;
}

//  1 1 0 1 0 0 1
