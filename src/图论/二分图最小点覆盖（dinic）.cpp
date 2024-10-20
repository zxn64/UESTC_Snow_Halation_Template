#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int N=101010;
const int qwq=303030;
const int inf=0x3f3f3f3f;

int n1,n2,m,s,t;
int ans;
struct E{
	int to,nxt,cap;
}e[qwq];
int cnt = 1;
int head[N],cur[N];
int dep[N],vis[N];
queue <int> q;
int tag[N],belong[N];

inline void add(int u,int v,int w) {
	// cout<<u<<" -> "<<v<<" "<<w<<endl;
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

void mark(int u) {
	if(tag[u]) return ;
	tag[u] = 1;
	for(int i=head[u]; i; i=e[i].nxt) {
		int v = e[i].to;
		if(v==s) continue;
		if(!tag[v] && belong[v]) {
			tag[v] = 1;
			mark(belong[v]);
		}
	}
}

int main() {
	int x,y;
	n1 = read(); n2 = read(); m = read(); s = 0; t = n1+n2+1;
	for(int i=1;i<=n1;i++) add(s,i,1);
	for(int i=1;i<=n2;i++) add(i+n1,t,1);
	while(m--) {
		x = read(); y = read();
		add(x,y+n1,1);
	}
	while(SPFA()) ans += DFS(s,inf);

	for(int u=n1+1;u<t;u++) {
		for(int i=head[u]; i; i=e[i].nxt) {
			int v = e[i].to;
			if(e[i].cap && v!=t) vis[v] = 1, belong[u] = v;
		}
	}
	for(int i=1;i<=n1;i++) if(!vis[i]) mark(i);

	for(int i=1;i<=n1;i++) if(!tag[i]) cout<<i<<" ";
	cout<<endl;
	for(int i=n1+1;i<t;i++) if(tag[i]) cout<<i<<" ";
	cout<<endl;
	return 0;
}

/*

4 4 7
1 1
2 2
1 3
2 3
2 4
3 2
4 2

*/
