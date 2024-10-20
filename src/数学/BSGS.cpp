map <ll,ll> f;

inline ll BSGS(ll a,ll b,ll p) { // a ^ res = b (mod p)
	f.clear();
	ll now = b % p;
	ll sq = sqrt(p) + 1;
	ll at = ksm(a,sq,p);
	f[now] = 0;
	for(ll i=1;i<=sq;i++) {
		now = now * a %p;
		f[now] = i;
	}
	now = 1;
	for(ll i=1;i<=sq;i++) {
		now = now * at %p;
		if(f[now]) return (i * sq %p - f[now] + p) %p;
	}
	return -1;
}