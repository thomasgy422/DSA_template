#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

#define for0(i, n) for (int i = 0; i < (int)(n); ++i)            // 0 based indexing
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)           // 1 based indexing
#define forc(i, l, r) for (int i = (int)(l); i <= (int)(r); ++i) // closed interval from l to r inclusive

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

const int LIMIT = 17;
const int MX = 100001;

int st[MX][LIMIT];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, cur, prev;
    cin >> n >> m;

    vi nums(n);
    vi left(n);
    vi lst;

    int idx = 0;

    cin >> prev;
    nums[0] = prev;
    left[0] = 0;
    cur = 1;
    for1(i, n - 1)
    {
        cin >> nums[i];
        if (nums[i] == prev)
        {
            cur++;
            left[i] = idx;
        }
        else
        {
            idx = i;
            lst.pb(cur);
            cur = 1;
            prev = nums[i];
            left[i] = idx;
        }
    }
    lst.pb(cur);

    vi pre;
    pre.pb(0);
    for0(i, sz(lst))
    {
        pre.pb(pre[sz(pre) - 1] + lst[i]);
    }

    for0(i, sz(lst)) {
        st[i][0] = lst[i];
    }

    int pow = (int) floor(log2(sz(lst)));

    for(int p = 1; p <= pow; p++) {
        for(int i = 0; i < sz(lst); i++) {
            if (i + (1 << p - 1) < sz(lst))
                st[i][p] = max(st[i][p - 1], st[i + (1 << p - 1)][p - 1]);
            else
                st[i][p] = st[i][p - 1];
        }
    }

    int l, r;
    for0(i, m) {
        cin >> l >> r;
        l--;
        r--;
        if (nums[l] == nums[r])
            cout << r - l + 1 << endl;
            continue;
        
        
    }
}

/*

    2 3
    1 10
    5 10
    0


*/
