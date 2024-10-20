#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=101010;
const int inf=0x3f3f3f3f;

int n,m;
int a[N],fa[N],son[N][2];
int dep[N];

int merge(int x,int y) {
	if(x==0 || y==0) return x|y;
	if(a[x]>a[y] || (a[x]==a[y] && x>y) ) swap(x,y);
	son[x][1] = merge(son[x][1],y);
	if(dep[ son[x][0] ] < dep[ son[x][1] ]) swap(son[x][0],son[x][1]);
	dep[x] = dep[ son[x][1] ] + 1;
	return x;
}

int find(int x) { return fa[x]==x ? x : fa[x]=find(fa[x]); }

void pop(int x) {
	a[x] = -1;
	fa[x] = merge(son[x][0],son[x][1]);
	fa[ fa[x] ] = fa[x];
}

int main() {
	int cz,x,y;
	n = read(); m = read();
	dep[0] = -1;
	for(int i=1;i<=n;i++) a[i] = read(), fa[i] = i;
	for(int i=1;i<=m;i++) {
		cz = read();
		if(cz==1) {
			x = read(); y = read();
			if(a[x]==-1 || a[y]==-1) continue;
			int xx = find(x), yy = find(y);
			if(xx==yy) continue;
			fa[xx] = fa[yy] = merge(xx,yy);    // merge x tree and y tree
		}
		else {
			x = read();
			if(a[x]==-1) printf("-1\n");   // x has been deleted
			else {
				int rt = find(x);      
				printf("%d\n",a[rt]);    // rt : the min val in x tree
				pop(rt);
			}
		}
	}

	return 0;
}