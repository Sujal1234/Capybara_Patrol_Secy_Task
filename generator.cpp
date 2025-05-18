#include "testlib.h"
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

void makeGraph(int n, int m, vector<tuple<int, int, int>> &edges);
void makeDot(vector<tuple<int, int, int>>& edges);

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    //Usage: "./gen n m [out_file]"

    int n = atoi(argv[1]); // Number of nodes
    assert(n >= 2 && n <= 100);

    int minEdges = n - 1; // To ensure connectivity at least n-1 nodes must be there
    int m = atoi(argv[2]);
    assert(m >= minEdges && m <= n * (n-1) / 2);

    vector<tuple<int, int, int>> edges{};
    makeGraph(n, m, edges);

    int u {}, v {};
    do{
        u = rnd.next(1, n);
        v = rnd.next(1, n);
    } while(u == v);
    
    
    // makeDot(edges);
    if(argc > 3){
        ofstream outf {argv[3]};
        outf << n << endl << m << endl;
        outf << u << " " << v << endl;
        for (auto [u, v, cost] : edges) {
            outf << u << " " << v << " " << cost << '\n';
        }
    }
    else{
        cout << n << endl << m << endl;
        cout << u << " " << v << endl;
        for (auto [u, v, cost] : edges) {
            cout << u << " " << v << " " << cost << '\n';
        }
    }

    return 0;
}

void makeGraph(int n, int m, vector<tuple<int, int, int>> &edges){
    set<pair<int, int>> usedEdges;

    // Generate a spanning tree to ensure connectivity
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end());

    for (int i = 1; i < n; ++i) {
        int u = perm[i];
        int v = perm[rnd.wnext(0, i - 1, 10)];
        int cost = rnd.next(1, 1000);
        if (u > v) swap(u, v);
        usedEdges.insert({u, v});
        edges.emplace_back(u, v, cost);
    }

    // Add remaining edges randomly
    while ((int)edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);

        if (u == v) continue;
        if (u > v) swap(u, v);

        if (usedEdges.count({u, v})) continue;

        usedEdges.insert({u, v});

        int cost = rnd.next(1, 1000);
        edges.emplace_back(u, v, cost);
    }

    shuffle(edges.begin(), edges.end());
}

//To visualise the graph. Only for my debugging.
//Generates a DOT file specifying the graph.
void makeDot(vector<tuple<int, int, int>>& edges){
    ofstream outf{"graph.dot"};
    outf << "graph G{\n";

    for(auto [u, v, cost] : edges){
        outf << u << " -- " << v << " [label=" << cost << "];\n";
    }
    outf << "}\n";
}