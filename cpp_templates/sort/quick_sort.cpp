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

// traditional quickSort
class QuickSort
{
public:
    vi nums;
    QuickSort(vi &lst)
    {
        nums = lst;
    }

    void quickSort(vi &nums, int l, int r)
    {
        if (l >= r)
        {
            return;
        }

        int idx = l + (rand() % (r - l + 1));
        int t = nums[idx];
        int j = l;
        int k = 0;
        for (int i = l; i <= r; i++)
        {
            if (nums[i] < t)
            {
                swap(nums, i, j);
                j++;
            }
            if (nums[i] == t)
            {
                k = i;
            }
        }
        swap(nums, k, j);
        quickSort(nums, l, j - 1);
        quickSort(nums, j + 1, r);
    }

    void swap(vi &nums, int i, int j)
    {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    void sort()
    {
        int n = sz(nums);
        quickSort(nums, 0, n - 1);
        for0(i, n)
        {
            cout << nums[i] << " ";
        }
    }
};

// quickSort optimized with ductch flag algorithm to handle the same elements
class QuickSort1
{
public:
    vi nums;
    QuickSort1(vi &lst)
    {
        nums = lst;
    }

    void quickSort(vi &nums, int l, int r)
    {
        if (l >= r)
        {
            return;
        }

        int idx = l + (rand() % (r - l + 1));
        int t = nums[idx];
        int i = l;
        int p = l;
        int q = r;
        while (i <= q)
        {
            if (nums[i] < t)
            {
                swap(nums, p, i);
                p++;
                i++;
            }
            else if (nums[i] == t)
            {
                i++;
            }
            else
            {
                swap(nums, q, i);
                q--;
            }
        }
        quickSort(nums, l, p - 1);
        quickSort(nums, q + 1, r);
    }

    void swap(vi &nums, int i, int j)
    {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    void sort()
    {
        int n = sz(nums);
        quickSort(nums, 0, n - 1);
        for0(i, n)
        {
            cout << nums[i] << " ";
        }
    }
};

int main()
{
    vi nums = {4, 5, 3, 6, 7, 3, 4, 5};
    QuickSort1 solver(nums);
    solver.sort();
    return 0;
}

/*
    3 2 3 3 4 4 4 5 5
            p   q

*/
