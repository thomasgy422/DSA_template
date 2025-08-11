#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

#define for0(i, n) for (int i = 0; i < (int)(n); ++i)            // 0 based indexing
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)           // 1 based indexing
#define forc(i, l, r) for (int i = (int)(l); i <= (int)(r); ++i) // closed interval from l to r inclusive

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

const int MX = 1000001;
const int LIMIT = 21;

int stmx[MX][LIMIT];
int stmn[MX][LIMIT];

// sparse table 求区间最大最小值模版题
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vi hi(n);

    for0(i, n)
    {
        cin >> hi[i];
    }

    for0(i, n)
    {
        stmx[i][0] = hi[i];
        stmn[i][0] = hi[i];
    }

    int power = (int)floor(log2(n));

    for (int p = 1; p <= power; p++)
    {
        for (int i = 0; i < n; i++)
        {
            if (i + (1 << p - 1))
                stmx[i][p] = max(stmx[i + (1 << p - 1)][p - 1], stmx[i][p - 1]);
            else
                stmx[i][p] = stmx[i][p - 1];

            if (i + (1 << p - 1))
                stmn[i][p] = min(stmn[i + (1 << p - 1)][p - 1], stmn[i][p - 1]);
            else
                stmn[i][p] = stmn[i][p - 1];
        }
    }

    int mx, mn;
    int a, b;
    for0(i, q)
    {
        cin >> a >> b;
        a--;
        b--;
        mx = hi[a];
        mn = hi[a];
        int p = (int)floor(log2(b - a + 1));
        mx = max(stmx[a][p], stmx[b - (1 << p) + 1][p]);
        mn = min(stmn[a][p], stmn[b - (1 << p) + 1][p]);
        cout << mx - mn << endl;
    }

    return 0;
}