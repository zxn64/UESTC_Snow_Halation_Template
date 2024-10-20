#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int N=1010;

int n1,n2,m;
vector <int> e[N];
int vis[N],belong[N];  // index is the right_part of G(V,E)
bool tagx[N],tagy[N];

int DFS(int u) {
	for(int v : e[u]) {
		if(vis[v]) continue;
		vis[v] = 1;
		if(!belong[v] || DFS(belong[v])) { belong[v] = u; return 1; }
	}
	return 0;
}

void mark(int u) {
	if(tagx[u]) return ;
	tagx[u] = 1;
	for(int v : e[u]) {
		if(!tagy[v] && belong[v]) {
			tagy[v] = 1;
			mark(belong[v]);
		}
	}
}

int main() {
	int x,y;
	n1 = read(); n2 = read(); m = read();
	while(m--) {
		x = read(); y = read();
		e[x].push_back(y);
	}
	int ans = 0;
	for(int i=1;i<=n1;i++) {
		memset(vis, 0, sizeof(vis));
		ans += DFS(i);
	}
	cout<<"ans = "<<ans<<endl;
	memset(vis, 0, sizeof(vis));
	for(int i=1;i<=n2;i++) vis[ belong[i] ] = 1;
	for(int i=1;i<=n1;i++) if(!vis[i]) mark(i);
	for(int i=1;i<=n1;i++) if(!tagx[i]) cout<<i<<" ";
	cout<<endl;
	for(int i=1;i<=n2;i++) if(tagy[i]) cout<<i<<" ";
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
