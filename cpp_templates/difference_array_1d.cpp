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

int main()
{
    DifferenceArray df;
    df.set(2, 6, 1, 5, 1);
    df.calc();
    return 0;
}