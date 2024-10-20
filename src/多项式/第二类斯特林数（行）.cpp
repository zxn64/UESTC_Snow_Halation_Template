const ll N=801010;
const ll qwq=303030;
const ll inf=0x3f3f3f3f;
const ll p=167772161, g=3, gi=55924054;

ll n,m;
ll r[N];
ll a[N],b[N];
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
			for(ll i=0;i<k;i++,gk=gk*g1%p) {
				ll x = A[i+j], y = gk*A[i+j+k] %p;
				A[i+j] = (x+y) %p; A[i+j+k] = (x-y+p) %p;
			}
		}
	}
	if(cl==1) return ;
	ll inv = ksm(len,p-2);
	for(int i=0;i<len;i++) A[i] = A[i] * inv %p;
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


int main() {
	qiu();
	n = read();
	for(int i=0;i<=n;i++) {
		a[i] = (p+((i&1)?-1:1) * ni[i]) %p;
		b[i] = ksm(i,n) * ni[i] %p;
	}
	PMUL(a,b,n,n);
	for(int i=0;i<=n;i++) cout<<a[i]<<" ";
    return 0;
}


/* 通项公式:

for(int i=0;i<=k;i++) S(n,k) += ((-1)^(k-i) * i^n) / (i! * (k-i)!)

*/