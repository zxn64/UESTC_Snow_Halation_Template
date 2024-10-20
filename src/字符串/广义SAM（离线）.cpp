int n,num,cnt=1;
ll ans;
char s[N];
int to[qwq][26],ch[qwq][26];
int fa[qwq],len[qwq];
struct E{
	int id;
	int lst;
	int c;
};

inline void outing() {
	for(int u=1;u<=cnt;u++) {
		cout<<u<<" : fa="<<fa[u]<<" len="<<len[u]-len[fa[u]]<<"\n   ";
		for(int i=0;i<26;i++) {
			if(ch[u][i]) cout<<(char)('a'+i)<<"="<<ch[u][i]<<" ";
		}
		cout<<"\n";
	}
}

inline int insert(int u,int c) {
	int cur = ++cnt; len[cur] = len[u] + 1;
	for(; !ch[u][c] && u; u=fa[u]) ch[u][c] = cur;
	if(!u) fa[cur] = 1;
	else {
		int v =  ch[u][c];
		if(len[v]==len[u]+1) fa[cur] = v;
		else {
			int w = ++cnt; len[w] = len[u] + 1;
			memcpy(ch[w], ch[v], sizeof ch[w]);
			fa[w] = fa[v]; fa[v] = fa[cur] = w;
			for(; ch[u][c]==v && u; u=fa[u]) ch[u][c] = w;
		}
	}
	return cur;
}

int main() {
	scanf("%d",&n);
	for(int u=0,k=1;k<=n;k++) {
		scanf("%s",s); int len = strlen(s);
		u = 0;
		for(int i=0;i<len;i++) {
			int c = s[i]-'a';
			if(!to[u][c]) to[u][c] = ++num;
			u = to[u][c];
		}
	}
	queue <E> q;
	for(int i=0;i<26;i++) if(to[0][i]) q.push({to[0][i],1,i});
	while(!q.empty()) {
		E now = q.front(); q.pop();
		int u = now.id;
		int tmp = insert(now.lst,now.c);
		for(int i=0;i<26;i++) if(to[u][i]) q.push({to[u][i],tmp,i});
	}

	outing();
	for(int i=2;i<=cnt;i++) ans += len[i] - len[fa[i]];
	cout<<ans<<endl;
	cout<<cnt;
	return 0;
}

/*

4
aa
ab
bac
caa

*/

