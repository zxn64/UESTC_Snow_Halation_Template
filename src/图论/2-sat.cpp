#include <bits/stdc++.h>
#define FOR() int le=e[u].size();for(int i=0;i<le;i++)
#define QWQ cout<<"QwQ"<<endl;
#define ll long long
#include <vector>
#include <map>

using namespace std;
const int N=2010101;
const int qwq=303030;
const int inf=0x3f3f3f3f;

int n,m;
int belong[N],tot=0,low[N],dfn[N],tim=0;
int in[N],cnt,st[N];
vector <int> e[N];

void tarjan(int u) {
	dfn[u] = low[u] = ++tim;
	st[++cnt] = u; in[u] = 1;
	FOR() {
		int v = e[u][i];
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u],low[v]);
		}
		else if(in[v]) low[u] = min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		tot++;
		while(1) {
			int v = st[cnt--]; in[v] = 0;
			belong[v] = tot;
			if(v==u) break;
		}
	}
}

int main() {
	int x,lx,y,ly;
	n = read(); m = read();
	while(m--) {
		x = read(); lx = read(); y = read(); ly = read();
		if(!lx) x += n;   // x is false
		if(!ly) y += n;
		if(x>n) e[x-n].push_back(y); // if !x : y
		else    e[x+n].push_back(y);
		if(y>n) e[y-n].push_back(x);
		else    e[y+n].push_back(x);
	}
	for(int i=1;i<=2*n;i++)
		if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;i++) if(belong[i]==belong[i+n]) { printf("IMPOSSIBLE"); return 0; }
	printf("POSSIBLE\n");
	for(int i=1;i<=n;i++) {
		if(belong[i] > belong[i+n]) cout<<"0 ";   // (i) -> (i+n)   so i is false
		else                        cout<<"1 ";
	}
	return 0;
}