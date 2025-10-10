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
class FenwickTree {
   public:
    int size;
    vector<T> tree;

    FenwickTree(int n) {
        size= n;
        tree.assign(n + 1, 0);
    }

    void update(int i, T v) {
        while (i <= size) {
            tree[i]+= v;
            i+= i & -i;
        }
    }

    T query(int i) const {
        T ans= 0;
        while (i > 0) {
            ans+= tree[i];
            i-= i & -i;
        }
        return ans;
    }

    T rangeQuery(int l, int r) const { return query(r) - query(l - 1); }
};