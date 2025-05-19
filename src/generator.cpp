    #include "testlib.h"
    #include <bits/stdc++.h>
    #include <fstream>
    using namespace std;
    using ll = long long;

    constexpr int MIN_N = 2;
    constexpr int MAX_N = 1e5;
    constexpr ll MIN_M = 1;
    constexpr ll MAX_M = 1e6;

    void makeBipartite(int n, vector<pair<int, int>> &edges);
    void makeSparseBipartite(int n, int m, vector<pair<int, int>> &edges);
    void makeDenseBipartite(int n, vector<pair<int, int>> &edges);
    void makeGraph(int n, int m, vector<pair<int, int>> &edges);
    void makeCompleteGraph(int n, vector<pair<int, int>> &edges);
    void makeCompleteBipGraph(int n, vector<pair<int, int>> &edges);

    ll encodePair(int x, int y, int n);

    int main(int argc, char* argv[]){
        //Usage: "./gen n m type [outfile]"

        //n: Number of nodes
        //m: Number of edges

        //type 0: A random graph. May or may not be bipartite.
        //type 1: A random bipartite graph. Number of edges is random.
        //type 2: A bipartite graph more likely to have several edges 
        // (explained near the function definition).
        //type 3: A random bipartite graph with specified number of edges.
        //type 4: A complete graph with n nodes.
        //type 5: A complete bipartite graph with n nodes.

        //outfile is optional. If specified, the program's output is written to the file "outfile"

        //For type == 1, 2 or 4, m is not the number of edges
        //but it can work as a seed for the rng.

        if(argc < 4){
            printf("Wrong usage\n");
            return 1;
        }

        registerGen(argc, argv, 1);
        int n = atoi(argv[1]);
        ll m = atoi(argv[2]);
        int bipartiteType = atoi(argv[3]);

        assert(n >= MIN_N && n <= MAX_N);
        assert(m >= MIN_M && m <= MAX_M);

        vector<pair<int, int>> edges;

        switch(bipartiteType){
            case 0:
                assert(m <= (ll) n * (ll) (n-1) / 2); //Not more edges than number of distinct pairs
                makeGraph(n, m, edges);
                break;
            case 1:
                makeBipartite(n, edges);
                break;
            case 2:
                makeDenseBipartite(n, edges);
                break;
            case 3:
                assert(m <= (ll)(n/2) * ll(n - n/2)); //This is the upper bound on number of edges in the bipartite graph
                
                makeSparseBipartite(n, m, edges);
                break;
            case 4:
                makeCompleteGraph(n, edges);
                break;
            case 5:
                makeCompleteBipGraph(n, edges);
                break;
            default:
                printf("Invalid bipartite type.\n");
                return 1;
        }

        if(argc == 5){
            //Redirect output to the outfile
            freopen(argv[4], "w", stdout);
        }

        printf("%d\n", n);
        printf("%zu\n", edges.size());
        
        for(auto [u, v] : edges){
            int x = rnd.next(0, 1);
            if(x) printf("%d %d\n", u, v);
            else printf("%d %d\n", v, u);
        }
        return 0;
    }

    //To encode a pair of ints into a single 64 bit number which can be hashed and hence
    //used in the unordered_set.
    ll encodePair(int x, int y, int n){
        return (ll) x * (ll) n + y;
    }

    //Makes a randomised graph (not necessarily bipartite) with a given number of edges
    void makeGraph(int n, int m, vector<pair<int, int>> &edges){
        unordered_set<ll> edgesSet;

        while(edgesSet.size() < m){
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if(u == v)
                continue;
            if(u > v) swap(u, v);
            ll encoding = encodePair(u, v, n);

            if(!edgesSet.count(encoding)){
                edgesSet.insert(encoding);
                edges.emplace_back(u, v);
            }
        }
        shuffle(edges.begin(), edges.end());
    }

    //Makes a randomised bipartite graph with a randomly generated number of edges.
    void makeBipartite(int n, vector<pair<int, int>> &edges){
        //Size of one of the disjoint sets
        int a = rnd.next(1, n-1);

        //Generate permutation
        vector<int> arr(n);
        iota(arr.begin(), arr.end(), 1);
        shuffle(arr.begin(), arr.end()); 
        //First a elements of arr are in one set and the next n-a are in another.

        unordered_set<ll> edgesSet;

        ll m = rnd.next(1LL, (ll) a * (ll) (n-a));

        while(edgesSet.size() < m){
            int u = arr[rnd.next(0, a-1)];
            int v = arr[rnd.next(a, n-1)];

            if(u > v) swap(u, v);

            ll encoding = encodePair(u, v, n);
            if(!edgesSet.count(encoding)){
                edgesSet.insert(encoding);
                edges.emplace_back(u, v);
            }        
        }
        shuffle(edges.begin(), edges.end());  
    }

    //Makes a randomised bipartite graph with a given number of edges.
    void makeSparseBipartite(int n, int m, vector<pair<int, int>> &edges){
        //Size of one of the disjoint sets

        //we must have m <= a * (n - a);
        int a = rnd.next(1, n-1);
        while(m > (ll)a * (n - a)){
            a = rnd.next(1, n-1);
        }

        //Generate permutation
        vector<int> arr(n);
        iota(arr.begin(), arr.end(), 1);
        shuffle(arr.begin(), arr.end()); 
        //First a elements of arr are in one set and the next n-a are in another.

        unordered_set<ll> edgesSet;

        while(edgesSet.size() < m){
            int u = arr[rnd.next(0, a-1)];
            int v = arr[rnd.next(a, n-1)];

            if(u > v) swap(u, v);

            ll encoding = encodePair(u, v, n);
            if(!edgesSet.count(encoding)){
                edgesSet.insert(encoding);
                edges.emplace_back(u, v);
            }        
        }
        shuffle(edges.begin(), edges.end());  
    }

    //Makes a randomised bipartite graph such that if we partition the nodes into two disjoint
    //sets then each edge connects nodes from different sets and also every pair of nodes
    //in different sets is connected by an edge.
    void makeDenseBipartite(int n, vector<pair<int, int>> &edges){
        //Size of one of the disjoint sets
        int a = rnd.next(1, n-1);

        //Generate permutation
        vector<int> arr(n);
        iota(arr.begin(), arr.end(), 1);
        shuffle(arr.begin(), arr.end()); 
        //First a elements of arr are in one set and the next b are in another.

        unordered_set<ll> edgesSet;

        ll m = (ll) a * (ll) (n - a); // This is what makes it "dense"

        while(edgesSet.size() < m){
            int u = arr[rnd.next(0, a-1)];
            int v = arr[rnd.next(a, n-1)];

            if(u > v) swap(u, v);

            ll encoding = encodePair(u, v, n);
            if(!edgesSet.count(encoding)){
                edgesSet.insert(encoding);
                edges.emplace_back(u, v);
            }        
        }
        shuffle(edges.begin(), edges.end());
    }

    void makeCompleteGraph(int n, vector<pair<int, int>> &edges){
        for (int i = 1; i <= n; i++)
        {
            for(int j = i+1; j <= n; j++){
                edges.emplace_back(i, j);
            }
        }
    }

    void makeCompleteBipGraph(int n, vector<pair<int, int>> &edges){
        vector<int> arr(n);
        iota(arr.begin(), arr.end(), 1);
        shuffle(arr.begin(), arr.end());

        int a = n/2;

        for (int i = 0; i < a; i++)
        {
            for (int j = a; j < n; j++)
            {
                edges.emplace_back(arr[i], arr[j]);
            }
            
        }
        
    }