#include <bits/stdc++.h>
#define FOR() int le=e[u].size();for(int i=0;i<le;i++)
#define ls L[now]
#define rs R[now]

using namespace std;
const int N=101010;
const int big = 100000;

int n,m;
vector <int> e[N];
int t[N*20],d[N*20],rt[N],cnt,L[N*20],R[N*20];
int dep[N],f[N][22];
int ans[N];

void DFS(int u,int fa) {
	f[u][0] = fa;
	dep[u] = dep[fa] + 1;
	FOR() {
		int v = e[u][i];
		if(v==fa) continue;
		DFS(v,u);
	}
}

inline int LCA(int x,int y) {
	if(dep[x]<dep[y]) swap(x,y);
	for(int k=20;k>=0;k--)
		if(dep[ f[x][k] ] >= dep[y]) x = f[x][k];
	if(x==y) return x;
	for(int k=20;k>=0;k--)
		if(f[x][k] != f[y][k])
			x = f[x][k], y = f[y][k];
	return f[x][0];
}

inline void pushup(int now) {     // 合并次数最多的颜色，相同则选择左侧
	if(d[ls]>=d[rs]) d[now] = d[ls], t[now] = t[ls];
	else             d[now] = d[rs], t[now] = t[rs];
}

void insert(int &now,int l,int r,int x,int g) {
	if(!now) now = ++cnt;
	if(l==r) { d[now] += g; t[now] = l; return ; }
	int mid = l+r >> 1;
	if(x<=mid) insert(ls, l, mid, x, g);
	else       insert(rs, mid+1, r, x, g);
	pushup(now);
}

int merge(int r1,int r2,int l,int r) {
	if(!r1 || !r2) return r1 + r2;
	if(l==r) {
		d[r1] += d[r2];
		return r1;
	}
	int mid = l+r >> 1;
	L[r1] = merge(L[r1], L[r2], l, mid);
	R[r1] = merge(R[r1], R[r2], mid+1, r);
	pushup(r1);
	return r1;
}

void hebing(int u) {
	FOR() {
		int v = e[u][i];
		if(v==f[u][0]) continue;
		hebing(v);
		rt[u] = merge(rt[u], rt[v], 1, big);
	}
	if(d[ rt[u] ]) ans[u] = t[ rt[u] ];
}

int main() {
	int x,y,z;
	n = read(); m = read();
	for(int i=1;i<n;i++) {
		x = read(); y = read();
		e[x].push_back(y);
		e[y].push_back(x);
	}
	DFS(1,0);
	for(int k=1;k<=20;k++)
		for(int i=1;i<=n;i++)
			f[i][k] = f[ f[i][k-1] ][k-1];
	while(m--) {
		x = read(); y = read(); z = read();
		int lca = LCA(x,y);
		insert(rt[x], 1, big, z, 1);
		insert(rt[y], 1, big, z, 1);
		insert(rt[lca], 1, big, z, -1);
		if(f[lca][0]) insert(rt[f[lca][0]], 1, big, z, -1);
	}
	hebing(1);
	for(int i=1;i<=n;i++) cout<<ans[i]<<"\n";
	return 0;
}