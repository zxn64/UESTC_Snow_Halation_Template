const ll N=501010;
const ll qwq=303030;
const ll inf=0x3f3f3f3f;
const ll p=998244353, g=3, gi=332748118;

inline ll read() {
    ll sum = 0, ff = 1; char c = getchar();
    while(c<'0' || c>'9') { if(c=='-') ff = -1; c = getchar(); }
    while(c>='0'&&c<='9') { sum = (sum * 10 + c - '0') %p; c = getchar(); }
    return sum * ff;
}

ll n,m,K;
ll r[N];
ll a[N],b[N];
ll c1[N];

inline ll ksm(ll aa,ll bb) {
    ll sum = 1;
    while(bb) {
        if(bb&1) sum = sum * aa %p;
        bb >>= 1; aa = aa * aa %p;
    }
    return sum;
}

void NTT(ll *A,ll len,ll cl) {
    for(ll i=0;i<len;i++) if(i<r[i]) swap(A[i],A[r[i]]);
    for(ll k=1;k<len;k<<=1) {
        ll g1 = ksm((cl==1)?g:gi, (p-1)/(k<<1));
        for(ll j=0;j<len;j+=(k<<1)) {
            ll gk = 1;
            for(ll i=0;i<k;i++,(gk*=g1)%=p) {
                ll x = A[i+j], y = gk*A[i+j+k]%p;
                A[i+j] = (x+y)%p; A[i+j+k] = (x-y+p)%p;
            }
        }
    }
    if(cl==1) return ;
    ll inv = ksm(len,p-2);
    for(ll i=0;i<len;i++) A[i] = A[i] * inv %p;
}

void Pksm(ll *F,ll *G,ll K,ll n) {    //  G = F^K  (mod x^n)
    ll len = 1, L = 0; while(len-1<n+n+2) len<<=1, L++;
    for(ll i=0;i<len;i++) r[i] = (r[i>>1]>>1) | ((i&1)<<(L-1));
    G[0] = 1;
    while(K) {
        NTT(F, len, 1);
        if(K&1) {
            NTT(G, len, 1);
            for(int i=0;i<len;i++) G[i] = G[i] * F[i] %p;
            NTT(G, len, -1);
            for(int i=n;i<len;i++) G[i] = 0;
        }
        K >>= 1;
        for(int i=0;i<len;i++) F[i] = F[i] * F[i] %p;
        NTT(F, len, -1);
        for(int i=n;i<len;i++) F[i] = 0;
    }
}

int main() {
    n = read(); K = read();
    for(ll i=0;i<n;i++) a[i] = read();
    Pksm(a, b, K, n);
    for(ll i=0;i<n;i++) cout<<b[i]<<" ";
    return 0;
}

/*

9 18948465
1 2 3 4 5 6 7 8 9

1 37896930 597086012 720637306 161940419 360472177 560327751 446560856 524295016

*/