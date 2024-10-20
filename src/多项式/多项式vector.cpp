#include <bits/stdc++.h>
#define ll long long
#define poly vector<ll>

using namespace std;
const ll N=301010;
const ll inf=0x3f3f3f3f;
const ll p=998244353, g=3, gi=332748118, inv2=499122177;


ll r[N];

inline ll ksm(ll aa,ll bb) {
	ll sum = 1;
	while(bb) {
		if(bb&1) sum = sum * aa %p;
		bb >>= 1; aa = aa * aa %p;
	}
	return sum;
}

inline int init(int wo) {
	ll len = 1; while(len<wo) len<<=1;
	for(ll i=0;i<len;i++) r[i] = (r[i>>1]>>1) | ((i&1)?len>>1:0);
	return len;
}

void NTT(poly &A, ll len, ll cl) {

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
	for(int i=0;i<len;i++) A[i] = A[i] * inv %p;
}

poly PMUL(poly A,poly B,ll mod=-1) {
	int deg = A.size() + B.size() - 1;
	if(A.size()<=32 || B.size()<=32) {
		poly C(deg, 0);
		for(int i=0;i<A.size();i++)
			for(int j=0;j<B.size();j++) 
				(C[i+j] += A[i] * B[j] %p) %= p;
		return C;
	}
	ll len = init(deg);
	A.resize(len); B.resize(len);
	NTT(A, len, 1);
	NTT(B, len, 1);
	for(int i=0;i<len;i++) A[i] = A[i] * B[i] %p;
	NTT(A, len, -1);
	if(mod==-1) A.resize(deg);
	else        A.resize(mod);
	return A;
}

poly PI(poly A,int deg=-1) {
	if(deg==-1) deg = A.size();
	poly B(1, ksm(A[0],p-2)), C;
	for(int k=2; (k>>1)<deg; k<<=1) {
		C.resize(k);
		ll len = init(k<<1);
		for(int i=0;i<k;i++) C[i] = i<(int)A.size() ? A[i] : 0;
		C.resize(len);
		B.resize(len);
		NTT(C, len, 1);
		NTT(B, len, 1);
		for(int i=0;i<len;i++) B[i] = (2ll - C[i]*B[i] %p + p) %p * B[i] %p;
		NTT(B, len, -1);
		B.resize(k);
	}
	B.resize(deg);
	return B;
}

poly SQRT(poly A,int deg=-1) { // a[0] = 1
	if(deg==-1) deg = A.size();
	poly B(1,1), C, D;
	ll len = 0;
	for(int k=4; (k>>2)<deg; k<<=1) {
		C = A;
		C.resize(k>>1);
		len = init(k);
		D = PI(B,k>>1);
		C.resize(len);
		D.resize(len);
		NTT(C, len, 1);
		NTT(D, len, 1);
		for(int i=0;i<len;i++) C[i] = C[i] * D[i] %p;
		NTT(C, len, -1);
		B.resize(k>>1);
		for(int i=0;i<(k>>1);i++) B[i] = (B[i] + C[i]) %p * inv2 %p;
	}
	B.resize(len);
	return B;
}

poly PDIV(poly A,poly B) {
	int deg = A.size() - B.size() + 1;
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());
	A.resize(deg);
	A = PMUL(A, PI(B,deg));
	A.resize(deg);
	reverse(A.begin(), A.end());
	return A;
}

poly PMOD(poly A,poly B) {
	if(A.size() < B.size()) return A;
	poly C = PMUL(B, PDIV(A, B));
	for(int i=0;i<A.size();i++) A[i] = (A[i] - C[i] + p) %p;
	A.resize(B.size()-1);
	return A;
}

poly Pksm2(poly A,ll K,ll mod) {  // log^2
	poly B(1,1);
	while(K) {
		if(K&1) B = PMUL(B, A, mod);
		K >>= 1; A = PMUL(A, A, mod);
	}
	return B;
}

poly Pdao(poly A) { for(int i=0;i+1<A.size();i++) A[i]=A[i+1]*(i+1)%p; A.pop_back(); return A; }
poly Pji(poly A) { for(int i=A.size()-1;i;i--) A[i]=A[i-1]*ksm(i,p-2)%p; A[0]=0; return A; }
poly Pln(poly A,ll mod=-1) {
	if(mod==-1) mod = A.size();
	A = Pji( PMUL( Pdao(A), PI(A,mod) ) );
	A.resize(mod);
	return A;
}
poly Pexp(poly A,ll mod=-1) {
	if(mod==-1) mod = A.size();
	poly B(1,1), C;
	for(int k=2;(k>>1)<mod;k<<=1) {
		C = Pln(B,k);
		for(int i=0;i<k;i++) C[i] = ((i<(int)A.size()?A[i]:0) - C[i] + p) %p;
		C[0]++;
		B = PMUL(B,C);
		B.resize(k);
	}
	B.resize(mod);
	return B;
}

poly Pksm(poly A,ll K,ll mod=-1) {
	if(mod==-1) mod = A.size();
	poly B = Pln(A);
	for(int i=0;i<mod;i++) B[i] = B[i] * K %p;
	A = Pexp(B);
	A.resize(mod);
	return A;
}

ll n,m,k;
poly a, b, e[N];

poly calc(int L,int R) {
	if(L==R) return e[L];
	int mid = L+R >> 1;
	poly A = calc(L,mid), B = calc(mid+1,R);
	return PMUL(A,B);
}

int main() {
	
	return 0;
}
