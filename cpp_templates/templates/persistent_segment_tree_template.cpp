#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct PersistentSegmentTree {
    static const int MAXN= 1000002;  // update
    static const int MAXT= MAXN * 23;
    int cnt;
    int root[MAXN];
    T tree[MAXT];
    int leftChild[MAXT], rightChild[MAXT];
    int n;

    PersistentSegmentTree(int _n, vector<T>& nums) {
        n= _n;
        cnt= 0;
        root[0]= build(nums, 1, n);
    }

    int build(vector<T>& nums, int l, int r) {
        int rt= ++cnt;
        if (l == r) {
            tree[rt]= nums[l];
            return rt;
        }
        int mid= (l + r) / 2;
        leftChild[rt]= build(nums, l, mid);
        rightChild[rt]= build(nums, mid + 1, r);
        return rt;
    }

    int update(int pos, T val, int l, int r, int pre) {
        int rt= ++cnt;
        leftChild[rt]= leftChild[pre];
        rightChild[rt]= rightChild[pre];
        tree[rt]= tree[pre];
        if (l == r) {
            tree[rt]= val;
            return rt;
        }
        int mid= (l + r) / 2;
        if (pos <= mid)
            leftChild[rt]= update(pos, val, l, mid, leftChild[rt]);
        else
            rightChild[rt]= update(pos, val, mid + 1, r, rightChild[rt]);
        return rt;
    }

    // 查询单点
    T query(int pos, int l, int r, int rt) {
        if (l == r) return tree[rt];
        int mid= (l + r) / 2;
        if (pos <= mid)
            return query(pos, l, mid, leftChild[rt]);
        else
            return query(pos, mid + 1, r, rightChild[rt]);
    }
};
