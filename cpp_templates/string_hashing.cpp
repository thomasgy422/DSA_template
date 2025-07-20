#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <cstdlib>
#include <ctime>

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
typedef unsigned long long ull;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef double ld;

// string hash template
// https://www.luogu.com.cn/problem/P3370
class P3370
{
public:
    int base = 499;
    void solve()
    {
        int n;
        cin >> n;
        vector<string> strs(n);
        for0(i, n)
        {
            cin >> strs[i];
        }
        vll nums(n);
        for0(i, n)
        {
            string cur = strs[i];
            ull ans = get(cur[0]);
            // a * base^3 + b * base^2 + c ^ base^1 + d * base^0
            for (int j = 1; j < sz(cur); j++)
            {
                ans = ans * base + get(cur[j]);
            }
            nums[i] = ans;
        }
        sort(nums.begin(), nums.end());
        int count = 1;
        for (int i = 1; i < n; i++)
        {
            if (nums[i] != nums[i - 1])
            {
                count++;
            }
        }
        cout << count << endl;
        return;
    }

    int get(char c)
    {
        if (c >= '0' && c <= '9')
        {
            return 53 + (c - '0');
        }
        else if (c >= 'a' && c <= 'z')
        {
            return 1 + (c - 'a');
        }
        else
        {
            return 27 + (c - 'A');
        }
    }
};

// use string hashing to get hash value of a substring in O(1)
// https://leetcode.com/problems/repeated-string-match/description/
class Leetcode686
{
public:
    int base = 499;
    ll MOD = 1e9 + 7;

    vll build(int len)
    {
        vll power(len + 1);
        power[0] = 1;
        for1(i, len)
        {
            power[i] = power[i - 1] * base;
            power[i] %= MOD;
        }
        return power;
    }

    // get value of substring
    ll get_hash(int l, int r, vll &hash, vll &power)
    {
        ll ans = hash[r];
        if (l > 0)
        {
            return (ll)(hash[r] - hash[l - 1] * power[r - l + 1] % MOD + MOD) % MOD;
        }
        return ans;
    }

    int repeatedStringMatch(string a, string b)
    {
        int n = sz(a);
        int m = sz(b);
        int k = (m + n - 1) / n;
        string s = a;
        for0(i, k + 1)
        {
            s += a;
        }

        ll ans = b[0] - 'a' + 1;
        for (int i = 1; i < m; i++)
        {
            ans = ans * base + (b[i] - 'a' + 1);
            ans %= MOD;
        }

        n = sz(s);
        vll hash(n + 1);
        ll cur = s[0] - 'a' + 1;
        hash[0] = cur;
        for (int i = 1; i < n; i++)
        {
            cur = cur * base + (s[i] - 'a' + 1);
            cur %= MOD;
            hash[i] = cur;
        }

        vll power = build(m);
        for (int i = m - 1; i < n; i++)
        {
            if (get_hash(i - m + 1, i, hash, power) == ans)
            {
                return (i < k * sz(a)) ? k : k + 1;
            }
        }
        return -1;
    }
};

int main()
{
    P3370 p3370;
    p3370.solve();
    return 0;
}