ll n;
ll a[N];
ll d[N];
ll ans;

int main() {
	n = read();
	for(ll i=1;i<=n;i++) a[i] = read();
	for(ll i=1;i<=n;i++) {
		ll x = a[i];
		for(ll j=60;j>=0;j--) {
			if(!(x>>j)) continue;
			if(!d[j]) {
				d[j] = x;
				break;
			}
			x ^= d[j];
		}
	}
	for(ll j=60;j>=0;j--) {
		if((ans^d[j])>ans) ans ^= d[j];
	}
	cout<<ans;

	return 0;
}