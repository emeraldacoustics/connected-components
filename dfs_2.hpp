#include <cstring>
#include <stack>
#include <vector>

using namespace std;

class Edge
{
private:
protected:
public:
	int u;
	int v;
	int id;

	Edge(void);
	Edge(const int &, const int &, const int &);
};

Edge::Edge(void) : u(0), v(0), id(0)
{

}

Edge::Edge(const int &u, const int &v, const int &id) : u(u), v(v), id(id)
{

}

const int maxN = 100000;
const int maxM = 100000;

const int maxvsz = maxN;
const int maxesz = maxM;

int N, M;
int vsz, esz;
vector<Edge> E[maxvsz];
int dfs_clock;
int pre[maxvsz];
int low[maxvsz];
int ebcccnt;
int ebccno[maxvsz];
vector<int> Ebcc[maxvsz];
int parent[maxvsz];
bool evis[maxesz];
stack<int> ebcc_stk;

inline void dfs_ebcc(const int &u, const int &dad)
{
	++dfs_clock;
	pre[u] = dfs_clock;
	low[u] = dfs_clock;
	parent[u] = dad;

	ebcc_stk.push(u);
	for(auto edge : E[u])
	{
		int v = edge.v, id = edge.id;

		if(pre[v] == 0)
		{
			evis[id] = true;

			dfs_ebcc(v, u);
			low[u] = min(low[u], low[v]);
		}
		else if(pre[v] < pre[u] && !evis[id])
		{
			evis[id] = true;
			low[u] = min(low[u], pre[v]);
		}
	}

	if(low[u] == pre[u])
	{
		for(ebccno[u] = ebcccnt; ebcc_stk.top() != u; ebcc_stk.pop())
			ebccno[ebcc_stk.top()] = ebcccnt;
		ebcc_stk.pop();
		++ebcccnt;
	}
}

inline void find_ebcc(void)
{
	for (int i = 0; i < vsz; ++i)
	{
		if (pre[i] == 0)
			dfs_ebcc(i, -1);
	}
	for (int i = 0; i < vsz; ++i)
	{
		if (parent[i] != -1 && ebccno[i] != ebccno[parent[i]])
		{
			int u = ebccno[i], v = ebccno[parent[i]];

			Ebcc[u].push_back(v);
			Ebcc[v].push_back(u);
		}
	}
}

inline void clear_ebcc(void)
{
	dfs_clock = 0;
	memset(pre, 0, sizeof pre[0] * vsz);
	memset(evis, false, sizeof evis[0] * esz);

	for (int i = 0; i < ebcccnt; ++i)
		Ebcc[i].clear();
	ebcccnt = 0;
}

