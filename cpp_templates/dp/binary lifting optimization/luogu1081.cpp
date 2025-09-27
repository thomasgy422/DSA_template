#include <algorithm>
#include <climits>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>

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

const int MAXN= 100005;
int n;
int h[MAXN], s[MAXN], x[MAXN];
ii rankArr[MAXN];
int last[MAXN], nxt[MAXN];
int to1[MAXN], dist1[MAXN];
int to2[MAXN], dist2[MAXN];

ll st[MAXN][18][2];
ll stdist[MAXN][18][2];

void update(int i, int j) {
    if (j == 0) return;
    int dist= abs(h[i] - h[j]);
    if (to1[i] == 0 || dist < dist1[i] ||
        (dist == dist1[i] && h[j] < h[to1[i]])) {
        to2[i]= to1[i];
        dist2[i]= dist1[i];
        to1[i]= j;
        dist1[i]= dist;
    } else if (to2[i] == 0 || dist < dist2[i] ||
               (dist == dist2[i] && h[j] < h[to2[i]])) {
        to2[i]= j;
        dist2[i]= dist;
    }
}

void deletePos(int i) {
    int l= last[i];
    int r= nxt[i];
    if (l != 0) nxt[l]= r;
    if (r != 0) last[r]= l;
}

void near() {
    for (int i= 1; i <= n; i++) {
        rankArr[i].fi= i;
        rankArr[i].se= h[i];
    }
    sort(rankArr + 1, rankArr + n + 1,
         [](const ii& a, const ii& b) { return a.se < b.se; });
    rankArr[0].fi= 0;
    rankArr[n + 1].fi= 0;

    for (int i= 1; i <= n; i++) {
        last[rankArr[i].fi]= rankArr[i - 1].fi;
        nxt[rankArr[i].fi]= rankArr[i + 1].fi;
    }

    for (int i= 1; i <= n; i++) {
        to1[i]= dist1[i]= 0;
        to2[i]= dist2[i]= 0;
        update(i, last[i]);
        update(i, last[last[i]]);
        update(i, nxt[i]);
        update(i, nxt[nxt[i]]);
        deletePos(i);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i= 1; i <= n; i++) {
        cin >> h[i];
    }

    int x0, m;
    cin >> x0 >> m;

    for (int i= 1; i <= m; i++) {
        cin >> s[i] >> x[i];
    }

    near();

    for (int i= 1; i <= n; i++) {
        st[i][0][0]= to2[i];
        stdist[i][0][0]= dist2[i];
        st[i][0][1]= to1[i];
        stdist[i][0][1]= dist1[i];
        st[i][1][0]= st[i][0][0] + st[st[i][0][0]][0][1];
        stdist[i][1][0]= stdist[st[i][0][0]][0][1] + stdist[i][0][0];
        st[i][1][1]= st[i][0][1] + st[st[i][0][1]][0][0];
        stdist[i][1][1]= stdist[st[i][0][1]][0][0] + stdist[i][0][1];
    }

    int nxta, nxtb;
    for (int p= 2; p < 18; p++) {
        for (int i= 1; i <= n; i++) {
            st[i][p][0]= st[st[i][p - 1][0]][p - 1][0];
            st[i][p][1]= st[st[i][p - 1][1]][p - 1][1];
            stdist[i][p][0]=
                stdist[st[i][p - 1][0]][p - 1][1] + stdist[i][p - 1][0];
            stdist[i][p][1]=
                stdist[st[i][p - 1][1]][p - 1][0] + stdist[i][p - 1][1];
        }
    }

    // for (int p= 0; p < 18; p++) {
    //     for (int i= 1; i <= n; i++) {
    //         cout << p << " " << st[i][p][0] << " " << st[i][p][1] << endl;
    //         cout << stdist[i][p][0] << " " << stdist[i][p][1] << endl;
    //     }
    // }
}

/*


2 3 1 4
1 2 3 4

find 1, 2 smallest to the right, if not found, use 0

find for each start si, start with a or b, travel 10^9, the distance a,
and b would go

case x == 0, q1: 0/0 = 1,  q2 all 0

else:
    stto:
    stdist:  
    sta:
    stb:

    2 3 1 4      0 1 2 3 4 0
    1 2 3 4.     0 3 1 2 4 0
                   1 2 3 4

    last.  [0,3,1,0,2]
    nxt.   [0,2,4,1,0]

    2,3



*/