#define ls now<<1
#define rs now<<1|1

using namespace std;
const int N=501010;
const int qwq=303030;
const int inf=0x3f3f3f3f;


int T;
int n,m;
int da;
int L[N],R[N];
vector < pair<int,int> > t[N<<2];
struct CZ{
    int x,y,depy,tim;
}st[N];
int fa[N],tag[N],dep[N];
int cnt;

int find(int x) { return x==fa[x] ? x : find(fa[x]); }

void insert(int now,int l,int r,int x,int y,pair<int,int>pa) {
    if(x<=l && r<=y) { t[now].push_back(pa); return ; }
    int mid = l+r >> 1;
    if(x<=mid) insert(ls, l, mid, x, y, pa);
    if(y>mid)  insert(rs, mid+1, r, x, y, pa);
}

void merge(int x,int y,int tim) {
    int xx = find(x), yy = find(y);
    if(xx==yy) return ;
    if(dep[xx] > dep[yy]) swap(xx,yy);   //  xx -> yy
    st[++cnt] = {xx, yy, dep[yy], tim};
    fa[xx] = yy;
    if(dep[xx]==dep[yy]) dep[yy]++;
    tag[xx] -= tag[yy];
}

void DFS(int now,int l,int r) {
    for(auto v : t[now]) {
        merge(v.first, v.second, now);
    }
    if(l==r) tag[find(1)]++;
    else {
        int mid = l+r >> 1;
        DFS(ls, l, mid);
        DFS(rs, mid+1, r);
    }
    while(st[cnt].tim==now) {
        CZ cz = st[cnt--];
        tag[cz.x] += tag[cz.y];
        fa[cz.x] = cz.x;
        dep[cz.y] = cz.depy;
    }
}

int main() {
    int x,y;
    n = read(); m = read();
    for(int i=1;i<=n;i++) L[i] = read(), R[i] = read(), da = max(da,R[i]);
    for(int i=1;i<=m;i++) {
        x = read(); y = read();
        int le = max(L[x], L[y]);
        int re = min(R[x], R[y]);
        if(le<=re) insert(1, 1, da, le, re, pair<int,int>{x,y});
    }
    for(int i=1;i<=n;i++) fa[i] = i;
    DFS(1, 1, da);
    for(int i=1;i<=n;i++) if(tag[i]) cout<<i<<" ";
    return 0;
}