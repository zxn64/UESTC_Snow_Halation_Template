// solution 1
ll base = 13333;
bool cmp(ll A,ll B) { return ha[A] < ha[B]; }

void TREE(ll u) {
    for(ll i=0;i<e[u].size();i++) TREE(e[u][i],cl);
    sort(e[u].begin(),e[u].end(),cmp);
    ha[u] = a[u];
    ll now = 114514;
    for(ll v : e[u]) {
        (ha1[u] += now * ha1[u] %p) %= p;
        (now *= base) %= p;
    }
}


// solution 2
void dfs3(int u){
    dp1[u]=827,dp2[u]=827;
    for(int i=0;i<g2[u].size();i++){
        int v=g2[u][i];
        dfs3(v);
        dp1[u]+=(ull)(siz[v]+dp1[v]-(siz[v]^dp1[v])+siz[u]);
        dp2[u]+=(ull)(siz[v]+dp2[v]+(siz[v]^dp2[v])+siz[u]);
    }
    dp1[u]*=829;
    dp2[u]*=829;
}