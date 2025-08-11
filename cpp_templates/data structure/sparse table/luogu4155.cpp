#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

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

const int MAXN = 200001;
const int LIMIT = 18;

int power;
int n, m;

vvi line;
int st[MAXN * 2][LIMIT];
int ans[MAXN];

int log2_floor(int n)
{
    int ans = 0;
    while ((1 << ans) <= (n >> 1))
        ans++;
    return ans;
}

void build()
{
    for (int i = 0; i < n; i++)
    {
        if (line[i][1] > line[i][2])
        {
            line[i][2] += m;
        }
    }

    sort(line.begin(), line.begin() + n, [](const vi &a, const vi &b)
         { return a[1] < b[1]; });

    int e = n * 2;
    for (int i = 0; i < n; i++)
    {
        line[i + n][0] = line[i][0];
        line[i + n][1] = line[i][1] + m;
        line[i + n][2] = line[i][2] + m;
    }

    for (int i = 0, arrive = 0; i < e; i++)
    {
        while (arrive + 1 < e && line[arrive + 1][1] <= line[i][2])
        {
            arrive++;
        }
        if (arrive <= i)
            st[i][0] = i;
        else
            st[i][0] = arrive;
    }

    for (int p = 1; p <= power; p++)
    {
        for (int i = 0; i < e; i++)
        {
            st[i][p] = st[st[i][p - 1]][p - 1];
        }
    }
}

int jump(int i)
{
    int aim = line[i][1] + m;
    int cur = i;
    int ans_val = 0;

    for (int p = power; p >= 0; p--)
    {
        int next = st[cur][p];
        if (next != cur && line[next][2] < aim)
        {
            ans_val += (1 << p);
            cur = next;
        }
    }
    return ans_val + 2;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    line.resize(n << 1, vi(3));
    for (int i = 0; i < n; i++)
    {
        line[i][0] = i + 1;
        cin >> line[i][1] >> line[i][2];
    }

    power = log2_floor(n);
    build();

    vi ans_vec(n);
    for (int i = 0; i < n; i++)
    {
        ans_vec[line[i][0] - 1] = jump(i);
    }

    for (int i = 0; i < n; i++)
    {
        cout << ans_vec[i] << (i == n - 1 ? '\n' : ' ');
    }

    return 0;
}