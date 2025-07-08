#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

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

/*
 negative number with two's complement, invert all bits and add 1 to result, high bit is sign bit.
 range of int: -2,147,483,648 to 2,147,483,647
 10000000 00000000 00000000 00000000               01111111 11111111 11111111 11111111
*/

// (a ^ p) % p modular exponentiation
void power()
{
    int a, b, p;
    cin >> a >> b >> p;
    int ans = 1 % p; // if p == 1 then always 0;
    while (b > 0)
    {
        if (b & 1)
        {
            ans = (ll)ans * a % p; // assign ll to int if it's within the range of int
        }
        a = (ll)a * a % p;
        b >>= 1;
    }
    cout << ans;
}

// (a*b) % p, b into binary format;
void acwing90()
{
    ll a, b, p;
    cin >> a >> b >> p;

    ll ans = 0;

    for (; b; b >>= 1)
    {
        if (b & 1)
        {
            ans = (ll)(ans + a) % p;
        }
        a = (ll)a * 2 % p;
    }

    cout << ans;
}

int calc(int idx, int b, vi &nums, vector<string> &s)
{
    int res = b;
    for0(i, sz(nums))
    {
        int x = (nums[i] >> idx) & 1;
        if (s[i] == "AND")
        {
            res &= x;
        }
        else if (s[i] == "OR")
        {
            res |= x;
        }
        else
        {
            res ^= x;
        }
    }
    return res;
}

// https://www.acwing.com/problem/content/1000/
//  from highest bit to lower bit, try to set each bit of answer to 1.
void acwing998()
{
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    vi nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i] >> nums[i];
    }
    int ans = 0;
    int val = 0;
    for (int i = 30; i >= 0; i--)
    {
        int a = calc(i, 1, nums, s);
        int b = calc(i, 0, nums, s);
        if ((val + (1 << i) <= m) && a == 1 && b == 0)
        {
            val += (1 << i);
            ans += (1 << i);
        }
        else if (b == 1)
        {
            ans += (1 << i);
        }
    }
    cout << ans;
}


// lowbit: 1010 -> 0101 -> 0110 -> 0110 & 1010 = 0010
// lowbit(n)= n&(~n +1)= n&(-n)