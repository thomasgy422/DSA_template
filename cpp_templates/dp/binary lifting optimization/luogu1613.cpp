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

bool st[51][51][64];
int times[51][51];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i= 1; i < 51; i++) {
        for (int j= 1; j < 51; j++) {
            st[i][j][0]= false;
            times[i][j]= INT_MAX;
        }
    }
    int n, m;
    int x, y;
    cin >> n >> m;

    for (int i= 0; i < m; i++) {
        cin >> x >> y;
        st[x][y][0]= 1;
        times[x][y]= 1;
    }

    for (int p= 1; p <= 63; p++) {
        for (int jump= 1; jump <= n; jump++) {
            for (int i= 1; i <= n; i++) {
                for (int j= 1; j <= n; j++) {
                    if (st[i][jump][p - 1] && st[jump][j][p - 1]) {
                        st[i][j][p]= 1;
                        times[i][j]= 1;
                    }
                }
            }
        }
    }
    if (times[1][n] != 1) {
        for (int jump= 1; jump <= n; jump++) {
            for (int i= 1; i <= n; i++) {
                for (int j= 1; j <= n; j++) {
                    if (times[i][jump] != INT_MAX &&
                        times[jump][j] != INT_MAX) {
                        times[i][j]=
                            min(times[i][j], times[i][jump] + times[jump][j]);
                    }
                }
            }
        }
    }
    cout << times[1][n] << endl;
}