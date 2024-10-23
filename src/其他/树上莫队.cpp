ll f[N][24];
ll dep[N],siz[N];
ll st[N],ed[N],ob[N],cnt;

struct Q{
    ll id,l,r,lca;
} q[N];

inline bool cmp(Q A,Q B) {
    if(A.l/K != B.l/K) return A.l < B.l;
    if((A.l/K)&1) return A.r < B.r;
    else          return A.r > B.r;
}

void DFS(ll u) {
    dep[u] = dep[f[u][0]] + 1; siz[u] = 1;
    st[u] = ++cnt; ob[cnt] = u;
    for(ll v : e[u]) {
        DFS(v);
        siz[u] += siz[v];
    }
    ed[u] = ++cnt; ob[cnt] = u;
}

inline void add(ll u) {
    // cout<<"add("<<u<<")\n";
    ll c = num[u];
    num[u] ^= 1;
    if(c) (res -= dp[u]-p) %= p;
    else  (res += dp[u]) %= p;
}

int main() {
    n = read(); m = read();
    for(ll i=1;i<=m;i++) {
        x = read(); y = read();
        if(st[x]>st[y]) swap(x,y);
        ll lca = LCA(x,y);
        if(lca==x) q[i] = {i,st[x],st[y],0};
        else       q[i] = {i,ed[x],st[y],lca};
    }
    sort(q+1,q+m+1,cmp);

    ll L = q[1].l, R = q[1].l;
    res = dp[ ob[L] ];
    num[ ob[L] ] = 1;
    for(ll i=1;i<=m;i++) {
        // cout<<q[i].l<<" "<<q[i].r<<"  i = "<<i<<"\n";

        while(L>q[i].l) add(ob[--L]);
        while(R<q[i].r) add(ob[++R]);
        while(L<q[i].l) add(ob[L++]);
        while(R>q[i].r) add(ob[R--]);
        // cout<<"res = "<<res<<"\n";
        if(q[i].lca) add(q[i].lca);
        ans[ q[i].id ] = res;
        if(q[i].lca) add(q[i].lca);
    }
    return 0;
}