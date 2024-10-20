#include <bits/stdc++.h>
#define ll long long
#define QWQ cout<<"QwQ"<<endl;
#define FOR() int le=e[u].size();for(int i=0;i<le;i++)
#define ls son[x][0]
#define rs son[x][1]

using namespace std;
const int N=501010;
const int inf=0x3f3f3f3f;

int n,m,tot;
int fa[N],son[N][2],val[N],sum[N],rev[N];
int st[N],cnt;

inline void pushup(int x) { sum[x] = sum[ls] ^ sum[rs] ^ val[x]; }
inline void rever(int x) { rev[x] ^= 1; swap(ls,rs); }
inline void pushdown(int x) { if(rev[x]) { rev[x] = 0; if(ls) rever(ls); if(rs) rever(rs); } }
inline bool touhou(int x) { return son[fa[x]][1]==x; }
inline bool flandre(int x) { return son[fa[x]][0]==x || son[fa[x]][1]==x; }
inline void rotate(int x) {
	int y = fa[x], z = fa[y], k = touhou(x), w = son[x][k^1];
	if(flandre(y)) son[z][touhou(y)] = x; son[x][k^1] = y; son[y][k] = w;
	if(w) fa[w] = y; fa[y] = x; fa[x] = z; pushup(y); pushup(x);
}
inline void splay(int x) {
	int y = x; st[++cnt] = y;
	while(flandre(y)) st[++cnt] = (y=fa[y]);
	while(cnt) pushdown(st[cnt--]);
	while(flandre(x)) {
		y = fa[x];
		if(flandre(y)) {
			if(touhou(y)==touhou(x)) rotate(y);
			else rotate(x);
		}
		rotate(x);
	}
}

inline void access(int x) { for(int y=0;x;x=fa[y=x]) splay(x), son[x][1] = y, pushup(x); }
inline void makert(int x) { access(x); splay(x); rever(x); }
inline void split(int x,int y) { makert(x); access(y); splay(y); }

int find(int x) { access(x); splay(x); while(ls) pushdown(ls), x = ls; splay(x); return x; }
inline void link(int x,int y) { makert(x); if(find(y)!=x) fa[x] = y; }
inline void cut(int x,int y) { makert(x); if(find(y)==x && fa[y]==x && !son[y][0]) fa[y] = son[x][1] = 0, pushup(x); }

inline bool judge(int x,int y) { while(fa[x]) x = fa[x]; while(fa[y]) y = fa[y]; return x==y; } // 是否连通

int main() {
	int cz,x,y;
	n = read(); m = read();
	for(int i=1;i<=n;i++) val[i] = read();
	while(m--) {
		cz = read(); x = read(); y = read();
		if(cz==0) { split(x,y); cout<<sum[y]<<"\n"; }
		if(cz==1) { link(x,y); }
		if(cz==2) { cut(x,y); }
		if(cz==3) { splay(x); sum[x] ^= y ^ val[x]; val[x] = y; }
	}
	return 0;
}