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

/*
    sorting algorithm     Time       Space.    Stability
    SelectionSort         O(n^2).    O(1)      False.
    BubbleSort            O(n^2).    O(1).     True
    InsertionSort.        O(n^2).    O(1).     True
    MergeSort             O(n*logn)  O(n).     True
    QuickSort             O(n*logn). O(logn).  False
    HeapSort              O(n*logn). O(1).     False
    CountSort             O(n).      O(m).     True.       has constraint on the object being sorted
    RadixSort.            O(n)       O(m).     True.       has constraint on the object being sorted
*/

class RadixSort
{
public:
    vi nums;
    vi help;
    RadixSort(vi &lst)
    {
        nums = lst;
        help = lst;
        for0(i, sz(nums))
        {
            help[i] = 0;
        }
    }

    int get_bits()
    {
        int ans = 0;
        for0(i, sz(nums))
        {
            int cur = nums[i];
            int temp = 0;
            while (cur > 0)
            {
                cur /= 10;
                temp += 1;
            }
            ans = max(ans, temp);
        }
        return ans;
    }

    int get_bit_at(int i, int num)
    {
        while (i > 0)
        {
            num /= 10;
            i--;
        }
        return num % 10;
    }

    void sort()
    {
        int bits = get_bits();
        vi bucket(10);
        for (int i = 0; i < bits; i++)
        {
            for (int j = 0; j < sz(nums); j++)
            {
                bucket[get_bit_at(i, nums[j])]++;
            }

            // Trick: prefix sum for each digit, then we can loop backward
            // and fill the help while decrement index in bucket
            for (int j = 1; j < 10; j++)
            {
                bucket[j] = bucket[j - 1] + bucket[j];
            }

            for (int j = sz(nums) - 1; j >= 0; j--)
            {
                help[--bucket[get_bit_at(i, nums[j])]] = nums[j];
            }

            for0(j, sz(nums))
            {
                nums[j] = help[j];
            }

            for0(j, 10)
            {
                bucket[j] = 0;
            }
        }

        for0(i, sz(nums))
        {
            cout << nums[i] << " ";
        }
    }
};

int main()
{
    vi nums = {3, 20, 1234, 30, 8, 64, 4, 15, 199};
    RadixSort rs(nums);
    rs.sort();
    return 0;
}

/*

*/
