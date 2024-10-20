#include <bits/stdc++.h>
#define ll long long

using namespace std;
const ll N=101010;
const ll inf=0x3f3f3f3f;

ll n,m,s,t,ss,tt;
struct EE{ ll u,v,l,r; } a[N]; ll cnta;
ll du[N];
struct E{
	ll to,nxt,cap;
}e[N];
ll cnt = 1;
ll head[N],cur[N];
ll dep[N],vis[N];
queue <ll> q;

inline void add(ll u,ll v,ll w) {
	// cout<<u<<" -> "<<v<<" "<<w<<endl;
	e[++cnt] = (E){ v,head[u],w }; head[u] = cnt;
	e[++cnt] = (E){ u,head[v],0 }; head[v] = cnt;
}

inline bool SPFA(ll S,ll T) {
	for(ll i=0;i<=tt;i++) dep[i] = inf, vis[i] = 0, cur[i] = head[i];
	q.push(S); dep[S] = 0;
	while(!q.empty()) {
		ll u = q.front(); q.pop();
		vis[u] = 0;
		for(ll i=head[u]; i; i=e[i].nxt) {
			ll v = e[i].to;
			if(dep[v] > dep[u] + 1 && e[i].cap) {
				dep[v] = dep[u] + 1;
				if(vis[v]) continue;
				q.push(v);
				vis[v] = 1;
			}
		}
	}
	return dep[T]!=inf;
}

ll DFS(ll u,ll goal,ll flow) {
	ll res = 0, f;
	if(u==goal || !flow) return flow;
	for(ll i=cur[u]; i; i=e[i].nxt) {
		cur[u] = i;
		ll v = e[i].to;
		if(e[i].cap && (dep[v] == dep[u]+1)) {
			f = DFS(v,goal,min(flow-res,e[i].cap));
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

ll solve() {
	ll ans1 = 0, ans2 = 0, cha = 0;
	for(ll i=1;i<=cnta;i++) {
		ll u = a[i].u, v = a[i].v;
		du[u] += a[i].l;
		du[v] -= a[i].l;
		add(u, v, a[i].r-a[i].l);
	}
	ll lim = cnt;
	for(ll u=s;u<=t;u++) {
		if(du[u]>0) add(u,tt,du[u]), cha += du[u];
		if(du[u]<0) add(ss,u,-du[u]);
	}
	add(t,s,inf);
	while(SPFA(ss,tt)) cha -= DFS(ss,tt,inf);
	if(cha) return -1;

	ans1 = e[cnt].cap;

	for(ll i=lim+1;i<=cnt;i++) e[i].cap = 0;
	while(SPFA(s,t)) ans2 += DFS(s,t,inf);

	return ans1+ans2;
}

void chushihua() {
	cnt = 1;
	cnta = 0;
	for(ll i=0;i<=tt;i++) head[i] = du[i] = 0;
}

int main() {
	ll x,y,l,r;
	while(scanf("%lld%lld",&n,&m)!=EOF) {
		chushihua();

		s = 0; t = n+m+1; ss = n+m+2; tt = n+m+3;

		for(int i=1;i<=m;i++) {
			x = read(); y = read(); l = read(); r = read();
			a[++cnta] = {x,y,l,r};
		}

		cout<<solve()<<"\n\n";
	}
	return 0;
}