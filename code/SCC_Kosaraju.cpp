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
const int di[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
const int dj[] = { 0, 1, 0, -1, -1, 1, -1, 1 };
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const long double EPS = 1e-10;
#define all(n) n.begin(),n.end()

vvi scc;

class Graph
{
	int V;
	list<int> *adj;
	void fillOrder(int v, bool visited[], stack<int> &Stack);
	void DFSUtil(int v, bool visited[]);
public:
	Graph(int V);
	void addEdge(int v, int w);
	void printSCCs();
	Graph getTranspose();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::DFSUtil(int v, bool visited[])
{
	visited[v] = true;
	scc.back().push_back(v);

	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFSUtil(*i, visited);
}

Graph Graph::getTranspose()
{
	Graph g(V);
	for (int v = 0; v < V; v++)
	{
		list<int>::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i)
		{
			g.adj[*i].push_back(v);
		}
	}
	return g;
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
{
	visited[v] = true;

	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			fillOrder(*i, visited, Stack);

	Stack.push(v);
}

void Graph::printSCCs()
{
	stack<int> Stack;

	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			fillOrder(i, visited, Stack);

	Graph gr = getTranspose();

	for (int i = 0; i < V; i++)
		visited[i] = false;

	while (Stack.empty() == false)
	{
		int v = Stack.top();
		Stack.pop();

		if (visited[v] == false)
		{
			scc.push_back({});
			gr.DFSUtil(v, visited);
		}
	}
}