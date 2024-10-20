#include <bits/stdc++.h>
#define ll long long
#define db double
#define ls now<<1
#define rs now<<1|1
using namespace std;
const int p1=39989;
const int p2=1000000000;
const double eps = 1e-9;

const int N=101010;
const int RR=40404;

int T,ans,cnt;
struct E{
	db K,B; int id;
}d[N],t[RR<<2];

inline void add(int x0,int y0,int x1,int y1) {
	++cnt;
	if(x0==x1) d[cnt] = {0,(db)max(y0,y1),cnt};
	else d[cnt].K = (db)(y1-y0)/(x1-x0), d[cnt].B = y0-d[cnt].K*x0, d[cnt].id = cnt;
}

inline db w(E L,int x) { return L.K * x + L.B; }
bool cmp(E L1,E L2,int x) { if(fabs(w(L1,x)-w(L2,x))<eps) return L1.id<L2.id; return w(L1,x)>w(L2,x); } // L1 > L2

void insert(int now,int l,int r,E g) {
	if( cmp(g,t[now],l) &&  cmp(g,t[now],r)) { t[now] = g; return; }
	if(!cmp(g,t[now],l) && !cmp(g,t[now],r)) return ;
	int mid = l+r >> 1;
	if(t[now].K < g.K) {
		if(cmp(g,t[now],mid)) insert(ls, l, mid, t[now]), t[now] = g;
		else                  insert(rs, mid+1, r, g);
	}
	else {
		if(cmp(g,t[now],mid)) insert(rs, mid+1, r, t[now]), t[now] = g;
		else                  insert(ls, l, mid, g);
	}
}

void update(int now,int l,int r,int x,int y,E g) {
	if(x<=l && r<=y) { insert(now, l, r, g); return ; }
	int mid = l+r >> 1;
	if(x<=mid) update(ls, l, mid, x, y, g);
	if(mid<y)  update(rs, mid+1, r, x, y, g);
}

E query(int now,int l,int r,int x) {
	if(l==r) return t[now];
	int mid = l+r >> 1;
	E res = t[now];
	if(x<=mid) { E la = query(ls, l, mid, x); if(cmp(la,res,x)) res=la; }
	else       { E ra = query(rs, mid+1, r, x); if(cmp(ra,res,x)) res=ra; }
	return res;
}

int main() {
	T = read();
	while(T--) {
		int cz;
		cz = read();
		if(cz==1) {
			int x0, y0, x1, y1;
			x0 = read(); y0 = read(); x1 = read(); y1 = read();
			if(x0>x1) swap(x0,x1), swap(y0,y1);
			add(x0,y0,x1,y1);
			update(1, 1, RR, x0, x1, d[cnt]);
		}
		else {
			int x = read();
			cout<<w(query(1, 1, RR, x),x)<<endl;
		}
	}
	return 0;
}