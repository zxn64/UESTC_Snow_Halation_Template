int n,m,rt,p;
int a[N];
vector <int> e[N];
int siz[N],fa[N],son[N],dep[N];
int cnt,tp[N],id[N],w[N];
ll tree[qwq],tag[qwq];

void DFS1(int u,int f) {
	dep[u] = dep[f] + 1; siz[u] = 1; fa[u] = f;
	FOR() {
		int v = e[u][i];
		if(v==f) continue;
		DFS1(v,u);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}

void DFS2(int u,int zuzu) {
	tp[u] = zuzu; id[u] = ++cnt; w[cnt] = a[u];
	if(son[u]) DFS2(son[u],zuzu);
	FOR() {
		int v = e[u][i];
		if(v==fa[u] || v==son[u]) continue;
		DFS2(v,v);
	}
}

inline void add(int x,int y,int g) {
	while(tp[x] != tp[y]) {
		if(dep[tp[x]] < dep[tp[y]]) swap(x,y);
		insert(1, 1, n, id[tp[x]], id[x], g);
		x = fa[ tp[x] ];
	}
	if(dep[x] > dep[y]) swap(x,y);
	insert(1, 1, n, id[x], id[y], g);
}

inline int ask(int x,int y) {
	ll res = 0;
	while(tp[x] != tp[y]) {
		if(dep[tp[x]] < dep[tp[y]]) swap(x,y);
		(res += query(1, 1, n, id[tp[x]], id[x])) %= p;
		x = fa[ tp[x] ];
	}
	if(dep[x] > dep[y]) swap(x,y);
	(res += query(1, 1, n, id[x], id[y])) %= p;
	return res;
}

int main() {
	int x,y,z,cz;
	n = read(); m = read(); rt = read(); p = read();
	for(int i=1;i<=n;i++) a[i] = read();
	for(int i=1;i<n;i++) {
		x = read(); y = read();
		e[x].push_back(y);
		e[y].push_back(x);
	}
	DFS1(rt,rt);
	DFS2(rt,rt);
	built(1, 1, n);
	while(m--) {
		cz = read(); x = read();
		if(cz==1) { y = read(); z = read(); add(x,y,z); }
		if(cz==2) { y = read(); printf("%d\n",ask(x,y)); }
		if(cz==3) { z = read(); insert(1, 1, n, id[x], id[x]+siz[x]-1, z); }
		if(cz==4) { printf("%d\n",query(1, 1, n, id[x], id[x]+siz[x]-1)); }
	}
	return 0;
}