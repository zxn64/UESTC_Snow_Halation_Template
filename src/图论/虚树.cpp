const int N=501010;
const int qwq=303030;
const int inf=0x3f3f3f3f;


int T;
int n,a[N],da;
vector <int> e[N];
vector <int> g[N];
int dfn[N],tot,dep[N];
int f[N][22],rec[N][22];
int ob[N];
int cnt,st[N];
vector <int> d[N];

inline bool cmp(int x,int y) { return dfn[x] < dfn[y]; }

void DFS(int u,int fa) {
    dep[u] = dep[fa] + 1;
    f[++tot][0] = dep[u]; rec[tot][0] = u;
    dfn[u] = tot;
    FOR() {
        int v = e[u][i];
        if(v==fa) continue;
        DFS(v,u);
        f[++tot][0] = dep[u]; rec[tot][0] = u;
    }
}

inline int LCA(int x,int y) {
    if(dfn[x]>dfn[y]) swap(x,y);
    int l = dfn[x], r = dfn[y], k = ob[r-l+1];
    if(f[l][k] < f[r-(1<<k)+1][k]) return rec[l][k];
    else return rec[r-(1<<k)+1][k];
}

void built(int h) {
    cout<<"\nh = "<<h<<endl;
    cnt = 0;
    st[++cnt] = 1;
    for(int v : g[h]) st[++cnt] = v;
    sort(st+1, st+cnt+1, cmp);
    int now = cnt;
    for(int i=2;i<=now;i++) st[++cnt] = LCA(st[i-1],st[i]);
    sort(st+1, st+cnt+1, cmp);
    cnt = unique(st+1, st+cnt+1) - st - 1;
    for(int i=2;i<=cnt;i++) {
        d[ LCA(st[i-1],st[i]) ].push_back( st[i] );
        cout<<LCA(st[i-1],st[i])<<" -> "<<st[i]<<endl;
    }
    // TREE(1);
    for(int i=1;i<=cnt;i++) d[st[i]].clear();
}

int main() {
    int x,y;
    ob[0] = -1; for(int i=1;i<=N-10;i++) ob[i] = ob[i>>1] + 1;
    n = read(); da = read();
    for(int i=1;i<=n;i++) a[i] = read(), g[a[i]].push_back(i);
    for(int i=1;i<n;i++) {
        x = read(); y = read();
        e[x].push_back(y);
        e[y].push_back(x);
    }
    DFS(1,1);
    for(int k=1;k<=20;k++) {
        for(int i=1;i+(1<<k-1)<=tot;i++) {
            if(f[i][k-1] < f[i+(1<<k-1)][k-1])
                f[i][k] = f[i][k-1], rec[i][k] = rec[i][k-1];
            else
                f[i][k] = f[i+(1<<k-1)][k-1], rec[i][k] = rec[i+(1<<k-1)][k-1];
        }
    }
    for(int i=1;i<=da;i++) {
        built(i);
    }
    return 0;
}

/*

11 4
1 4 2 1 3  4 1 1 4 2  1
1 2
1 3
2 4
4 5
4 6
3 7
7 8
7 9
1 10
2 11

*/
