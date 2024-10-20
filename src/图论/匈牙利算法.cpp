const int N=101010;
const int qwq=303030;
const int inf=0x3f3f3f3f;
int n,m,k;
int ans;
int vis[N],belong[N];  // index is the right_part of G(V,E)
int mp[1234][1234];

bool DFS(int u) {
	for(int i=1;i<=m;i++) {
		if(!mp[u][i] || vis[i]) continue; vis[i] = 1;
		if(!belong[i] || DFS(belong[i])) { belong[i] = u; return 1; }
	}
	return 0;
}

int main() {
	int x,y;
	scanf("%d%d%d",&n,&m,&k);
	while(k--) { scanf("%d%d",&x,&y); mp[x][y] = 1; }
	for(int i=1;i<=n;i++) {
		memset(vis,0,sizeof(vis));
		if(DFS(i)) ans++;
	}
	cout<<ans;
	return 0;
}
