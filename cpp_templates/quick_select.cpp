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
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef double ld;

// quickSort to find the kth smallest element with random
class QuickSelect
{
public:
    vi nums;
    int k;
    QuickSelect(vi &lst, int p)
    {
        nums = lst;
        k = p;
    }

    int quickSelect(vi &nums, int l, int r)
    {
        if (l > r)
        {
            return -1;
        }

        int idx = l + (rand() % (r - l + 1));
        int t = nums[idx];
        int j = l;
        int p = 0;
        for (int i = l; i <= r; i++)
        {
            if (nums[i] < t)
            {
                swap(nums, i, j);
                j++;
            }
            if (nums[i] == t)
            {
                p = i;
            }
        }
        swap(nums, j, p);
        if (j == k - 1)
        {
            return nums[j];
        }
        else if (j > k - 1)
        {
            return quickSelect(nums, l, j - 1);
        }
        return quickSelect(nums, j + 1, r);
    }

    void swap(vi &nums, int i, int j)
    {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    int solve()
    {
        int n = sz(nums);
        return quickSelect(nums, 0, n - 1);
    }
};

int main()
{
    vi nums = {4, 5, 3, 6, 7, 3, 4, 5};
    QuickSelect solver(nums, 8);
    cout << solver.solve();
    return 0;
}

/*

*/
