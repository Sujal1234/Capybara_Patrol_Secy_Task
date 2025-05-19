# Editorial
First of all, it is clear that only the parity of the integers matters and not the exact value since the only restriction we have is on the parity of sums.

The problem boils down to *assigning* "even" or "odd" to each child in such a way that no two friends are assigned the same parity, otherwise the sum of their integers will be even.

We can model this situation by an undirected graph with labeled nodes. Represent each Bombardino Crocodilo child by a node and represent a pair of best friends by an edge between them. The problem can be rephrased as "Can we assign an even/odd parity to each node such that no edge connects two nodes with the same parity? If yes then what are these parities?"

From this it is clear that we need to check whether the graph is **[bipartite](https://en.wikipedia.org/wiki/Bipartite_graph)**. We can do so by doing a series [breadth-first-searches (BFS)](https://cp-algorithms.com/graph/breadth-first-search.html) on the nodes which have not been visited.  
Start from any node and without loss of generality assign it "even". Then visit all of its adjacent nodes and assign them the opposite parity. Continue this BFS. If no more adjacent nodes can be visited then continue to the next unvisited node of the graph and repeat the process until all $n$ nodes have been visited and assigned a parity.

This runs in $O(n + m)$ time.  
Then we can simply give any valid integer of the assigned parity to each child.