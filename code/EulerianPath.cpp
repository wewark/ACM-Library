#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef vector<bool> vb;
typedef vector<string> vs;
const int di[] = { -1, 0, 1, 0 };
const int dj[] = { 0, 1, 0, -1 };
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const double EPS = 1e-5;
#define mp make_pair
#define all(x) x.begin(),x.end()

// Eulerian Path
// Get eulerian path for undirected graph in O(V + E)
/*
For directed graphs, follow this:
https://math.stackexchange.com/questions/1871065/euler-path-for-directed-graph

Step 1:
Check the following conditions ( Time Complexity : O( V ) ) to determine if Euler Path can exist or not :
a) There should be a single vertex in graph which has (indegree+1==outdegree), lets call this vertex 'an'.
b) There should be a single vertex in graph which has (indegree==outdegree+1), lets call this vertex 'bn'.
c) Rest all vertices should have (indegree==outdegree)
If either of the above condition fails Euler Path can't exist.

Step 2:
Add a edge from vertex 'bn' to 'an' in existing graph, now for all vertices (indegree==outdegree) holds true. ( Time Complexity : O( 1 ) )

Step 3:
Try to find Euler cycle in this modified graph using HIERHOLZER'S ALGORITHM. ( Time Complexity : O( V+E ) )
a) Choose any vertex v and push it onto a stack. Initially all edges are unmarked.
b) While the stack is nonempty, look at the top vertex, u, on the stack. If u has an unmarked incident edge, say, to a vertex w, then push w onto the stack and mark the edge uw. On the other hand, if u has no unmarked incident edge, then pop u off the stack and print it.
c) When the stack is empty, you will have printed a sequence of vertices that correspond to an Eulerian circuit.
Look into this Blog for better explanation of HIERHOLZER'S ALGORITHM .

Step 4:
Check if cycle so printed is sufficient number of edges included or not. If not then original graph might be disconnected and Euler Path can't exist in this case.

Step 5:
In the cycle so determined in Step 3, remove a edge from 'bn' to 'an', now start traversing this modified cycle (Not a cycle any more, it's a Path) from 'bn'. Finally you'll end up on 'an', So this path is Euler Path of original graph.
*/

struct Edge;
typedef list<Edge>::iterator iter;

struct Edge {
	int next_vertex;
	iter reverse_edge;

	Edge(int next_vertex)
		:next_vertex(next_vertex)
	{ }
};

const int max_vertices = 5;
int num_vertices;
list<Edge> adj[max_vertices];		// adjacency list

vector<int> path;

void find_path(int v) {
	while (adj[v].size() > 0) {
		int vn = adj[v].front().next_vertex;
		adj[vn].erase(adj[v].front().reverse_edge);
		adj[v].pop_front();
		find_path(vn);
	}
	path.push_back(v);
}

void add_edge(int a, int b) {
	adj[a].push_front(Edge(b));
	iter ita = adj[a].begin();
	adj[b].push_front(Edge(a));
	iter itb = adj[b].begin();
	ita->reverse_edge = itb;
	itb->reverse_edge = ita;
}

int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	add_edge(1, 4);
	add_edge(4, 3);
	add_edge(3, 2);
	add_edge(3, 2);
	add_edge(2, 1);
	add_edge(2, 3);
	find_path(1);
	cin.ignore(), cin.get();
}
