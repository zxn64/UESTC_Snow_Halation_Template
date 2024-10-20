const ll N=501010;
const ll qwq=303030;
const ll inf=0x3f3f3f3f;
const ll p=998244353, g=3, gi=332748118;

ll n,m;
ll rev[N],siz[N];
ll a[N],b[N];


inline ll ksm(ll aa,ll bb) {
	ll sum = 1;
	while(bb) {
		if(bb&1) sum = sum * aa %p;
		bb >>= 1; aa = aa * aa %p;
	}
	return sum;
}

void NTT(ll *A,ll len,ll cl) {
	for(ll i=0;i<len;i++) if(i<rev[i]) swap(A[i],A[rev[i]]);
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
	for(ll i=0;i<len;i++) A[i] = A[i] * inv %p;
}

void solve(ll now,ll l,ll r,ll *F,ll *G) {
	siz[now] = r-l+1;
	if(l==r) {
		G[0] = F[l]; G[1] = 1;   // a[i] + x
		return ;
	}
	ll len = 1, L = 0; while(len<=siz[now]) len<<=1, L++;
	for(int i=0;i<len;i++) G[i] = 0;
	ll A[len], B[len], mid = l+r >> 1;
	solve(ls, l, mid, F, A);
	solve(rs, mid+1, r, F, B);
	if(r-l<32) {
		for(ll i=0;i<=siz[ls];i++)
			for(ll j=0;j<=siz[rs];j++)
				G[i+j] = (G[i+j] + A[i] * B[j] %p) %p;
		return ;
	}
	for(int i=siz[ls]+1;i<len;i++) A[i] = 0;
	for(int i=siz[rs]+1;i<len;i++) B[i] = 0;
	for(ll i=0;i<len;i++) rev[i] = (rev[i>>1]>>1) | ((i&1)<<(L-1));
	NTT(A, len, 1);
	NTT(B, len, 1);
	for(ll i=0;i<len;i++) G[i] = A[i] * B[i] %p;
	NTT(G, len, -1);
}

int main() {
    n = read();
    for(ll i=1;i<=n;i++) a[i] = read();
    solve(1, 1, n, a, b);
	for(ll i=0;i<=n;i++) cout<<b[i]<<" ";
    return 0;
}


/*

10
10 9 8 7 6 5 4 3 2 1

3628800 10628640 12753576 8409500 3416930 902055 157773 18150 1320 55 1

*/

