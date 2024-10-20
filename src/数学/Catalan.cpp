#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=101010;
const ll p=998244353;

ll T;
ll n;
ll f[N],ni[N];

ll ksm(ll a,ll b) { ll sum = 1; while(b) { if(b&1) sum = (sum*a) % p; b >>= 1; a = (a*a) % p; } return sum; }

void qiu(ll h) {
	f[0] = ni[0] = 1;
	for(ll i=1;i<=h;i++) f[i] = f[i-1] * i %p;
	ni[h] = ksm(f[h],p-2);
	for(ll i=h-1;i;i--) ni[i] = ni[i+1] * (i+1) %p;
}

ll catalan(ll a) { return f[a<<1] * ni[a+1] %p * ni[a] %p; }
ll catalan(ll a) { return C(2*a,a) - C(2*a,a-1); }
ll catalan(ll a) { if(!a) return 1; ll res = 0; for(int i=0;i<=a-1;i++) res += catalan(i) * catalan(a-1-i); return res; }

int main() {
	qiu(N-10);
	cin>>T;
	while(T--) {
		cin>>n;
		cout<<catalan(n)<<endl;
	}
	return 0;
}