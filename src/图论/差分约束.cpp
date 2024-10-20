#include <bits/stdc++.h>
#define FOR() int le=e[u].size();for(int i=0;i<le;i++)
using namespace std;
const int N=101010;
const int inf=0x3f3f3f3f;

int n,m;
int dis[N],dep[N],in[N];
struct E{ int to,we; };
vector <E> e[N];
queue <int> q;

bool SPFA() {
	memset(dis,0x3f,sizeof(dis));   // min dis : the max solution
	// memset(dis,-0x3f,sizeof(dis));  // max dis : the min solution
	dis[0] = 0;
	q.push(0);
	while(!q.empty()) {
		int u = q.front(); q.pop(); in[u] = 0;
		FOR() {
			int v = e[u][i].to, w = e[u][i].we;
			if(dis[v] > dis[u] + w) {    // max solution
			// if(dis[v] < dis[u] + w) {    // min solution
				dis[v] = dis[u] + w;
				dep[v] = dep[u] + 1;
				if(dep[v]>n) return 0;
				if(!in[v]) q.push(v);
				in[v] = 1;
			}
		}
	}
	return 1;
}

int main() {
	int x,y,z;
	n = read(); m = read();
	while(m--) {
		x = read(); y = read(); z = read();  // x-y <= z
		e[y].push_back( (E){x,z} );  // x <= y+z    the max solution
     // e[x].push_back( (E){y,-z} ); // y >= x-z    the min solution
	}
	for(int i=1;i<=n;i++) e[0].push_back( (E){i,0} );
	if(!SPFA()) { cout<<"NO"; return 0; }
	for(int i=1;i<=n;i++) cout<<dis[i]<<" ";
	return 0;
}