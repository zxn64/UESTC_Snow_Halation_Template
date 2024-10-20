#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=301010;
const ll inf=0x3f3f3f3f;

ll T;
ll n,m,p;
ll f[N];

ll ksm(ll a,ll b) { ll sum = 1; while(b) { if(b&1) sum = (sum*a) % p; b >>= 1; a = (a*a) % p; } return sum; }

ll C(ll a,ll b) { if(b>a) return 0; return f[a] * ksm(f[b],p-2) % p * ksm(f[a-b],p-2) % p; }

ll Lucas(ll a,ll b) { if(!b) return 1; return C(a%p,b%p) * Lucas(a/p,b/p) % p; }

inline void qiu() { f[0] = 1; for(ll i=1;i<=n+m;i++) f[i] = f[i-1] * i % p; }

int main() {
	cin>>T;
	while(T--) {
		cin>>n>>m>>p;
		qiu();
		cout<<Lucas(n+m,m)<<"\n";
	}
	return 0;
}
