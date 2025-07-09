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

const int mx = 5001;

// v / 32 to get the index, v % 32 to get the bit pos
class Bitset
{
public:
    int arr[mx];
    Bitset()
    {
    }

    void add(int v)
    {
        arr[v / 32] |= (1 << v % 32);
    }

    void remove(int v)
    {
        arr[v / 32] &= ~(1 << (v % 32));
    }

    void reverse(int v)
    {
        arr[v / 32] ^= 1 << (v % 32);
    }

    bool contains(int v)
    {
        return (arr[v / 32] & (1 << (v % 32))) > 0;
    }
};

int main()
{
    Bitset bs;
    bs.add(27);
    bs.add(105);
    bs.add(6);
    bs.add(1004);
    bs.remove(6);
    cout << bs.contains(27);
    cout << bs.contains(6);
    return 0;
}

/*

*/
