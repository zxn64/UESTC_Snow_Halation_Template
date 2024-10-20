const ll N=101010;
const ll qwq=503030;
const ll inf=0x3f3f3f3f3f3f3f3f;

ll n,m,k;
ll dis[N],fa[N],head1[N],head2[N];
bool vis[N];
struct E{
	ll to,we,nxt,on;
} e[qwq],g[qwq]; ll cnt;
struct D{
	ll id,di;
};
bool operator < (D A,D B) { return A.di > B.di; }
priority_queue <D> q;

ll tot=0, rt[N<<4], ls[N<<4], rs[N<<4], dep[N<<4];
D tree[N<<4];


void add(ll u,ll v,ll z) {
	cnt++;
	e[cnt] = (E){v,z,head1[u],0}; head1[u] = cnt;
	g[cnt] = (E){u,z,head2[v],0}; head2[v] = cnt;
}

void DIJ() {
	memset(dis,0x3f,sizeof(dis));
	q.push({n,0}); dis[n] = 0;
	while(!q.empty()) {
		D now = q.top(); q.pop();
		ll u = now.id;
		if(dis[u]!=now.di) continue;
		for(ll i=head2[u]; i; i=g[i].nxt) {
			ll v = g[i].to, w = g[i].we;
			if(dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				q.push({v,dis[v]});
			}
		}
	}
}

ll addnew(ll u,ll di) { tree[++tot] = {u,di}; return tot; }

ll merge(ll x,ll y) {
	if(!x || !y) return x | y;
	if(tree[x] < tree[y]) swap(x,y);
	ll now = ++tot;
	tree[now] = tree[x];
	ls[now] = ls[x];
	rs[now] = merge(rs[x],y);
	if(dep[ls[now]] < dep[rs[now]]) swap(ls[now],rs[now]);
	dep[now] = dep[rs[now]] + 1;
	return now;
}

void DFS(ll u) {
	// cout<<"u = "<<u<<"\n";
	vis[u] = 1;
	for(ll i=head2[u]; i; i=g[i].nxt) {
		ll v = g[i].to;
		if(vis[v]) continue;
		if(dis[v] == dis[u]+g[i].we) {
			fa[v] = u;
			e[i].on = 1;
			DFS(v);
		}
	}
}

void DFS2(ll u) {
	// cout<<"  u = "<<u<<"\n";
	vis[u] = 1;
	if(fa[u]) rt[u] = merge(rt[u], rt[ fa[u] ]);
	for(ll i=head2[u]; i; i=g[i].nxt) {
		ll v = g[i].to;
		if(fa[v]==u && !vis[v]) DFS2(v);
	}
}

void built() {
	for(ll u=1;u<=n;u++) {
		if(dis[u]==inf) continue;
		for(ll i=head1[u]; i; i=e[i].nxt) {
			ll v = e[i].to;
			if(e[i].on || dis[v]==inf) continue;
			rt[u] = merge(rt[u],addnew(v,dis[v]-dis[u]+e[i].we));
		}
	}
}

int main() {
	ll x,y,z;
	n = read(); m = read(); k = read();
	for(ll i=1;i<=m;i++) {
		x = read(); y = read(); z = read();
		add(x,y,z);
	}
	DIJ(); DFS(n);
	if(k==1) { cout<<dis[1]; return 0; }
	memset(vis,0,sizeof(vis));
	built();
	DFS2(n);

	q.push( {rt[1], tree[rt[1]].di} );
	while(!q.empty()) {
		D now = q.top(); q.pop();
		ll u = now.id, w = now.di;
		k--; if(k==1) { cout<<dis[1]+w; return 0; }
		if(ls[u]) q.push( {ls[u], w-tree[u].di+tree[ls[u]].di} );
		if(rs[u]) q.push( {rs[u], w-tree[u].di+tree[rs[u]].di} );
		ll v = rt[ tree[u].id ];
		if(v) q.push( {v, w+tree[v].di} );
	}
	return 0;
}