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

const int mx = 10;

// difference array with arithmetic progression
class DifferenceArray
{
public:
    int arr[mx];

    DifferenceArray()
    {
        memset(arr, 0, sizeof(arr));
    }

    /*

        st = 1, end = 5, d = 1, l = 2 r = 6
        0 1 2 3 4 5 6 7 8
        0 0 0 0 0 0 0 0  0
        0 0 1 0 0 0 0 -6 5
        0 0 1 1 1 1 1 -5 0
        0 0 1 2 3 4 5  0 0

        arr[l] += st
        arr[l + 1] += d - st
        arr[r + 1] -= d + e
        arr[r + 2] += e

    */
    void set(int l, int r, int st, int end, int d)
    {
        arr[l] += st;
        arr[l + 1] += d - st;
        arr[r + 1] -= d + end;
        arr[r + 2] += end;
    }

    void calc()
    {
        for (int i = 1; i < mx; i++)
        {
            arr[i] += arr[i - 1];
        }

        for (int i = 1; i < mx; i++)
        {
            arr[i] += arr[i - 1];
        }

        for0(i, mx)
        {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
};

// 2-D difference array with discretization
// https://leetcode.cn/problems/xepqZ5/description/
class LCP74
{
public:
    int get(vector<ll> &arr)
    {
        sort(arr.begin(), arr.end());
        int j = 1;
        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i] != arr[i - 1])
            {
                arr[j] = arr[i];
                j++;
            }
        }
        return j;
    }

    // find lower bound for the value
    int getp(vector<ll> &arr, ll v, int sz)
    {
        int ans = -1;
        int l = 0;
        int r = sz - 1;
        while (l <= r)
        {
            int mid = l + ((r - l) >> 1);
            if (arr[mid] >= v)
            {
                ans = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        return ans + 1;
    }

    int fieldOfGreatestBlessing(vector<vector<int>> &ff)
    {
        vector<ll> ox;
        vector<ll> oy;
        for (int i = 0; i < ff.size(); i++)
        {
            int x = ff[i][0];
            int y = ff[i][1];
            int r = ff[i][2];

            /* discretiation: x -> x * 2 - r, x * 2 + r
                              y -> y * 2 - r, y * 2 + r
            */
            ox.push_back((ll)(x << 1) - r);
            ox.push_back((ll)(x << 1) + r);
            oy.push_back((ll)(y << 1) - r);
            oy.push_back((ll)(y << 1) + r);
        }

        int sx = get(ox);
        int sy = get(oy);

        vector<vector<int>> diff(sx + 2, vector<int>(sy + 2));

        for (int i = 0; i < ff.size(); i++)
        {
            int x = ff[i][0];
            int y = ff[i][1];
            int c = ff[i][2];
            int l = getp(ox, (ll)(x << 1) - c, sx);
            int r = getp(ox, (ll)(x << 1) + c, sx);
            int d = getp(oy, (ll)(y << 1) - c, sy);
            int t = getp(oy, (ll)(y << 1) + c, sy);
            diff[l][d] += 1;
            diff[r + 1][t + 1] += 1;
            diff[l][t + 1] -= 1;
            diff[r + 1][d] -= 1;
        }
        int ans = 0;

        for (int i = 1; i < diff.size() - 1; i++)
        {
            for (int j = 1; j < diff[0].size() - 1; j++)
            {
                diff[i][j] += diff[i][j - 1] + diff[i - 1][j] - diff[i - 1][j - 1];
                if (diff[i][j] > ans)
                {
                    ans = diff[i][j];
                }
            }
        }
        return ans;
    }
};

int main()
{
    DifferenceArray df;
    df.set(2, 6, 1, 5, 1);
    df.calc();
    return 0;
}