#include <stack>
#include <vector>

using namespace std;

const int maxn = 1000;

class Edge
{
private:
protected:
public:
	int u;
	int v;

	Edge(void);
	Edge(const int &, const int &);
};

Edge::Edge(void) : u(0), v(0)
{

}

Edge::Edge(const int & u, const int & v) : u(u), v(v)
{

}

int n, m;
bool R[maxn+1][maxn+1];
vector<int> E[maxn+1];
int dfs_clock;
int low[maxn+1];
int pre[maxn+1];
bool iscut[maxn+1];
int bcc_cnt;
int bccno[maxn+1];
vector<int> bcc[maxn+1];
char clr[maxn+1];
bool odd[maxn+1];

stack<Edge> stk;

int dfs(int u, int dad)
{
	int i;
	int v;
	int child;
	Edge e;

	++dfs_clock;
	low[u] = dfs_clock;
	pre[u] = dfs_clock;

	child = 0;
	for(i=0 ; i<E[u].size() ; ++i)
	{
		v = E[u][i];
		if(pre[v] == 0)
		{
			stk.push(Edge(u, v));
			++child;

			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] >= pre[u])
			{
				iscut[u] = true;
				++bcc_cnt;
				bcc[bcc_cnt].clear();
				for( ; ; )
				{
					e = stk.top();
					stk.pop();

					if(bccno[e.u] != bcc_cnt)
					{
						bccno[e.u] = bcc_cnt;
						bcc[bcc_cnt].push_back(e.u);
					}
					
					if(bccno[e.v] != bcc_cnt)
					{
						bccno[e.v] = bcc_cnt;
						bcc[bcc_cnt].push_back(e.v);
					}

					if(u==e.u && v==e.v)
						break;
				}
			}
		}
		else if(pre[v]<pre[u] && v!=dad)
		{
			stk.push(Edge(u, v));
			low[u] = min(low[u], pre[v]);
		}
	}

	if(dad<0 && child==1)
		iscut[u] = false;

	return low[u];
}

void find_bcc(void)
{
	int i;

	memset(pre+1, 0, sizeof(int)*n);
	memset(iscut+1, false, sizeof(bool)*n);
	memset(bccno+1, 0, sizeof(int)*n);
	
	dfs_clock = 0;
	bcc_cnt = 0;
	for(i=1 ; i<=n ; ++i)
	{
		if(pre[i] == 0)
			dfs(i, -1);
	}
}
