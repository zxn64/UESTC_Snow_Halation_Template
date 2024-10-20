#include <bits/stdc++.h>
#include <vector>

using namespace std;

const int N=101010;
const int qwq = 303030;

int n,m;
int X[N],Y[N],Z[N];
int head[N],to[qwq],cnt=1,we[qwq],nxt[qwq];
int dfn[N],low[N],tim;
bool cut[N],br[qwq];


void add(int u,int v,int z) {
	to[++cnt] = v;
	we[cnt] = z;
	nxt[cnt] = head[u];
	head[u] = cnt;

	to[++cnt] = u;
	we[cnt] = z;
	nxt[cnt] = head[v];
	head[v] = cnt;
}

void tarjan(int u,int fa) {
	dfn[u] = low[u] = ++tim;
	int son = 0;
	for(int i=head[u]; i; i=nxt[i]) {
		int v = to[i];
		if(v==fa) continue;
		if(!dfn[v]) {
			if(!fa) son++;
			tarjan(v,u);
			low[u] = min(low[u],low[v]);
			if(fa && low[v]>=dfn[u]) cut[u] = 1;
			if(low[v]>dfn[u]) br[i] = 1, br[i^1] = 1;
		}
		else low[u] = min(low[u],dfn[v]);
	}
	if(son>=2) cut[u] = 1;
}

int main() {
	n = read(); m = read();
	for(int i=1;i<=m;i++) {
		X[i] = read(); Y[i] = read(); Z[i] = read();
		add(X[i],Y[i],Z[i]);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i,0);
	for(int i=1;i<=n;i++) {
		cout<<"cut["<<i<<"] = "<<cut[i]<<endl;
	}
	for(int i=2;i<=cnt;i++) {
		cout<<"to = "<<to[i]<<"  br = "<<br[i]<<"\n";
	}
	return 0;
}