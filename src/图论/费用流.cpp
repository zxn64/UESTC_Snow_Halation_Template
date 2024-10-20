const int N=101010;
const int qwq=303030;
const int inf=0x3f3f3f3f;

int n,m,s,t,cnt=1,maxflow,mincost;
struct E{ int to,nxt,cap,we; } e[N];
int head[N],dep[N],vis[N],cur[N];
queue <int> q;

inline void add(int u,int v,int w,int z) {
	e[++cnt] = (E){ v,head[u],w,z };  head[u] = cnt;
	e[++cnt] = (E){ u,head[v],0,-z }; head[v] = cnt;
}

bool SPFA() {
	for(int i=0;i<=t;i++) cur[i] = head[i], vis[i] = 0, dep[i] = inf;
	dep[s] = 0; q.push(s);
	while(!q.empty()) {
		int u = q.front(); q.pop(); vis[u] = 0;
		for(int i=head[u]; i; i=e[i].nxt) {
			int v = e[i].to, w = e[i].we;
			if(e[i].cap && dep[v] > dep[u]+w) {
				dep[v] = dep[u]+w;
				if(vis[v]) continue;
				q.push(v); vis[v] = 1;
			}
		}
	}
	return dep[t] != inf;
}

int DFS(int u,int flow) {
	int res = 0, f;
	if(u==t || !flow) return flow;
	vis[u] = 1;
	for(int i=cur[u]; i; i=e[i].nxt) {
		cur[u] = i;
		int v = e[i].to, w = e[i].we;
		if(vis[v]) continue;
		if(e[i].cap && dep[v]==dep[u]+w) {
			f = DFS( v, min(e[i].cap,flow-res) );
			if(f) {
				res += f;
				e[i].cap -= f;
				e[i^1].cap += f;
				mincost += f * w;
				if(res==flow) break;
			}
		}
	}
	return res;
}

int main() {
	int x,y,z,w;
	n = read(); m = read(); s = read(); t = read();
	while(m--) {
		x = read(); y = read(); z = read(); w = read();
		add(x,y,z,w);
	}
	while( SPFA() ) maxflow += DFS(s,inf);
	cout<<maxflow<<" "<<mincost;
	return 0;
}