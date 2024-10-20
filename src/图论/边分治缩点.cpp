#define ls now<<1
#define rs now<<1|1

using namespace std;
const ll N=501010;
const ll qwq=303030;
const ll inf=0x3f3f3f3f;

ll T;
ll n,m;
int ans[N], _ans;
int fa[N];
struct E{
    int x,y,ti;
};
vector <E> d[N<<2];
vector <int> e[N];
int tim,dfn[N],low[N],belong[N];
int in[N],st[N],cnt;

int find(int x) { return fa[x]==x ? x : fa[x]=find(fa[x]); }

inline void merge(int x,int y) {
    x = find(x); y = find(y);
    if(x==y) return ;
    fa[x] = y;
    _ans--;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    st[++cnt] = u; in[u] = 1;
    for(int v : e[u]) {
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u],low[v]);
        }
        else if(in[v]) low[u] = min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u]) {
        while(1) {
            int v = st[cnt--]; in[v] = 0;
            belong[v] = u;
            if(v==u) break;
        }
    }
}

void solve(ll now,ll l,ll r) {
    // cout<<"solve("<<l<<","<<r<<") : ";
    // for(E vv : d[now]) cout<<vv.x<<"->"<<vv.y<<" ";
    // cout<<endl;
    if(l==r) {
        for(E vv : d[now]) merge(vv.x, vv.y);
        vector<E>().swap(d[now]);
        ans[l] = _ans;
        return ;
    }
    ll mid = l+r >> 1;
    for(E &vv : d[now]) {
        e[vv.x = find(vv.x)].clear();
        e[vv.y = find(vv.y)].clear();
        dfn[vv.x] = dfn[vv.y] = 0;
    }
    for(E vv : d[now]) if(vv.ti<=mid) e[vv.x].push_back(vv.y);
    for(E vv : d[now]) {
        if(vv.ti<=mid) {
            if(!dfn[vv.x]) tarjan(vv.x);
            if(!dfn[vv.y]) tarjan(vv.y);
            if(belong[vv.x]==belong[vv.y]) d[ls].push_back(vv);
            else                           d[rs].push_back(vv);
        }
        else {
            d[rs].push_back(vv);
        }
    }
    vector<E>().swap(d[now]);
    solve(ls, l, mid);
    solve(rs, mid+1, r);
}

void chushihua() {
    _ans = 0;
    tim = 0;
}

int main() {
    int x,y;
	T = read();
	while(T--) {
        chushihua();
        n = read(); m = read();
        _ans = n;
        for(int i=1;i<=n;i++) fa[i] = i;
        for(int i=1;i<=m;i++) {
            x = read(); y = read();
            d[1].push_back({x,y,i});
        }
        solve(1, 1, m+1);
        for(int i=1;i<=m;i++) cout<<ans[i]<<"\n";
	}
    return 0;
}


