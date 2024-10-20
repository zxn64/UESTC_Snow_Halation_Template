const ll N=501010;
const ll qwq=303030;
const ll inf=0x3f3f3f3f;
const ll p=998244353, g=3, gi=332748118, inv2=499122177;


ll n,m;
ll r[N];
ll a[N],b[N],c1[N],c2[N],c3[N],c4[N];

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

void SQRT(ll *F,ll *G,ll n) {  // G*G = F (mod x^n)
	G[0] = 1;
	ll *A=c3, *B=c4, k=1;
	for(ll len,L=1;k<(n+n);k<<=1,L++) {
		len = k<<1;
		for(ll i=0;i<k;i++) A[i] = F[i];
		PI(G, B, k);
		for(ll i=0;i<len;i++) r[i] = (r[i>>1]>>1) | ((i&1)<<(L-1));
		NTT(A, len, 1);
		NTT(B, len, 1);
		for(ll i=0;i<len;i++) A[i] = A[i] * B[i] %p;
		NTT(A, len, -1);
		for(ll i=0;i<k;i++) G[i] = (G[i] + A[i]) %p * inv2 %p;
		for(ll i=k;i<len;i++) G[i] = 0;
	}
	for(ll i=0;i<k;i++) A[i] = B[i] = 0;
	for(ll i=n;i<k;i++) G[i] = 0;
}

int main() {
    n = read();
    for(ll i=0;i<n;i++) a[i] = read();
    SQRT(a, b, n);
	for(ll i=0;i<n;i++) cout<<b[i]<<" ";
    return 0;
}

/*

7
1 8596489 489489 4894 1564 489 35789489  

1 503420421 924499237 13354513 217017417 707895465 411020414

*/
