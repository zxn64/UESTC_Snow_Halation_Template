int n,m;
int qiao,tot,dian,da,shuang;
int bian;
int dfn[N],low[N],tim;
int st[N],cnt;
bool in[N];
vector <int> e[N],d[N];


void tarjan(int u,int zu) {
	dfn[u] = low[u] = ++tim;
	st[++cnt] = u;
	int son = 0;
	FOR() {
		int v = e[u][i];
		if(!dfn[v]) {
			son++;
			tarjan(v,zu);
			low[u] = min(low[u],low[v]);
			if(low[v]==dfn[u]) {
				++tot;
				while(1) {
					int now = st[cnt--];
					d[tot].push_back(now);
					d[now].push_back(tot);
					if(now==v) break;
				}
				d[tot].push_back(u);
				d[u].push_back(tot);
			}
		}
		else low[u] = min(low[u],dfn[v]);
	}
	if(u==zu) cnt = 0;
}

int query(int fang) {
	int res = 0;
	for(int i=0;i<d[fang].size();i++) in[ d[fang][i] ] = 1;
	for(int i=0;i<d[fang].size();i++) {
		int u = d[fang][i];
		for(int j=0;j<e[u].size();j++) {
			int v = e[u][j];
			if(in[v]) res++;
		}
	}
	for(int i=0;i<d[fang].size();i++) in[ d[fang][i] ] = 0;
	return res/2;
}

int main() {
	int x,y;
	n = read(); m = read(); tot = n;
	for(int i=1;i<=m;i++) {
		x = read(); y = read();
		e[x].push_back(y);
		e[y].push_back(x);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i,i);

	for(int i=1;i<=n;i++) if(d[i].size()>=2) dian++;

	for(int i=n+1;i<=tot;i++) {
		if(d[i].size()==2) bian++;
		if(d[i].size()>=2) shuang++;
	}

	for(int i=n+1;i<=tot;i++)
		da = max(da,query(i));
	cout<<dian<<" "<<bian<<" "<<shuang<<" "<<da;
	return 0;
}
