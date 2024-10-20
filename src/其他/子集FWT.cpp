#include <bits/stdc++.h>
#define ll long long

using namespace std;
const ll N=501010;
const ll inf=0x3f3f3f3f;
const ll p=998244353, inv2=499122177;

inline ll read() {
    ll sum = 0, ff = 1; char c = getchar();
    while(c<'0' || c>'9') { if(c=='-') ff = -1; c = getchar(); }
    while(c>='0'&&c<='9') { sum = (sum * 10 + c - '0') %p; c = getchar(); }
    return sum * ff;
}

ll K, da;
ll a[N],b[N],c[N];
ll A[N],B[N];

inline void OR(ll *F,ll cl) {
	for(ll o=2;o<=da;o<<=1) {
		for(ll i=0,k=o>>1;i<da;i+=o) {
			for(ll j=0;j<k;j++) {
				F[i+j+k] = (F[i+j+k] + F[i+j]*cl + p) %p;
			}
		}
	}
}

inline void AND(ll *F,ll cl) {
	for(ll o=2;o<=da;o<<=1) {
		for(ll i=0,k=o>>1;i<da;i+=o) {
			for(ll j=0;j<k;j++) {
				F[i+j] = (F[i+j] + F[i+j+k]*cl + p) %p;
			}
		}
	}
}

inline void XOR(ll *F,ll cl) {
	for(ll o=2;o<=da;o<<=1) {
		for(ll i=0,k=o>>1;i<da;i+=o) {
			for(ll j=0;j<k;j++) {
				ll X = F[i+j], Y = F[i+j+k];
				F[i+j] = (X+Y) * (cl==1?1:inv2) %p;
				F[i+j+k] = (X-Y+p) * (cl==1?1:inv2) %p;
			}
		}
	}
}

void juan(ll *H,ll *F,ll *G) {
	for(int i=0;i<da;i++) A[i] = F[i], B[i] = G[i];
	OR(A, 1);
	OR(B, 1);
	for(int i=0;i<da;i++) A[i] = A[i] * B[i] %p;
	OR(A, -1);
	for(int i=0;i<da;i++) H[i] = A[i];
}

int main() {
	K = read(); da = 1<<K;
	for(ll i=0;i<da;i++) a[i] = read();
	for(ll i=0;i<da;i++) b[i] = read();
	juan(c, a, b);
	for(ll i=0;i<da;i++) cout<<c[i]<<" ";
	return 0;
}