const ll N=501010;
const ll qwq=3030303;
const ll inf=0x3f3f3f3f;

ll T;
ll n,m;
ll visp[qwq],pi[N],cntp;
ll st[N],cnt1;


inline ll ksm(ll aa,ll bb) {
	ll sum = 1;
	while(bb) {
		if(bb&1) sum = sum * aa %n;
		bb >>= 1; aa = aa * aa %n;
	}
	return sum;
}

void shai(ll h) {
	for(ll i=2;i<=h;i++) {
		if(!visp[i]) pi[++cntp] = i;
		for(ll j=1;j<=cntp && i*pi[j]<=h;j++) {
			visp[ i*pi[j] ] = 1;
			if(i%pi[j]==0) break;
		}
	}
}

void chushihua() {
    cnt1 = 0;
}

int get_root(int P) {
    ll now = P-1;
    for(ll i=1;i<=cntp;i++) {
        if(now%pi[i]==0) st[++cnt1] = pi[i];
        while(now%pi[i]==0) now /= pi[i];
    }
    if(now!=1) st[++cnt1] = now;
    // for(ll i=1;i<=cnt1;i++) cout<<st[i]<<" ";
    for(ll i=2;;i++) {
        bool you = 0;
        for(ll j=1;j<=cnt1;j++) if(ksm(i,(P-1)/st[j])==1) { you = 1; break; }
        if(!you) return i;
    }
}

int main() {
	shai(qwq-100);
    while(1) {
        chushihua();
        cin>>n;
        cout<<get_root(n)<<"\n";
    }
    return 0;
}

// n has r when n=1,2,4,p^a,2p^a

// 7 -> 3     1,3,2,6,4,5