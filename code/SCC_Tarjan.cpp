#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef vector<bool> vb;
typedef vector<string> vs;
#define MAX_N 20001
#define NIL -1
// Codeforces 427C

vvi comp;
vi cost;

// Class for Tarjan Algorithm (Strongly connected components)
// A class that represents an directed graph
class Graph {
	int V;    // No. of vertices
	vvi adj;    // A dynamic array of adjacency lists

	// A Recursive DFS based function used by SCC()
	// A recursive function that finds and prints strongly connected
	// components using DFS traversal
	// u --> The vertex to be visited next
	// disc[] --> Stores discovery times of visited vertices
	// low[] -- >> earliest visited vertex (the vertex with minimum
	//             discovery time) that can be reached from subtree
	//             rooted with current vertex
	// *st -- >> To store all the connected ancestors (could be part
	//           of SCC)
	// stackMember[] --> bit/index array for faster check whether
	//                  a node is in stack
	void SCCUtil(int u, vi& disc, vi& low, stack<int>& st,
		vb& stackMember) {
		// A static variable is used for simplicity, we can avoid use
		// of static variable by passing a pointer.
		static int time = 0;

		// Initialize discovery time and low value
		disc[u] = low[u] = ++time;
		st.push(u);
		stackMember[u] = true;

		// Go through all vertices adjacent to this
		for (auto& v : adj[u]) {
			// If v is not visited yet, then recur for it
			if (disc[v] == -1) {
				SCCUtil(v, disc, low, st, stackMember);

				// Check if the subtree rooted with 'v' has a
				// connection to one of the ancestors of 'u'
				// Case 1 (per above discussion on Disc and Low value)
				low[u] = min(low[u], low[v]);
			}

			// Update low value of 'u' only of 'v' is still in stack
			// (i.e. it's a back edge, not cross edge).
			// Case 2 (per above discussion on Disc and Low value)
			else if (stackMember[v])
				low[u] = min(low[u], disc[v]);
		}

		// head node found, pop the stack and print an SCC
		int w = 0;  // To store stack extracted vertices
		if (low[u] == disc[u]) {
			comp.push_back({});
			while (st.top() != u) {
				w = (int)st.top();
				//cout << w << " ";
				comp.back().push_back(w);
				stackMember[w] = false;
				st.pop();
			}
			w = (int)st.top();
			//cout << w << "\n";
			comp.back().push_back(w);
			stackMember[w] = false;
			st.pop();
		}
	}

public:
	// Constructor
	Graph(vvi adj) {
		this->V = adj.size();
		this->adj = adj;
	}

	// prints strongly connected components
	// The function to do DFS traversal. It uses SCCUtil()
	void SCC() {
		vi disc(V, -1), low(V, -1);
		vb stackMember(V);
		stack<int> st;

		// Call the recursive helper function to find strongly
		// connected components in DFS tree with vertex 'i'
		for (int i = 0; i < V; i++)
			if (disc[i] == -1)
				SCCUtil(i, disc, low, st, stackMember);
	}
};

int main() {
	//FILE* stream;
	//freopen_s(&stream, "input.txt", "r", stdin);
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	cost.resize(n);

	Graph g1(n);
	for (int i = 0; i < n; i++)
		cin >> cost[i];
	int m; cin >> m;
	for (int i = 0; i < m; i++)
	{
		int u, v; cin >> u >> v;
		g1.addEdge(u - 1, v - 1);
	}
	g1.SCC();

	ll rn = 1, rs = 0;
	for (int i = 0; i < comp.size(); i++)
	{
		sort(comp[i].begin(), comp[i].end());
		ll tc = 0, mn = comp[i][0];
		while (tc < comp[i].size() && comp[i][tc] == mn)
			tc++;
		rs += mn, rn *= tc, rn %= 1000000007;
	}
	cout << rs << " " << rn << endl;
	//cin.ignore(), cin.get();
}
