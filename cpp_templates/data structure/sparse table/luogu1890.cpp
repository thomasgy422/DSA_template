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

const int LIMIT = 10;
const int MX = 1001;

int st[MX][LIMIT];

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vi nums(n);
    for0(i, n)
    {
        cin >> nums[i];
        st[i][0] = nums[i];
    }

    int pow = (int)floor(log2(n));

    for (int p = 1; p <= pow; p++)
    {
        for (int i = 0; i < n; i++)
        {
            if (i + (1 << p - 1) < n)
                st[i][p] = gcd(st[i][p - 1], st[i + (1 << p - 1)][p - 1]);
            else
                st[i][p] = st[i][p - 1];
        }
    }

    int l, r, d;
    int ans;

    for0(i, m)
    {
        cin >> l >> r;
        l--;
        r--;
        d = (int)floor(log2(r - l + 1));
        ans = gcd(st[l][d], st[r - (1 << d) + 1][d]);
        cout << ans << endl;
    }
}