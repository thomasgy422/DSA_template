#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <cstring>
#include <cstdlib>

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

// index starts from 1!
class FenwickTree
{
public:
    int tree[500002];
    int size;
    // size is equal to the size of input list
    FenwickTree()
    {
    }

    FenwickTree(int n)
    {
        size = n;
        for (int i = 0; i <= size; ++i)
            tree[i] = 0;
    }

    void add(int i, int v)
    {
        int j = i;
        while (j <= size)
        {
            tree[j] += v;
            j += j & (-j);
        }
    }

    int sum(int i)
    {
        int j = i;
        int ans = 0;
        while (j > 0)
        {
            ans += tree[j];
            j -= j & (-j);
        }
        return ans;
    }

    int query(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }

    // single point update, range query
    void solve1()
    {
        int n, m;
        cin >> n >> m;
        FenwickTree ft(n);
        for0(i, n)
        {
            int v;
            cin >> v;
            // 维护前缀和
            ft.add(i + 1, v);
        }

        for0(i, m)
        {
            int op;
            cin >> op;
            if (op == 1)
            {
                int x, k;
                cin >> x >> k;
                ft.add(x, k);
            }
            else
            {
                int x, y;
                cin >> x >> y;
                int ret = ft.query(x, y);
                cout << ret << endl;
            }
        }
    }

    // range update, single point query
    void solve2()
    {
        int n, m;
        cin >> n >> m;
        FenwickTree ft(n);
        for0(i, n)
        {
            int v;
            cin >> v;
            // 数组中维护的是差分信息
            ft.add(i + 1, v);
            ft.add(i + 2, -v);
        }
        for0(i, m)
        {
            int op;
            cin >> op;
            if (op == 1)
            {
                int x, y, k;
                cin >> x >> y >> k;
                ft.add(x, k);
                ft.add(y + 1, -k);
            }
            else
            {
                int x;
                cin >> x;
                // 前缀和求当前下标x的值
                int ret = ft.query(1, x);
                cout << ret << endl;
            }
        }
    }
};

int main()
{
    FenwickTree ft;
    // ft.solve1();
    ft.solve2();
    return 0;
}