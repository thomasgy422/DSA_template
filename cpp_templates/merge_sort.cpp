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
    master theorem to estimate time complexity of recursion program
    T(n) = a * T(n/b) + O(n^c)

    if log(b, a) < c, O(n^c)
    if log(b, a) > c, O(n*log(b, a))
    if log(b, a) == c, O(n^c*logn)

*/

vi helper(10001);

void merge(vi &nums, int l, int mid, int r)
{
    int i = l;
    int j = mid + 1;
    int k = l;
    while (i <= mid && j <= r)
    {
        if (nums[i] <= nums[j])
            helper[k++] = nums[i++];
        else
            helper[k++] = nums[j++];
    }

    while (i <= mid)
    {
        helper[k++] = nums[i++];
    }

    while (j <= r)
    {
        helper[k++] = nums[j++];
    }

    for (int i = l; i <= r; i++)
    {
        nums[i] = helper[i];
    }
}

// recursive
void mergeSort(vi &nums, int l, int r)
{
    if (l == r)
    {
        return;
    }
    int mid = l + (r - l) / 2;
    mergeSort(nums, l, mid);
    mergeSort(nums, mid + 1, r);
    merge(nums, l, mid, r);
}

// iterative implementation
void mergeSortIt(vi &nums)
{
    int n = sz(nums);
    for (int size = 1; size < n; size <<= 1)
    {
        int l = 0;
        int m;
        int r;
        while (l < n)
        {
            m = l + size - 1;
            if (m + 1 >= n)
            {
                break;
            }
            r = min(m + size, n - 1);
            merge(nums, l, m, r);
            l = r + 1;
        }
    }
}

/*
    merge sort and divide conquer

    left part + right part +  the contribution of left part to right part
    consider whether ans can be updated when we have two sorted lists.
*/
// example: https://www.nowcoder.com/practice/edfe05a1d45c4ea89101d936cac32469?tab=note

class SumOfSmallers
{
public:
    ll ans = 0;
    vi nums;
    SumOfSmallers(vi &lst)
    {
        nums = lst;
    }
    void merge1(int l, int m, int r)
    {
        int i = l;
        int sum = 0;
        for (int j = m + 1; j <= r; j++)
        {
            while (i <= m && nums[i] <= nums[j])
            {
                sum += nums[i];
                i++;
            }
            ans += sum;
        }
        i = l;
        int k = l;
        int j = m + 1;
        while (i <= m && j <= r)
        {
            if (nums[i] <= nums[j])
            {
                helper[k++] = nums[i++];
            }
            else
            {
                helper[k++] = nums[j++];
            }
        }

        while (i <= m)
        {
            helper[k++] = nums[i++];
        }

        while (j <= r)
        {
            helper[k++] = nums[j++];
        }

        for (int i = l; i <= r; i++)
        {
            nums[i] = helper[i];
        }
    }

    void get_count(int l, int r)
    {
        if (l == r)
        {
            return;
        }
        int m = l + (r - l) / 2;
        get_count(l, m);
        get_count(m + 1, r);
        merge1(l, m, r);
    }

    void solve()
    {
        int n = sz(nums);
        get_count(0, n - 1);
        cout << ans << "\n";
    }
};

// merge sort can be used to count the number of inversion pairs in a list
// example: https://leetcode.com/problems/reverse-pairs/
class ReversePairs
{
public:
    ll ans = 0;
    vi nums;
    ReversePairs(vi &lst)
    {
        nums = lst;
    }

    void merge1(int l, int m, int r)
    {
        int i = l;
        for (int j = m + 1; j <= r; j++)
        {
            while (i <= m && nums[i] <= 2 * nums[j])
            {
                i++;
            }
            ans += m - i + 1;
        }
        i = l;
        int k = l;
        int j = m + 1;
        while (i <= m && j <= r)
        {
            if (nums[i] <= nums[j])
            {
                helper[k++] = nums[i++];
            }
            else
            {
                helper[k++] = nums[j++];
            }
        }

        while (i <= m)
        {
            helper[k++] = nums[i++];
        }

        while (j <= r)
        {
            helper[k++] = nums[j++];
        }

        for (int i = l; i <= r; i++)
        {
            nums[i] = helper[i];
        }
    }

    void get_count(int l, int r)
    {
        if (l == r)
        {
            return;
        }
        int m = l + (r - l) / 2;
        get_count(l, m);
        get_count(m + 1, r);
        merge1(l, m, r);
    }

    void solve()
    {
        int n = sz(nums);
        get_count(0, n - 1);
        cout << ans << "\n";
    }
};

int main()
{
    vector<int> nums = {6, 5, 3, 2, 1};
    int n = sz(nums);
    // mergeSort(nums, 0, n - 1);
    // mergeSortIt(nums);
    // SumOfSmallers solver(nums);
    ReversePairs solver(nums);
    solver.solve();
    for0(i, n)
    {
        cout << nums[i] << " ";
    }
    return 0;
}