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

int main()
{
    vector<int> nums = {4, 5, 3, 6, 2, 5, 1};
    int n = sz(nums);
    // mergeSort(nums, 0, n - 1);
    mergeSortIt(nums);
    for0(i, n)
    {
        cout << nums[i] << " ";
    }
    return 0;
}