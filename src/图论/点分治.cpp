int n,Q;
struct E{ int to,we; };
vector <E> e[N];
int q[N],ans[N];
int big[N],sss,rt;
int siz[N],vis[N],dis[N];
int st[N],cnt;
int st2[N],cnt2;
bool f[qwq];

void getid(int u,int fa) {
	siz[u] = 1; big[u] = 0;
	FOR() {
		int v = e[u][i].to;
		if(v==fa || vis[v]) continue;
		getid(v,u);
		siz[u] += siz[v];
		big[u] = max(big[u],siz[v]);
	}
	big[u] = max(big[u],sss-siz[u]);
	if(big[u] < big[rt]) rt = u;
}

void DFS(int u,int fa) {
	if(dis[u]>10000000) return ;
	st[++cnt] = dis[u];
	FOR() {
		int v = e[u][i].to;
		if(vis[v] || v==fa) continue;
		dis[v] = dis[u] + e[u][i].we;
		DFS(v,u);
	}
}

void calc(int u) {
	FOR() {
		int v = e[u][i].to;
		if(vis[v]) continue;
		dis[v] = e[u][i].we;
		DFS(v,u);
		for(int j=1;j<=cnt;j++) {
			int d = st[j];
			for(int l=1;l<=Q;l++)
				if(q[l]>=d) ans[l] |= f[q[l]-d];
		}
		while(cnt) {
			f[ st[cnt] ] = 1;
			st2[++cnt2] = st[cnt--];
		}
	}
	while(cnt2) f[st2[cnt2--]] = 0;
}

void TREE(int u) {
	vis[u] = f[0] = 1;    // only TREE->u  is  visited.
	calc(u);
	FOR() {
		int v = e[u][i].to;
		if(vis[v]) continue;
		big[rt=0] = sss = siz[v];
		getid(v,0);
		TREE(rt);
	}
}

int main() {
	int x,y,z;
	n = read(); Q = read();
	for(int i=1;i<n;i++) {
		x = read(); y = read(); z = read();
		e[x].push_back((E){y,z});
		e[y].push_back((E){x,z});
	}
	for(int i=1;i<=Q;i++) q[i] = read();
	big[rt=0] = sss = n;
	getid(1,0);
	TREE(rt);
	for(int i=1;i<=Q;i++) {
		if(ans[i]) printf("AYE\n");
		else       printf("NAY\n");
	}
	return 0;
}