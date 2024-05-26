#include <cstring>
#include <vector>

using namespace std;

class StronglyConnectedComponent
{
public:
	static const int maxn = 100000;

	int n, m;
	vector<int> E[maxn];
	vector<int> Er[maxn];
	vector<int> vec;
	int scc_cnt;
	int sccno[maxn];
	vector<int> scc[maxn];
	bool vis[maxn];

	StronglyConnectedComponent(void) : n(0), m(0)
	{

	}

	void resize(const int & n)
	{
		for (int i = 0; i < this->n; i++)
		{
			E[i].clear();
			Er[i].clear();
		}
		this->n = n;
	}

	void add_edge(const int & u, const int & v)
	{
		E[u].push_back(v);
		Er[v].push_back(u);
	}

	void dfs(const int & u)
	{
		if(!vis[u])
		{
			vis[u] = true;
			for (const auto & v : E[u])
				dfs(v);
			vec.push_back(u);
		}
	}

	void dfsr(const int & u)
	{
		if(sccno[u] == -1)
		{
			sccno[u] = scc_cnt;
			scc[scc_cnt].push_back(u);
			for (const auto & v : Er[u])
				dfsr(v);
		}
	}

	void find_scc(void)
	{
		vec.clear();
		memset(vis, false, sizeof vis[0] * n);
		for (int i = 0; i < n; i++)
		{
			if (!vis[i])
				dfs(i);
		}

		for (int i = 0; i < scc_cnt; i++)
			scc[i].clear();
		scc_cnt = 0;
		memset(sccno, -1, sizeof sccno[0] * n);
		for (int i = n - 1; i >= 0; i--)
		{
			if (sccno[vec[i]] == -1)
			{
				dfsr(vec[i]);
				scc_cnt++;
			}
		}
	}
};
