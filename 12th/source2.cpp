#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

// integer pair
typedef  pair<int, int> iPair;

// Graph
struct Graph
{
	int V, E; // vertex 개수, edge 개수
	std::vector< pair<int, iPair> > edges;
	// Constructor
	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
	}
	// Graph에 Edge 추가 function
	void addEdge(int u, int v, int w)
	{
		edges.push_back({ w,{ u, v } });
	}

	// MST 찾는 알고리즘		
	int kruskalMST();
};

// Disjoint Sets
struct DisjointSets
{
	int *parent, *rnk;
	int n;

	// Constructor.
	DisjointSets(int V)
	{
		// Allocate memory
		n = V;
		parent = (int *)malloc(sizeof(int)*(n + 1));
		rnk = (int *)malloc(sizeof(int)*(n + 1));

		// Initially, all vertices are in
		// different sets and have rank 0.
		for (int i = 0; i <= n; i++)
		{
			rnk[i] = 0;
			//every element is parent of itself
			parent[i] = i;
		}
	}

	~DisjointSets() {
		free(parent);
		free(rnk);
	}

	// Find the parent of a node 'u'
	// Path Compression
	int find(int u)
	{
		/* Make the parent of the nodes in the path
		from u--> parent[u] point to parent[u] */
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	// Union by rank
	void merge(int x, int y)
	{
		x = find(x);
		y = find(y);
		/* Make tree with smaller height
		a subtree of the other tree  */
		if (rnk[x] > rnk[y])
			parent[y] = x;
		else // If rnk[x] <= rnk[y]
			parent[x] = y;
		if (rnk[x] == rnk[y])
			rnk[y]++;
	}
};

/* Functions returns weight of the MST*/

int Graph::kruskalMST()
{
	int mst_wt = 0; // (최소 멀미값)
	// Create disjoint sets
	DisjointSets ds(V);

	sort(edges.begin(), edges.end());
	std::vector<pair<int, iPair>>::iterator it;

	for (it = edges.begin(); it != edges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.find(u);
		int set_v = ds.find(v);
		// Check if the selected edge is creating
		// a cycle or not (Cycle is created if u
		// and v belong to same set)
		if (set_u != set_v)
		{
			mst_wt += it->first;
			// Merge two sets
			ds.merge(set_u, set_v);
		}
	}

	return mst_wt;
}

// Driver program to test above functions
int main()
{
	int tc, i;
	int regionCount, roadCount;
	int from, to, add, min;

	scanf("%d", &tc);
	for (tc; tc > 0; tc--) {
		scanf("%d %d", &regionCount, &roadCount);

		Graph g(regionCount, roadCount); // MST를 만들기 위해서 사용하는 Graph

		for (i = 0; i < roadCount; i++) {
			scanf("%d %d %d", &from, &to, &add);
			g.addEdge(from, to, add);
		}
		min = g.kruskalMST();
		printf("%d\n", min);
	}
	return 0;
}