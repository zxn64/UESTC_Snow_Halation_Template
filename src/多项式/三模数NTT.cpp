const ll N=301010;
const ll inf=0x3f3f3f3f;
const ll p1=469762049, p2=998244353, p3=1004535809, g=3;
const ll M = p1 * p2;
typedef long double db;

ll n,m,P;
ll r[N];
ll a[N],b[N];
ll c1[N],c2[N];
ll A1[N],A2[N],A3[N];

inline ll ksm(ll aa,ll bb,ll p) {
	ll sum = 1;
	while(bb) {
		if(bb&1) sum = sum * aa %p;
		bb >>= 1; aa = aa * aa %p;
	}
	return sum;
}

inline ll gsc(ll aa,ll bb,ll p) {
	aa %= p; bb %= p;
	return (( aa * bb - (ll)( (ll)((db)aa / p * bb + 1e-3) * p)) %p + p) %p;
}

void NTT(ll *A,ll len,ll cl,ll p) {
	ll gi = ksm(3,p-2,p);
	for(ll i=0;i<len;i++) if(i<r[i]) swap(A[i],A[r[i]]);
	for(ll k=1;k<len;k<<=1) {
		ll g1 = ksm((cl==1)?g:gi, (p-1)/(k<<1), p);
		for(ll j=0;j<len;j+=(k<<1)) {
			ll gk = 1;
			for(ll i=0;i<k;i++,gk=gk*g1%p) {
				ll x = A[i+j], y = gk*A[i+j+k] %p;
				A[i+j] = (x+y) %p; A[i+j+k] = (x-y+p) %p;
			}
		}
	}
	if(cl==1) return ;
	ll inv = ksm(len,p-2, p);
	for(int i=0;i<len;i++) A[i] = A[i] * inv %p;
}

inline int init(int wo) {
	ll len = 1, L = 0; while(len<wo) len<<=1, L++;
	for(ll i=0;i<len;i++) r[i] = (r[i>>1]>>1) | ((i&1)<<(L-1));
	return len;
}

void PMUL(ll *F,ll *G,ll n,ll m) {  // F -> 1+..+x^n   G -> 1+...+x^m
	ll len = init(n+m+1);
	ll *A = c1, *B = c2;

	for(int i=0;i<len;i++) A[i] = (i<=n) ? F[i] : 0, B[i] = (i<=m) ? G[i] : 0;
	NTT(A,len,1,p1); NTT(B,len,1,p1);
	for(ll i=0;i<len;i++) A1[i] = A[i] * B[i] %p1;
	NTT(A1,len,-1,p1);
	
	for(int i=0;i<len;i++) A[i] = (i<=n) ? F[i] : 0, B[i] = (i<=m) ? G[i] : 0;
	NTT(A,len,1,p2); NTT(B,len,1,p2);
	for(ll i=0;i<len;i++) A2[i] = A[i] * B[i] %p2;
	NTT(A2,len,-1,p2);

	for(int i=0;i<len;i++) A[i] = (i<=n) ? F[i] : 0, B[i] = (i<=m) ? G[i] : 0;
	NTT(A,len,1,p3); NTT(B,len,1,p3);
	for(ll i=0;i<len;i++) A3[i] = A[i] * B[i] %p3;
	NTT(A3,len,-1,p3);

	for(int i=0;i<=n+m;i++) {
		ll wo = (gsc(A1[i]*p2%M, ksm(p2%p1, p1-2, p1), M) +
				 gsc(A2[i]*p1%M, ksm(p1%p2, p2-2, p2), M)) %M;
		ll K = ((A3[i]-wo) % p3 + p3) %p3 * ksm(M%p3, p3-2, p3) %p3;
		F[i] = ((K%P) * (M%P) %P + wo%P) %P;
	}
}


int main() {
    n = read(); m = read(); P = read();
    for(ll i=0;i<=n;i++) a[i] = read();
    for(ll i=0;i<=m;i++) b[i] = read();
    PMUL(a, b, n, m);
	for(ll i=0;i<=n+m;i++) cout<<a[i]<<" ";
    return 0;
}
