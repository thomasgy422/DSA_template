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

class Solution {
   public:
    vvi multi(vvi &m1, vvi &m2) {
        int n= sz(m1), k= sz(m1[0]);
        int m= sz(m2[0]);
        vvi res(n, vi(m));
        for (int i= 0; i < n; i++) {
            for (int j= 0; j < m; j++) {
                for (int c= 0; c < k; c++) {
                    res[i][j]+= m1[i][c] * m2[c][j];
                }
            }
        }
        return res;
    }

    vvi pow(int p, vvi mat) {
        vvi cur= {{1, 0}, {0, 1}};
        while (p > 0) {
            if (p & 1) {
                cur= multi(cur, mat);
            }
            mat= multi(mat, mat);
            p>>= 1;
        }
        return cur;
    }

    int fib(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        vvi mat= {{1, 1}, {1, 0}};
        vvi res= pow(n - 1, mat);
        vvi start= {{1, 0}};
        vvi ans= multi(start, res);
        return ans[0][0];
    }
};

/*
    a[0][0] * b[0][0] + a[0][1] * b[1][0] i = 0.  j = 0, k = 0 - 1
    a[0][0] * b[0][1] + a[0][1] * b[1][1] i = 0.  j = 1
    a[1][0] * b[0][0] + a[1][1] * b[1][0] i = 1   j = 0
    a[1][0] * b[0][1] + a[1][1] * b[1][1] i = 1   j = 1
         [1 1]
         [1 0]
    [1 1]
    [1 0]
*/