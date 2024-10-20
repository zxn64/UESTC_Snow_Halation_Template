
const ll N=501010;
const ll qwq=303030;
const ll inf=0x3f3f3f3f;
const ll p=998244353, g=3, gi=332748118, inv2=499122177;

ll n,m;
ll r[N];
ll a[N],b[N];
ll c1[N],c2[N],c3[N];
ll Q[N],R[N];
ll Fr[N],Gri[N],Gr[N];

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

void PDIV(ll *F,ll *G,ll *Q,ll *R,ll n,ll m) {  // F -> 1+..+x^n   G -> 1+...+x^m
	for(ll i=0;i<=n;i++) Fr[n-i] = F[i];
	for(ll i=0;i<=m;i++) Gr[m-i] = G[i];
	for(ll i=n-m+2;i<=m;i++) Gr[i] = 0;
	PI(Gr,Gri,n-m+1);
	PMUL(Fr,Gri,n,n-m);
	for(ll i=0;i<=n-m;i++) Q[n-m-i] = Fr[i];
	ll *A = c3;
	for(ll i=0;i<=n-m;i++) A[i] = Q[i];
	PMUL(G,A,m,n-m);
	for(ll i=0;i<m;i++) R[i] = (F[i]-G[i]+p)%p;
}

int main() {
    n = read(); m = read();
    for(ll i=0;i<=n;i++) a[i] = read();
    for(ll i=0;i<=m;i++) b[i] = read();
    PDIV(a,b,Q,R,n,m);
	for(ll i=0;i<=n-m;i++) cout<<Q[i]<<" ";
	cout<<endl;
	for(ll i=0;i<m;i++) cout<<R[i]<<" ";
    return 0;
}

/*

5 1
1 9 2 6 0 8
1 7

237340659 335104102 649004347 448191342 855638018
760903695

*/

