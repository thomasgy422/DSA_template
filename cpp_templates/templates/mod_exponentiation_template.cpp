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

template <typename T>
T modPower(T num, T pow, T mod) {
    T ans= 1 % mod;
    num%= mod;

    while (pow > 0) {
        if (pow & 1) ans= (1LL * ans * num) % mod;
        num= (1LL * num * num) % mod;
        pow>>= 1;
    }

    return ans;
}