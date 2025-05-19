#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges(n+1);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    vector<int> parity(n+1, -1);
    queue<int> q;

    for(int start = 1; start <= n; start++){
        if(parity[start] != -1) continue;
        //Start a BFS from this node
        parity[start] = 0;
        q.push(start);

        while(!q.empty()){
            int u = q.front();
            q.pop();

            for(int v : edges[u]){
                if(parity[v] == -1){
                    parity[v] = !parity[u];
                    q.push(v);
                } else if(parity[v] == parity[u]){
                    //Found same‑parity edge => not bipartite
                    cout << -1 << '\n';
                    return 0;
                }
            }
        }
    }

    //If we reach here, it's bipartite.
    //parity[i] == 0 => give even number 2
    //parity[i] == 1 => give odd number 1
    for(int i = 1; i <= n; i++){
        cout << (parity[i] == 0 ? 2 : 1) << " \n"[i==n];
    }
    return 0;
}