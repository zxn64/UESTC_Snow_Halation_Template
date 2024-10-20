#include <bits/stdc++.h>
#define ll long long
#define ls L[now]
#define rs R[now]
const int N=1010101;

int n,m;
int a[N],rt[N],tot;
int t[N*33], L[N*33], R[N*33];

inline void pushup(int now) { t[now] = t[ls] + t[rs]; }
void built(int &now,int l,int r) {
	now = ++tot;
	if(l==r) { t[now] = a[l]; return ; }
	int mid = l+r >> 1;
	built(ls, l, mid);
	built(rs, mid+1, r);
	pushup(now);
}

void insert(int &now,int pre,int l,int r,int we,int g) {
	now = ++tot;
	ls = L[pre]; rs = R[pre];
	if(l==r) { t[now] = g; return ; }
	int mid = l+r >> 1;
	if(we<=mid) insert(ls, L[pre], l, mid, we, g);
	else        insert(rs, R[pre], mid+1, r, we, g);
	pushup(now); return ;
}

int query(int now,int l,int r,int x,int y) {
	if(x<=l && r<=y) return t[now];
	int mid = l+r >> 1, res = 0;
	if(x<=mid) res += query(ls, l, mid, x, y);
	if(y>mid)  res += query(rs, mid+1, r, x, y);
	return res;
}

int main() {
	int x,y,z,w;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	built(rt[0],1,n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		if(y==1)
		{
			scanf("%d",&w);
			insert(rt[i], rt[x], 1, n, z, w);
		}
		else
		{
			printf("%d\n",query(rt[x], 1, n, z, z));
			rt[i] = rt[x];
		}
	}
	return 0;
}