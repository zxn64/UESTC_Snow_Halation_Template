#include <bits/stdc++.h>
#define QWQ cout<<"QwQ"<<endl;
#define ll long long
#define ls son[x][0]
#define rs son[x][1]
using namespace std;
const int N=501010;

int n,a[N];

int m,rt,tot;
int fa[N],son[N][2],siz[N],sum[N],val[N],rev[N];

inline void pushup(int x) {
	siz[x] = siz[ls] + siz[rs] + 1;
	sum[x] = sum[ls] + sum[rs] + val[x];
}
inline void pushdown(int x) {
	if(rev[x]) {
		rev[x] = 0;
		rev[ls] ^= 1; rev[rs] ^= 1;
		swap(son[ls][0],son[ls][1]);
		swap(son[rs][0],son[rs][1]);
	}
}

inline bool touhou(int x) { return son[fa[x]][1]==x; }
inline void rotate(int x) {
	int y = fa[x], z = fa[y], k = touhou(x), w = son[x][k^1];
	son[z][touhou(y)] = x; son[x][k^1] = y; son[y][k] = w;
	fa[x] = z; fa[y] = x; fa[w] = y; pushup(y); pushup(x);
}
inline void splay(int x,int goal) {
	while(fa[x]!=goal) {
		int y = fa[x], z = fa[y];
		if(z!=goal) {
			if(touhou(x)==touhou(y)) rotate(y);
			else rotate(x);
		}
		rotate(x);
	}
	if(!goal) rt = x;
}

inline int rnk(int k) {
	int x = rt;
	while(1) {
		pushdown(x);
		if(siz[ls]>=k) x = ls;
		else if(siz[ls]+1<k) k -= siz[ls]+1, x = rs;
		else return x;
	}
}

inline int Push(int v) {
	int x = ++tot;
	siz[x] = 1; val[x] = sum[x] = v; return x;
}
int built(int l,int r) {
	if(l>r) return 0;
	int mid = l+r >> 1, x = Push(a[mid]);
	if(ls=built(l,mid-1)) fa[ls] = x;
	if(rs=built(mid+1,r)) fa[rs] = x;
	pushup(x); return x;
}
inline void insert(int wei,int v) {  //insert one num after one position
	int y = rnk(wei+1), z = rnk(wei+2);
	splay(y,0); splay(z,y); int x = Push(v);
	son[z][0] = x; fa[x] = z;
	pushup(z); pushup(y);
}
inline void del(int wei) {
	int y = rnk(wei), z = rnk(wei+2);
	splay(y,0); splay(z,y); int x = son[z][0];
	fa[x] = son[z][0] = 0;
	pushup(z); pushup(y);
}

inline void zhuan(int L,int R) {
	int y = rnk(L), z = rnk(R+2);
	splay(y,0); splay(z,y); int x = son[z][0];
	rev[x] ^= 1; swap(ls,rs);
}
inline int qiu(int L,int R) {
	int y = rnk(L), z = rnk(R+2);
	splay(y,0); splay(z,y);
	return sum[son[z][0]];
}

int main() {
	built(0,n+1); rt = 1;
	return 0;
}