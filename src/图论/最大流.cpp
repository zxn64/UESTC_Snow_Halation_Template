const int N=101010;
const int qwq=303030;
const int inf=0x3f3f3f3f;

int n,m,s,t;
struct E{
	int to,nxt,cap;
}e[qwq];
int cnt = 1;
int head[N],cur[N];
int dep[N],vis[N];
queue <int> q;

inline void add(int u,int v,int w) {
	e[++cnt] = (E){ v,head[u],w }; head[u] = cnt;
	e[++cnt] = (E){ u,head[v],0 }; head[v] = cnt;
}

inline bool SPFA() {
	for(int i=s;i<=t;i++) dep[i] = inf, vis[i] = 0, cur[i] = head[i];
	q.push(s); dep[s] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = 0;
		for(int i=head[u]; i; i=e[i].nxt) {
			int v = e[i].to;
			if(dep[v] > dep[u] + 1 && e[i].cap) {
				dep[v] = dep[u] + 1;
				if(vis[v]) continue;
				q.push(v);
				vis[v] = 1;
			}
		}
	}
	return dep[t]!=inf;
}

int DFS(int u,int flow) {
	int res = 0, f;
	if(u==t || !flow) return flow;
	for(int i=cur[u]; i; i=e[i].nxt) {
		cur[u] = i;
		int v = e[i].to;
		if(e[i].cap && (dep[v] == dep[u]+1)) {
			f = DFS(v,min(flow-res,e[i].cap));
			if(f) {
				res += f;
				e[i].cap -= f;
				e[i^1].cap += f;
				if(res==flow) break;
			}
		}
	}
	return res;
}


int main() {
	int x,y,z;
	n = read(); m = read(); s = read(); t = read();
	while(m--) {
		x = read(); y = read(); z = read();
		add(x,y,z);
	}
	int max_flow = 0;
	while(SPFA()) max_flow += DFS(s,inf);
	cout<<max_flow;
	return 0;
}
