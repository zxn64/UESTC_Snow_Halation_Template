#define ls L[now]
#define rs R[now]

using namespace std;
const ll N=501010;
const ll qwq=N*35;
const ll inf=0x3f3f3f3f;

ll n,K;
ll ans;
ll a[N];
ll cnt[N];
ll rt[N],tot;
ll val[qwq];
ll L[qwq],R[qwq],siz[qwq];
struct E{
    ll zhi,id;
};
inline bool operator < (E A,E B) { return A.zhi < B.zhi; }
priority_queue <E> q;


void insert(ll &now,ll pre,ll h,ll v) {
    now = ++tot; siz[now] = siz[pre] + 1;
    ls = L[pre]; rs = R[pre];
    if(h==-1) { val[now] = v; return ; }
    if((v>>h)&1) insert(rs, R[pre], h-1, v);
    else         insert(ls, L[pre], h-1, v);
}

ll query(ll now,ll k,ll h,ll v) {
    if(h==-1) { return v ^ val[now]; }
    if((v>>h)&1) {
        if(siz[ls] >= k) return query(ls, k, h-1, v);
        else             return query(rs, k-siz[ls], h-1, v);
    }
    else {
        if(siz[rs] >= k) return query(rs, k, h-1, v);
        else             return query(ls, k-siz[rs], h-1, v);
    }
}

int main() {
    ll x;
    n = read(); K = read();
    for(ll i=1;i<=n;i++) {
        x = read(); a[i] = a[i-1] ^ x;
        insert(rt[i], rt[i-1], 31, a[i-1]);
        q.push( E{query(rt[i], ++cnt[i], 31, a[i]), i} );
    }
    ll ci = 0;
    while(!q.empty()) {
        E now = q.top(); q.pop();
        ans += now.zhi;
        ci++;
        if(ci==K) break;
        ll u = now.id;
        if(cnt[u] < u)
        q.push( E{query(rt[u], ++cnt[u], 31, a[u]), u} );
    }
    cout<<ans;
    return 0;
}
