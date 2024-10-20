int n,m,ans;
int fa[N],cl[N],mp[N],pre[N];
int cnt,tim[N];
vector <int> e[N];
queue <int> q;


int find(int x) { return (fa[x]==x) ? x : fa[x]=find(fa[x]); }

inline void link(int x,int y) { mp[x] = y; mp[y] = x; }

void rev(int x) { if(x) { rev(mp[pre[x]]), link(x,pre[x]); } }

inline int lca(int x,int y) {
    ++cnt;
    x = find(x); y = find(y);
    while(tim[x]!=cnt) {
        tim[x] = cnt;
        x = find(pre[ mp[x] ]);
        if(y) swap(x,y);
    }
    return x;
}

inline void blossom(int x,int y,int ff) {
    for(; find(x)!=ff; x=pre[y]) {
        pre[x] = y;
        y = mp[x];
        fa[x] = fa[y] = ff;
        if(cl[y]==2) cl[y] = 1, q.push(y);
    }
}

int BFS(int s) {
    for(int i=1;i<=n;i++) pre[i] = cl[i] = 0, fa[i] = i;
    while(!q.empty()) q.pop();
    cl[s] = 1; q.push(s);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        FOR() {
            int v = e[u][i];
            if(cl[v]==1) {
                int ff = lca(u,v);
                blossom(u,v,ff);
                blossom(v,u,ff);
            }
            else if(!cl[v]) {
                pre[v] = u; cl[v] = 2;
                if(!mp[v]) { rev(v); return 1; }
                else { cl[ mp[v] ] = 1; q.push(mp[v]); }
            }
        }
    }
    return 0;
}

int main() {
    int x,y;
    n = read(); m = read();
    for(int i=1;i<=n;i++) fa[i] = i;
    for(int i=1;i<=m;i++) {
        x = read(); y = read();
        e[x].push_back(y);
        e[y].push_back(x);
    }
    for(int i=1;i<=n;i++) {
        if(!mp[i]) ans += BFS(i);
    }
    cout<<ans<<"\n";
    return 0;
}
