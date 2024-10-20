#include <bits/stdc++.h>
#define ll long long

using namespace std;
const ll N=2020202;
const ll inf=0x3f3f3f3f;
const ll p=1000000009;

ll K, da;
ll a[N],b[N],c[N];
ll A[22][N], B[22][N], C[22][N], wei[N];

inline void OR(ll *F,ll cl) {
	for(ll o=2;o<=da;o<<=1) {
		for(ll i=0,k=o>>1;i<da;i+=o) {
			for(ll j=0;j<k;j++) {
				F[i+j+k] = (F[i+j+k] + F[i+j]*cl + p) %p;
			}
		}
	}
}

void juan(ll *H,ll *F,ll *G) {
	for(ll i=0;i<da;i++) A[wei[i]][i] = F[i];
	for(ll i=0;i<da;i++) B[wei[i]][i] = G[i];
	for(ll i=0;i<=K;i++) {
		OR(A[i], 1);
		OR(B[i], 1);
	}
	for(ll i=0;i<=K;i++) {
		for(ll j=0;j<=i;j++) {
			for(ll k=0;k<da;k++) {
				(C[i][k] += A[j][k]*B[i-j][k] %p) %= p;
			}
		}
	}
	for(ll i=0;i<=K;i++) OR(C[i], -1);
	for(ll i=0;i<da;i++) H[i] = C[wei[i]][i];
}

int main() {
	for(ll i=1;i<=N-10;i++) wei[i] = wei[i^(i&-i)] + 1;
	K = read(); da = 1<<K;
	for(ll i=0;i<da;i++) a[i] = read();
	for(ll i=0;i<da;i++) b[i] = read();
	juan(c, a, b);
	for(ll i=0;i<da;i++) cout<<c[i]<<" ";
	return 0;
}