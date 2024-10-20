void JI(int u) {
	nowans += f[u];
	FOR() JI(e[u][i]);
}

void JIA(int u,int cl) {
	f[u] += cl;
	FOR() JIA(e[u][i],cl);
}

void DSU(int u,bool shan) {
	FOR() {
		int v = e[u][i];
		if(v==son[u]) continue;
		DSU(v,1);
	}

	if(son[u]) DSU(son[u],0);

	for(int i=0;i<le;i++) {
		int v = e[u][i];
		if(v==son[u]) continue;
		JI(v); JIA(v,1);
	}

	if(shan) JIA(u,-1);
}