#include <iostream>
#include <cstdio>
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

// always update the code inside the template instead of passing +1, -1 index in main solution
// https://leetcode.com/problems/range-sum-query-2d-mutable/
class FenwickTree2D
{
public:
    int tree[304][304];
    int grid[304][304];
    int m;
    int n;
    FenwickTree2D()
    {
    }
    FenwickTree2D(vvi &matrix)
    {
        memset(tree, 0, sizeof(tree));
        memset(grid, 0, sizeof(grid));
        m = sz(matrix);
        n = sz(matrix[0]);
        for0(i, m)
        {
            for0(j, n)
            {
                update(i, j, matrix[i][j]);
            }
        }
        for0(i, m)
        {
            for0(j, n)
            {
                grid[i][j] = matrix[i][j];
            }
        }
    }

    int lowbit(int i)
    {
        return i & (-i);
    }

    void add(int x, int y, int v)
    {
        for (int i = x; i <= m; i += lowbit(i))
        {
            for (int j = y; j <= n; j += lowbit(j))
            {
                tree[i][j] += v;
            }
        }
    }

    void update(int x, int y, int v)
    {
        add(x + 1, y + 1, v - grid[x][y]);
        grid[x][y] = v;
    }

    int sum(int x, int y)
    {
        int ans = 0;
        for (int i = x; i > 0; i -= lowbit(i))
        {
            for (int j = y; j > 0; j -= lowbit(j))
            {
                ans += tree[i][j];
            }
        }
        return ans;
    }

    int query(int a, int b, int x, int y)
    {
        return sum(x + 1, y + 1) - sum(a, y + 1) - sum(x + 1, b) + sum(a, b);
    }
};

class NumMatrix
{
public:
    FenwickTree2D ft;
    NumMatrix(vector<vector<int>> &matrix) : ft(matrix)
    {
    }

    void update(int row, int col, int val)
    {
        ft.update(row, col, val);
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        return ft.query(row1, col1, row2, col2);
    }
};

// range update, range query
// https://www.luogu.com.cn/problem/P4514
/*
    sum(1, 1, n, m) =
     (n + 1) * (m + 1) * (sum(i from 1 to n, j from 1 to m) d[i][j])
    -(m + 1) * (sum(i from 1 to n, j from 1 to m) i * d[i][j])
    -(n + 1) * (sum(i from 1 to n, j from 1 to m) j * d[i][j])
    + (sum(i from 1 to n, j from 1 to m) i * j * d[i][j])
    四个树状数组分别维护
*/

const int maxm = 2051;
const int maxn = 2051;
// 维护信息 : d[i][j]
int tree1[maxn][maxm];
// 维护信息 : d[i][j] * i
int tree2[maxn][maxm];
// 维护信息 : d[i][j] * j
int tree3[maxn][maxm];
// 维护信息 : d[i][j] * i * j
int tree4[maxn][maxm];
int m;
int n;

class FenwickTree2D_Range
{
public:
    FenwickTree2D_Range(int x, int y)
    {
        n = x;
        m = y;
        memset(tree1, 0, sizeof(tree1));
        memset(tree2, 0, sizeof(tree2));
        memset(tree3, 0, sizeof(tree3));
        memset(tree4, 0, sizeof(tree4));
    }

    int lowbit(int i)
    {
        return i & (-i);
    }

    void add(int x, int y, int v)
    {
        int v1 = v;
        int v2 = x * v;
        int v3 = y * v;
        int v4 = x * y * v;

        for (int i = x; i <= n; i += lowbit(i))
        {
            for (int j = y; j <= m; j += lowbit(j))
            {
                tree1[i][j] += v1;
                tree2[i][j] += v2;
                tree3[i][j] += v3;
                tree4[i][j] += v4;
            }
        }
    }

    int sum(int x, int y)
    {
        int ans = 0;
        for (int i = x; i > 0; i -= lowbit(i))
        {
            for (int j = y; j > 0; j -= lowbit(j))
            {
                ans += (x + 1) * (y + 1) * tree1[i][j] - (y + 1) * tree2[i][j] - (x + 1) * tree3[i][j] + tree4[i][j];
            }
        }
        return ans;
    }

    int range(int a, int b, int c, int d)
    {
        return sum(c, d) - sum(a - 1, d) - sum(c, b - 1) + sum(a - 1, b - 1);
    }

    void add(int a, int b, int c, int d, int v)
    {
        add(a, b, v);
        add(c + 1, d + 1, v);
        add(a, d + 1, -v);
        add(c + 1, b, -v);
    }
};

int main()
{
    char op;
    int n, m, a, b, c, d, v;
    scanf("%s", &op);
    scanf("%d%d", &n, &m);
    FenwickTree2D_Range ft(n, m);

    while (scanf("%s", &op) != EOF)
    {
        if (op == 'X')
        {
            scanf("%d%d", &n, &m);
        }
        else if (op == 'L')
        {
            scanf("%d%d%d%d%d", &a, &b, &c, &d, &v);
            ft.add(a, b, c, d, v);
        }
        else
        {
            scanf("%d%d%d%d", &a, &b, &c, &d);
            printf("%d\n", ft.range(a, b, c, d));
        }
    }
    return 0;
}