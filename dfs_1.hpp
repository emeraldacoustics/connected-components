#include <vector>

using namespace std;

const int maxP = 10000;

int P, C;
vector<int> E[maxP];
int clk;
int pre[maxP];
int low[maxP];

int dfs(int u, int dad)
{
	int i;
	int v;
	int child, cnt;

	++clk;
	pre[u] = clk;
	low[u] = clk;

	child = 0;
	cnt = 0;
	for(i=0 ; i<E[u].size() ; ++i)
	{
		v = E[u][i];

		if(pre[v] == 0)
		{
			++child;

			dfs(v, u);
			minimize(low[u], low[v]);
			if(low[v] >= pre[u])
				++cnt;
		}
		else if(v != dad)
			minimize(low[u], pre[v]);
	}

	if(dad == -1)
		f[u] = child;
	else
		f[u] = cnt+1;

	return low[u];
}
