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

// 矩阵乘法，快速幂
template <typename T>
using Matrix= vector<vector<T>>;

template <typename T>
Matrix<T> identity(int n) {
    Matrix<T> I(n, vector<T>(n, 0));
    for (int i= 0; i < n; i++) I[i][i]= 1;
    return I;
}

template <typename T>
Matrix<T> multiply(const Matrix<T>& A, const Matrix<T>& B, T mod= 0) {
    int n= A.size(), k= A[0].size(), m= B[0].size();
    Matrix<T> C(n, vector<T>(m, 0));
    for (int i= 0; i < n; i++) {
        for (int c= 0; c < k; c++) {
            if (A[i][c] == 0) continue;
            for (int j= 0; j < m; j++) {
                C[i][j]+= A[i][c] * B[c][j];
                if (mod) C[i][j]%= mod;
            }
        }
    }
    return C;
}

template <typename T>
Matrix<T> power(Matrix<T> base, ll exp, T mod= 0) {
    int n= base.size();
    Matrix<T> res= identity<T>(n);
    while (exp > 0) {
        if (exp & 1) res= multiply(res, base, mod);
        base= multiply(base, base, mod);
        exp>>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Matrix<int> m= {{1, 0}};
}