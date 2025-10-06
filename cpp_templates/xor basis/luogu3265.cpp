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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    double basis[m + 1];
    vvi lst(n + 1, vi(m + 1));

    for (int i= 1; i <= n; i++) {
        for (int j= 1; j <= m; j++) {
            cin >> lst[i][j];
        }
    }

    vvi rank(n + 1, vi(2));

    for (int i= 1; i <= n; i++) {
        cin >> rank[i][0];
        rank[i][1]= i;
    }

    sort(rank.begin() + 1, rank.end());

    function<bool(int)> insert= [&](int i) -> bool {
        vi& cur= lst[i];
        for (int j= 1; j <= m; j++) {
            if (cur[j] > 0) {
                if (basis[j] == 0) {
                    basis[j]= i;
                    return true;
                }
            }
        }
    };

    ll ans= 0;
    for (int i= 1; i <= n; i++) {
        if (insert(rank[i][1])) {
            ans+= rank[i][0];
        }
    }

    cout << ans << endl;
}