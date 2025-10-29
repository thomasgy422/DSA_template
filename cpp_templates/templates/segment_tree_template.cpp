#include <bits/stdc++.h>
using namespace std;

template <typename T>
class SegmentTree {
   public:
    int n;
    vector<T> sums, lazy;

    SegmentTree(const vector<T>& arr, int size) : n(size) {
        sums.assign(n << 2, 0);
        lazy.assign(n << 2, 0);
        build(arr, 1, n, 1);
    }

    void lazyFunc(int i, int len, T val) {
        sums[i]+= val * len;
        lazy[i]+= val;
    }

    void down(int i, int ln, int rn) {
        if (lazy[i] != 0) {
            lazyFunc(i << 1, ln, lazy[i]);
            lazyFunc(i << 1 | 1, rn, lazy[i]);
            lazy[i]= 0;
        }
    }

    void up(int i) { sums[i]= sums[i << 1] + sums[i << 1 | 1]; }

    void build(const vector<T>& arr, int L, int R, int i) {
        if (L == R) {
            sums[i]= arr[L];
            return;
        }
        int mid= (L + R) >> 1;
        build(arr, L, mid, i << 1);
        build(arr, mid + 1, R, i << 1 | 1);
        up(i);
    }

    void update(int l, int r, T val, int L, int R, int i) {
        if (l <= L && R <= r) {
            lazyFunc(i, R - L + 1, val);
            return;
        }
        int mid= (L + R) >> 1;
        down(i, mid - L + 1, R - mid);
        if (l <= mid) update(l, r, val, L, mid, i << 1);
        if (r > mid) update(l, r, val, mid + 1, R, i << 1 | 1);
        up(i);
    }

    T query(int l, int r, int L, int R, int i) {
        if (l <= L && R <= r) return sums[i];
        int mid= (L + R) >> 1;
        down(i, mid - L + 1, R - mid);
        T res= 0;
        if (l <= mid) res+= query(l, r, L, mid, i << 1);
        if (r > mid) res+= query(l, r, mid + 1, R, i << 1 | 1);
        return res;
    }

    void update(int l, int r, T val) { update(l, r, val, 1, n, 1); }
    T query(int l, int r) { return query(l, r, 1, n, 1); }
};
