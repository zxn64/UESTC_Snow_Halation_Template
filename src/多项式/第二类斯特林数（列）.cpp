const ll N=801010;
const ll qwq=303030;
const ll inf=0x3f3f3f3f;
const ll p=167772161, g=3, gi=55924054;


ll n,m,K;
ll r[N];
ll a[N],b[N],c[N];
ll c1[N],c2[N],c3[N],c4[N],c5[N],c6[N],c7[N];
ll f[N],ni[N];

inline ll ksm(ll aa,ll bb) {
	ll sum = 1;
	while(bb) {
		if(bb&1) sum = sum * aa %p;
		bb >>= 1; aa = aa * aa %p;
	}
	return sum;
}

void qiu() {
	f[0] = ni[0] = 1;
	for(int i=1;i<=N-10;i++) f[i] = f[i-1] * i %p;
	ni[N-10] = ksm(f[N-10],p-2);
	for(int i=N-11;i>=1;i--) ni[i] = ni[i+1] * (i+1) %p;
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

inline int init(int wo) {
	ll len = 1, L = 0; while(len<wo) len<<=1, L++;
	for(ll i=0;i<len;i++) r[i] = (r[i>>1]>>1) | ((i&1)<<(L-1));
	return len;
}

void PMUL(ll *F,ll *G,ll n,ll m) {  // F -> 1+..+x^n   G -> 1+...+x^m
	ll len = init(n+m+1);
	NTT(F,len,1);
	NTT(G,len,1);
	for(ll i=0;i<len;i++) F[i] = F[i] * G[i] %p;
	NTT(F,len,-1);
}

void PI(ll *F,ll *G,ll n) {  // F*G = 1 (mod x^n)
	G[0] = ksm(F[0],p-2);
	ll *A=c1, *B=c2, k=1;
	for(ll len,L=1;k<(n+n);k<<=1,L++) {
		len = k<<1;
		for(ll i=0;i<k;i++) A[i] = F[i], B[i] = G[i];
		for(ll i=0;i<len;i++) r[i] = (r[i>>1]>>1) | ((i&1)<<(L-1));
		NTT(A, len, 1);
		NTT(B, len, 1);
		for(ll i=0;i<len;i++) G[i] = (2ll - A[i] * B[i] %p + p) %p * B[i] %p;
		NTT(G, len, -1);
		for(ll i=k;i<len;i++) G[i] = 0;
	}
	for(ll i=0;i<k;i++) A[i] = B[i] = 0;
	for(ll i=n;i<k;i++) G[i] = 0;
}

void Pdao(ll *F,ll *G,ll n) {
	for(ll i=1;i<n;i++) G[i-1] = i*F[i] %p; G[n-1] = 0;
}

void Pji(ll *F,ll *G,ll n) {
	for(ll i=1;i<n;i++) G[i] = ksm(i,p-2)*F[i-1] %p; G[0] = 0;
}

void Pln(ll *F,ll *G,ll n) {   // G = ln(F) (mod x^n)
	ll *A=c3, *B=c4;
	memset(c3,0,sizeof(c3));
	memset(c4,0,sizeof(c4));
	Pdao(F, A, n);
	PI(F, B, n);
	PMUL(A, B, n, n);
	Pji(A, G, n);
}

void Pexp(ll *F,ll *G,ll n) {   // G = exp(F) (mod x^n)
	if(n==1) { G[0] = 1; return ; }
	Pexp(F, G, (n+1)>>1);
	ll *A=c5, *B=c6;
	for(ll i=0;i<=(n<<1);i++) A[i] = B[i] = 0;
	Pln(G, A, n);
	ll len = init(n+n);
	for(ll i=0;i<n;i++) B[i] = F[i];
	NTT(G, len, 1);
	NTT(A, len, 1);
	NTT(B, len, 1);
	for(ll i=0;i<len;i++) G[i] = (1ll-A[i]+B[i]+p) %p *G[i] %p;
	NTT(G, len, -1);
	for(ll i=n;i<len;i++) G[i] = 0;
}

void Pksm(ll *F,ll *G,ll K,ll n) {    //  G = F^K  (mod x^n)
	ll *A=c7;
	Pln(F, A, n);
	for(int i=0;i<n;i++) A[i] = A[i] * K %p;
	Pexp(A, G, n);
}

void stling() {
    for(int i=0;i<=n;i++) a[i] = ni[i+1];
    Pksm(a, c, K, n+1);
    for(int i=n;i>=0;i--) {
        if(i>=K) c[i] = c[i-K];
        else c[i] = 0;
    }
    for(int i=0;i<=n;i++) c[i] = c[i] * f[i] %p * ni[K] %p;
}

int main() {
	qiu();
    n = read(); K = read();
    stling();
    for(int i=0;i<=n;i++) cout<<c[i]<<" ";
    return 0;
}
