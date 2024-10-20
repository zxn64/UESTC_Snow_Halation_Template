#include <bits/stdc++.h>
#define QWQ cout<<"QwQ"<<endl;
#define ll long long
#define ls son[x][0]
#define rs son[x][1]
using namespace std;
const int N=501010;
const int inf=0x3f3f3f3f;

int m,rt,tot;
int fa[N],son[N][2],siz[N],num[N],val[N];

/*
inline void access(ll x) {
    cnt = 0;
    st[++cnt] = x;
    while(fa[x]) st[++cnt] = (x=fa[x]);
    while(cnt) pushdown(st[cnt--]);
}
*/

inline int touhou(int x) { return son[fa[x]][1]==x; }
inline void pushup(int x) { siz[x] = siz[ls] + siz[rs] + num[x]; }
inline void rotate(int x) {
	int y = fa[x], z = fa[y], k = touhou(x), w = son[x][k^1];
	son[z][touhou(y)] = x; son[x][k^1] = y; son[y][k] = w;
	fa[w] = y; fa[y] = x; fa[x] = z; pushup(y); pushup(x);
}
inline void splay(int x,int goal) {
	// access(x);s
	while(fa[x]!=goal) {
		int y = fa[x], z = fa[y];
		if(z!=goal) {
			if(touhou(y)==touhou(x)) rotate(y);
			else rotate(x);
		}
		rotate(x);
	}
	if(!goal) rt = x;
}

inline void insert(int v) {
	int x = rt, f = 0;
	while(val[x]!=v && x)
		f = x, x = son[x][val[x]<v];
	if(x) num[x]++, pushup(x);
	else {
		x = ++tot;
		if(f) son[f][val[f]<v] = x;
		fa[x] = f; siz[x] = num[x] = 1;
		val[x] = v;
	}
	splay(x,0);
}

inline int rnk(int k) {
	int x = rt;
	while(1) {
		if(siz[ls]>=k) x = ls;
		else if(siz[ls]+num[x]<k) k -= siz[ls]+num[x], x = rs;
		else return x;
	}
}

inline void find(int v) {
	int x = rt;
	while(val[x]!=v && son[x][ val[x]<v ])
		x = son[x][ val[x]<v ];
	splay(x,0);	
}
inline int qian(int v) {
	find(v);
	if(val[rt]<v) return rt;
	int x = son[rt][0];
	while(rs) x = rs; return x;
}
inline int hou(int v) {
	find(v);
	if(val[rt]>v) return rt;
	int x = son[rt][1];
	while(ls) x = ls; return x;
}

void del(int v) {
	int y = qian(v), x = hou(v);
	splay(y,0); splay(x,y);
	if(num[ls]>1) num[ls]--, siz[ls]--;
	else ls = 0;
	pushup(x); pushup(y);
}

inline void outing() {
    for(int i=0;i<=tot;i++) {
        cout<<i<<" : v = "<<val[i]<<" fa = "<<fa[i]<<" ls = "<<son[i][0]
        <<" rs = "<<son[i][1]<<" num = "<<num[i]<<" siz = "<<siz[i]<<endl;
    }
}

int main() {
	int cz,x;
	insert(inf);
	insert(-inf);
	m = read();
	while(m--) {
		cz = read(); x = read();
		if(cz==1) { insert(x); }
		if(cz==2) { del(x); }
		if(cz==3) { find(x); cout<<siz[son[rt][0]]+(val[rt]<x?num[rt]:0)<<"\n"; }
		if(cz==4) { cout<<val[rnk(x+1)]<<"\n"; }
		if(cz==5) { cout<<val[qian(x)]<<"\n"; }
		if(cz==6) { cout<<val[hou(x)]<<"\n"; }
	}

	return 0;
}