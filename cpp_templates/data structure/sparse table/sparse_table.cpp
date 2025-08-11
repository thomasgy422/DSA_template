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

// show which bit is 1
void show1(int x, int m)
{
    int t = x;
    for (int i = m - 1; i >= 0; i--)
    {
        if (1 << i <= t)
        {
            t -= (1 << i);
            cout << "pos" << i << " is 1" << endl;
        }
        else
        {
            cout << "pos" << i << " is 0" << endl;
        }
    }
}

// the greatest power of 2 that is <= x
void show2(int x)
{
    int p = 0;
    // if overflow will have issue
    // while ((1 << p) <= x) {
    //     p++;
    // }

    while ((1 << p) <= (x >> 1))
    {
        p++;
    }
    cout << p;
}



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    // show1(100, 10);
    show2(100);
}
