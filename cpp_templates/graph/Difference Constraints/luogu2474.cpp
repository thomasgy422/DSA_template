#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second

#define present(c, x) ((c).find(x) != (c).end())
#define cpresent(c, x) (find(all(c), x) != (c).end())
#define sz(a) int((a).size())

typedef long long i64;
typedef double ld;
typedef __int128_t i128;
typedef pair<int, int> ii;
typedef pair<int, ld> pid;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;

    vvi dmx(n + 1, vi(n + 1)), dmn(n + 1, vi(n + 1));
    vector<vector<char>> mat(n + 1, vector<char>(n + 1, ' '));
    for (int i= 1; i <= n; i++) {
        for (int j= 1; j <= n; j++) {
            cin >> mat[i][j];
            if (i == j) {
                dmx[i][j]= 0;
                dmn[i][j]= 0;
            } else {
                if (mat[i][j] == '?') {
                    dmx[i][j]= 2;
                    dmn[i][j]= -2;
                } else if (mat[i][j] == '+') {
                    dmx[i][j]= 2;
                    dmn[i][j]= 1;
                } else if (mat[i][j] == '-') {
                    dmx[i][j]= -1;
                    dmn[i][j]= -2;
                } else {
                    dmx[i][j]= 0;
                    dmn[i][j]= 0;
                }
            }
        }
    }

    for (int k= 1; k <= n; k++) {
        for (int i= 1; i <= n; i++) {
            for (int j= 1; j <= n; j++) {
                if (dmx[i][k] + dmx[k][j] < dmx[i][j]) {
                    dmx[i][j]= dmx[i][k] + dmx[k][j];
                }

                if (dmn[i][k] + dmn[k][j] > dmn[i][j]) {
                    dmn[i][j]= dmn[i][k] + dmn[k][j];
                }
            }
        }
    }

    int ans1= 0, ans2= 0, ans3= 0;
    for (int i= 1; i <= n; i++) {
        for (int j= i + 1; j <= n; j++) {
            if (i != a && i != b && j != a && j != b) {
            }
        }
    }
    cout << ans1 << " " << ans2 << " " << ans3 << endl;
}
/*
    1 + x < 2 + y

    x + y + z < a + b + c

    x + y < a + b

    dmx[i][j] = k1

    dmx[i][a] = wi - wa <= k3
    dmx[a][j] = wa - w[j] <= k4

    dmn[i][j] = k2

    a - b >= k1
    b <= a - k1
    a - b <= k2
    a <= b + k2

    a - i > j - b

    a + b > i + j

    b - i > j - a

    dmn[a][i] > dmx[j][b]

    dmin[b][i] > dmax[j][a]
    b - i >=
    j - a <=
    b - i > j - a





*/
