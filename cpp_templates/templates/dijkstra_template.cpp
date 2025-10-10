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
void dijkstra(int n, const vector<vector<pair<int, T>>>& graph, vector<T>& dist,
              int src) {
    using P= pair<T, int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    dist.assign(n, numeric_limits<T>::max());
    dist[src]= 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u]= pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : graph[u]) {
            if (dist[v] > d + w) {
                dist[v]= d + w;
                pq.push({dist[v], v});
            }
        }
    }
}