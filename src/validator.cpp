#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int MIN_N = 2;
constexpr int MAX_N = 1e5;

constexpr ll MIN_M = 1;
constexpr ll MAX_M = 1e7;

ll encodePair(int x, int y, int n){
    return (ll) x * (ll) n + y;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(MIN_N, MAX_N, "n");
    inf.readEoln();
    ll m = inf.readLong(MIN_M, min((ll) n * (ll) (n - 1) / 2, MAX_M), "m~");
    inf.readEoln();

    unordered_set<ll> edges;

    for (ll i = 0; i < m; i++)
    {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");

        ensuref(u != v, "Self loop at node %d", u);

        if(u > v) swap(u, v);
        ll encoding = encodePair(u, v, n);

        ensuref(!edges.count(encoding), "Edge between %d and %d is repeated", u, v);
        
        edges.insert(encoding);

        inf.readEoln();
    }
    inf.readEof();

    cout << "Valid test case.\n";

    return 0;
}
