#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <list>

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

const int mx = 50001;

void swap(int i, int j, int arr[])
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

class MaxHeap
{
public:
    int arr[mx];
    int size;
    MaxHeap()
    {
        size = 0;
    }

    void push(int v)
    {
        int idx = size;
        arr[idx] = v;
        // heapify up
        while (idx > 0 && arr[idx] > arr[idx / 2])
        {
            swap(idx, idx / 2, arr);
            idx /= 2;
        }
        size++;
    }

    // heapify down
    void heapify(int i, int size)
    {
        int l = i * 2 + 1;
        while (l < size)
        {
            int best = (l + 1 < size && arr[l + 1] > arr[l]) ? l + 1 : l;
            best = arr[best] > arr[i] ? best : i;
            if (best == i)
            {
                break;
            }
            swap(best, i, arr);
            i = best;
            l = 2 * i + 1;
        }
    }

    void pop()
    {
        if (size == 0)
        {
            return;
        }
        arr[0] = 0;
        arr[0] = arr[size - 1];
        heapify(0, size);
        size--;
    }

    int top()
    {
        if (size > 0)
        {
            return arr[0];
        }
        return -1;
    }

    int get_size()
    {
        return size;
    }

    // time complexity: O(nlogn) with const space
    void heapsort(int n)
    {
        while (size > 1)
        {
            swap(0, --size, arr);
            heapify(0, size);
        }
        for0(i, n)
        {
            cout << arr[i] << " ";
        }
    }
};

int main()
{
    // default max heap
    priority_queue<int> maxpq;
    priority_queue<int, vector<int>, greater<int>> minpq;
    MaxHeap hp;
    hp.push(1);
    hp.push(10);
    hp.push(3);
    hp.push(6);
    hp.push(5);
    hp.push(20);
    int n = hp.get_size();
    hp.heapsort(n);
    return 0;
}

/*

    1 0 0
*/
