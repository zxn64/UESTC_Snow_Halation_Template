ll T;
ll m,P;
struct D{
	ll l,r;
}d[N];
inline bool cmp(D A,D B) { return A.l < B.l; }
ll cnt;

void get_fen(ll R,ll X) {   // [0, R] ^= X   --->  [ d[i].l, d[i].r ]
	ll da = 1ll << 60ll;
	d[cnt=1] = {0,R};
	for(ll i=60;i>=0;i--,da>>=1) {
		if(d[1].l+da<=d[1].r) {
			if((X>>i)&1) {
				d[++cnt] = {d[1].l+da,d[1].l+2*da-1};
				d[1].r -= da;
			}
			else {
				d[++cnt] = {d[1].l,d[1].l+da-1};
				d[1].l += da;
			}
		}
		else if((X>>i)&1) d[1].l += da, d[1].r += da;
	}
	sort(d+1,d+cnt+1,cmp);
	// for(ll i=1;i<=cnt;i++) cout<<d[i].l<<" "<<d[i].r<<"\n";
}