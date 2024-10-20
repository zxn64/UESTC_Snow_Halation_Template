const int N=1101010;
const int qwq=303030;
const int inf=0x3f3f3f3f;

int T;
int n,m;
int ans,a[N];
vector <int> e[N];
int dfn[N],tot;
int dep[N];
int f[N][26],rec[N][26];
int ob[N];

void DFS(int u,int fa) {
    dep[u] = dep[fa] + 1;
    f[++tot][0] = dep[u];
    rec[tot][0] = u;
    dfn[u] = tot;
    FOR() {
        int v = e[u][i];
        if(v==fa) continue;
        DFS(v,u);
        f[++tot][0] = dep[u];
        rec[tot][0] = u;
    }
}

inline int LCA(int x,int y) {
    if(dfn[x]>dfn[y]) swap(x,y);
    int l = dfn[x], r = dfn[y], k = ob[r-l+1];
    if(f[l][k] < f[r-(1<<k)+1][k]) return rec[l][k];
    else return rec[r-(1<<k)+1][k];
}

int main() {
    ob[0] = -1; for(int i=1;i<=N-10;i++) ob[i] = ob[i>>1] + 1;
	int x,y,rt;
    n = read(); m = read(); rt = read();
    for(int i=1;i<n;i++) {
        x = read(); y = read();
        e[x].push_back(y);
        e[y].push_back(x);
    }
    DFS(rt,rt);
    for(int i=1;i<=tot;i++) cout<<rec[i][0]<<" ";
    for(int k=1;k<=22;k++) {
        for(int i=1;i+(1<<k-1)<=tot;i++) {
            if(f[i][k-1] < f[i+(1<<k-1)][k-1])
                f[i][k] = f[i][k-1], rec[i][k] = rec[i][k-1];
            else
                f[i][k] = f[i+(1<<k-1)][k-1], rec[i][k] = rec[i+(1<<k-1)][k-1];
        }
    }
    while(m--) {
        x = read(); y = read();
        cout<<LCA(x,y)<<"\n";
    }
    return 0;
}
