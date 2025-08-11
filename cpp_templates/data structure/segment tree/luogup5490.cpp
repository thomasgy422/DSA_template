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

class SegmentTree
{
public:
    vll sum;
    int n;
    SegmentTree(int m)
    {
        n = m + 1;
        sum.resize(n << 2);
    }

    void up(int i)
    {
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }

    void buildTree(int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = 0;
        }
        else
        {
            int mid = (l + r) >> 1;
            buildTree(l, mid, i << 1);
            buildTree(mid + 1, r, i << 1 | 1);
            up(i);
        }
    }

    void update(int jobl, int jobr, int jobv, int l, int r, int i)
    {
        if (jobl <= l && r <= jobr)
        {
            sum[i] += (r - l + 1) * jobv;
        }
        else
        {
            int mid = (l + r) >> 1;
            if (jobl <= mid) {
                update(jobl, jobr, jobv, l, mid, i << 1);
            }
            if (jobr > r) {
                update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }
            up(i);
        }
    }

    ll query()
    {
        return sum[1];
    }
};

int main()
{
    int n;
    cin >> n;
    int a, b, c, d;
    vvll lst;
    vll nums;
    for0(i, n)
    {
        cin >> a >> b >> c >> d;
        lst.pb({a, b, d, 1});
        lst.pb({c, b, d, -1});
        nums.pb(b);
        nums.pb(d);
    }

    sort(nums.begin(), nums.end());
    int size = 1;
    int m = sz(nums);
    for (int i = 1; i < m; i++)
    {
        if (nums[i] == nums[i - 1])
        {
            continue;
        }
        nums[size++] = nums[i];
    }

    vll newnums;
    for0(i, size) {
        newnums.pb(nums[i]);
    }
    newnums.pb(nums[size-1]);
    size++;

    sort(lst.begin(), lst.end(), [](const vll& a, const vll& b) {
        return a[0] < b[0];
    });
    nums = newnums;
    SegmentTree st(size);
    int h;
    int low, hi;
    int prev = lst[0][0];
    ll ans = 0;
    for(int i = 0; i < sz(lst); i++) {
        vll &cur = lst[i];
        low = lower_bound(nums.begin(), nums.end(), cur[1]) - nums.begin() + 1;
        hi = lower_bound(nums.begin(), nums.end(), cur[2]) - nums.begin() + 1;
        if (prev == cur[0]) {
            st.update(low, hi, cur[3], 1, size, 1);
        } else {
            h = st.query();
            cout << cur[0] << " " << prev << " " << h << endl;
            ans += (cur[0] - prev) * h;
            st.update(low, hi, cur[3], 1, size, 1);
            prev = cur[0];
        }
    }
    cout << ans << endl;
    return 0;
}


/*

100 150 200 255

100 100 200 1
150 150 255 1
200 100 200 -1
250 150 255 -1


*/