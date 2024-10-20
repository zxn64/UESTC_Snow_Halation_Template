#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int N=501010;
const int inf=0x3f3f3f3f;

int n,m;
int fa[N],dep[N];
vector <int> e[N];

int find(int x) { return fa[x]==x ? x : fa[x]=find(fa[x]); }


void merge(int x,int y) {
    if(x==y) return ;
    if(dep[x]<dep[y]) swap(x,y);
    fa[x] = y;
}

void tarjan(int u) {
    for(int v : e[u]) {
        if(!dep[v]) {
            dep[v] = dep[u] + 1;
            tarjan(v);
        }
        int vv = find(v), uu = find(u);
        if(dep[vv] > 0) merge(uu,vv);
    }
    dep[u] = -1;
}

int main() {
    int x,y;
    n = read(); m = read();
    for(int i=1;i<=n;i++) fa[i] = i;
    for(int i=1;i<=m;i++) {
        x = read(); y = read();
        e[x].push_back(y);
    }
    for(int i=1;i<=n;i++) {
        if(!dep[i]) tarjan(i);
    }

    for(int i=1;i<=n;i++) cout<<"belong["<<i<<"] = "<<find(i)<<"\n";
    return 0;
}
