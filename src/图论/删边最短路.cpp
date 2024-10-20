#include <bits/stdc++.h>
#define ll long long
#define ls now<<1
#define rs now<<1|1

using namespace std;
const ll N=202020;
const ll inf=0x3f3f3f3f3f3f3f3f;

ll n,m,Q;
ll X[N],Y[N],Z[N];
struct E{
	ll to,we,id;
};
vector <E> e[N];
ll dis1[N],dis2[N],L[N],R[N],pre[N];
ll vis[N],in[N],da;
struct D {
	ll id,di;
};
inline bool operator < (D A,D B) { return A.di > B.di; }
priority_queue <D> q;

void DIJ(ll s,ll *dis,ll cl) {
	for(ll i=1;i<=n;i++) dis[i] = inf;
	dis[s] = 0;
	q.push({s,0});
	while(!q.empty()) {
		D now = q.top(); q.pop();
		ll u = now.id;
		if(dis[u]!=now.di) continue;
		for(E vv : e[u]) {
			ll v = vv.to;
			if(dis[v] > dis[u]+vv.we) {
				dis[v] = dis[u]+vv.we;
				pre[v] = vv.id;
				if(cl==1 && !vis[v]) L[v] = L[u];
				if(cl==2 && !vis[v]) R[v] = R[u];
				q.push({v,dis[v]});
			}
		}
	}
}

void access() {
	ll u = 1;
	vis[u] = 1; L[u] = R[u] = 0;
	while(u!=n) {
		ll id = pre[u];
		in[id] = ++da;
		u ^= X[id] ^ Y[id];
		vis[u] = 1;
		L[u] = R[u] = da;
	}
}

ll t[N<<2];
void built(ll now,ll l,ll r) {
	t[now] = inf;
	if(l==r) return ;
	ll mid = l+r >> 1;
	built(ls, l, mid);
	built(rs, mid+1, r);
}

void insert(ll now,ll l,ll r,ll x,ll y,ll g) {
	if(x<=l && r<=y) { t[now] = min(t[now],g); return; }
	ll mid = l+r >> 1;
	if(x<=mid) insert(ls, l, mid, x, y, g);
	if(y>mid)  insert(rs, mid+1, r, x, y, g);
}

ll query(ll now,ll l,ll r,ll x) {
	if(l==r) return t[now];
	ll mid = l+r >> 1, res = t[now];
	if(x<=mid) res = min(res, query(ls, l, mid, x));
	else       res = min(res, query(rs, mid+1, r, x));
	return res;
}

int main() {
	n = read(); m = read(); Q = read();
	for(ll i=1;i<=m;i++) {
		X[i] = read(); Y[i] = read(); Z[i] = read();
		e[X[i]].push_back({Y[i],Z[i],i});
		e[Y[i]].push_back({X[i],Z[i],i});
	}
	DIJ(n, dis2, 0);
	access();
	DIJ(1, dis1, 1);
	DIJ(n, dis2, 2);
	built(1, 1, da);
	for(ll i=1;i<=m;i++) {
		if(!in[i]) {
			ll u = X[i], v = Y[i];
			if(L[u]<R[v]) insert(1, 1, da, L[u]+1, R[v], dis1[u]+dis2[v]+Z[i]);
			if(L[v]<R[u]) insert(1, 1, da, L[v]+1, R[u], dis1[v]+dis2[u]+Z[i]);
		}
	}
	ll id,x;
	while(Q--) {
		id = read(); x = read();
		ll ans = dis1[n];
		if(!in[id]) {
			if(x<Z[id]) {
				ans = min(ans, dis1[X[id]]+dis2[Y[id]]+x);
				ans = min(ans, dis1[Y[id]]+dis2[X[id]]+x);
			}
		}
		else {
			ans = ans-Z[id]+x;
			if(x>Z[id]) {
				ans = min(ans, query(1, 1, da, in[id]));
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}