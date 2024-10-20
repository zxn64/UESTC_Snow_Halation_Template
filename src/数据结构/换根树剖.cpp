#define ls now<<1
#define rs now<<1|1

using namespace std;
const int N=101010;
const int qwq=N<<2;
const int inf=0x3f3f3f3f;


int T;
int n,m,root = 1;
int a[N];
vector <int> e[N];
int son[N],fa[N],dep[N],siz[N];
int tp[N],id[N],w[N],cnt;
ll t[qwq],tag[qwq];

void DFS(int u,int f) {
    dep[u] = dep[f] + 1; siz[u] = 1; fa[u] = f;
    FOR() {
        int v = e[u][i];
        if(v==f) continue;
        DFS(v,u);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}

void DFS2(int u,int zuzu) {
    tp[u] = zuzu; id[u] = ++cnt; w[cnt] = a[u];
    if(son[u]) DFS2(son[u],zuzu);
    FOR() {
        int v = e[u][i];
        if(v==fa[u] || v==son[u]) continue;
        DFS2(v,v);
    }
}

inline void pushdown(int now,int l,int r) {
    if(!tag[now]) return ;
    int mid = l+r >> 1;
    tag[ls] += tag[now]; tag[rs] += tag[now];
    t[ls] += tag[now] * (ll)(mid-l+1); t[rs] += tag[now] * (ll)(r-mid);
    tag[now] = 0;
}

void built(int now,int l,int r) {
    if(l==r) { t[now] = w[l]; return ; }
    int mid = l+r >> 1;
    built(ls, l, mid);
    built(rs, mid+1, r);
    t[now] = t[ls] + t[rs];
}

inline void insert(int now,int l,int r,int x,int y,ll g) {
    if(x<=l && r<=y) { t[now] += (r-l+1) * g; tag[now] += g; return ; }
    int mid = l+r >> 1;
    pushdown(now, l, r);
    if(x<=mid) insert(ls, l, mid, x, y, g);
    if(y>mid)  insert(rs, mid+1, r, x, y, g);
    t[now] = t[ls] + t[rs];
}

inline ll query(int now,int l,int r,int x,int y) {
    if(x<=l && r<=y) return t[now];
    ll res = 0, mid = l+r >> 1;
    pushdown(now, l, r);
    if(x<=mid) res += query(ls, l, mid, x, y);
    if(y>mid)  res += query(rs, mid+1, r, x, y);
    return res;
}

inline int lca(int x,int y) {
    while(tp[x] != tp[y]) {
        if(dep[tp[x]] < dep[tp[y]]) swap(x,y);
        x = fa[tp[x]];
    }
    if(dep[x] > dep[y]) swap(x,y);
    return x;
}

inline int LCA(int x,int y) {
    if(dep[x]>dep[y]) swap(x,y);
    int rx = lca(x,root), ry = lca(y,root), xy = lca(x,y);
    if(xy==x) {
        if(rx==x) {
            if(ry==y) return y;
            return ry;
        }
        return x;
    }
    if(rx==x) return x;
    if(ry==y) return y;
    if((rx==root&&xy==ry) || (ry==root&&xy==rx)) return root;
    if(rx==ry) return xy;
    if(xy!=rx) return rx; return ry;
}

inline int find(int x,int y) {  // find the son of x
    while(tp[x] != tp[y]) {
        if(dep[tp[x]] < dep[tp[y]]) swap(x,y);
        if(fa[tp[x]]==y) return tp[x];
        x = fa[tp[x]];
    }
    if(dep[x] > dep[y]) swap(x,y);
    return son[x];
}

inline void add(int x,ll g) {
    if(x==root) { t[1] += n * g; tag[1] += g; return ; }
    if(id[root]>id[x] && id[root]<=id[x]+siz[x]-1) { // root in x
        int y = find(x, root);
        t[1] += n * g; tag[1] += g;
        insert(1, 1, n, id[y], id[y]+siz[y]-1, -g);
    }
    else insert(1, 1, n, id[x], id[x]+siz[x]-1, g);
}

inline ll ask(int x) {
    if(x==root) return t[1];
    if(id[root]>id[x] && id[root]<=id[x]+siz[x]-1) {
        int y = find(x, root);
        return t[1] - query(1, 1, n, id[y], id[y]+siz[y]-1);
    }
    return query(1, 1, n, id[x], id[x]+siz[x]-1);
}

int main() {
    int cz,x,y,z;
	n = read(); m = read();
    for(int i=1;i<=n;i++) a[i] = read();
    for(int i=1;i<n;i++) {
        x = read(); y = read();
        e[x].push_back(y);
        e[y].push_back(x);
    }
    DFS(1,0);
    DFS2(1,1);
    built(1,1,n);
    while(m--) {
        cz = read();
        if(cz==1) root = read();
        if(cz==2) {
            x = read(); y = read(); z = read();
            add(LCA(x,y), z);
        }
        if(cz==3) {
            x = read();
            printf("%lld\n",ask(x));
        }
    }
    return 0;
}
