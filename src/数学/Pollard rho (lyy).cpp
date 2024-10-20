#define ll long long
#define lll __int128

const ll N=501010;
const ll qwq=303030;
const ll inf=0x3f3f3f3f;

ll T;
ll n,m;
map <ll,ll> f;
ll zz[] = {2,3,5,7,11,13,17,19,23};


ll gcd(ll aa,ll bb) { return !bb ? aa : gcd(bb,aa%bb); }

inline ll gsc(ll aa,ll bb,ll p) {
    return (lll)aa*bb %p;
    // ll sum = 0;
    // while(bb) {
    //     if(bb&1) sum = (sum+aa) %p;
    //     bb >>= 1; aa = (aa+aa) %p;
    // }
    // return sum;
}

inline ll ksm(ll aa,ll bb,ll p) {
    ll sum = 1;
    while(bb) {
        if(bb&1) sum = gsc(sum,aa,p);
        bb >>= 1; aa = gsc(aa,aa,p);
    }
    return sum;
}

inline bool miller_rabin(ll h,ll b) {
    ll k = h-1;
    while(k) {
        ll now = ksm(b,k,h);
        if(now!=1 && now!=h-1) return 0;
        if(k&1 || now==h-1) return 1;
        k >>= 1;
    }
    return 1;
}

inline bool prime(ll h) {
    if(h==1) return 0;
    if(h==2 || h==3 || h==5 || h==7 || h==11 || h==13 || h==17 || h==19 || h==23) return 1;
    for(ll i=0;i<9;i++) if(!miller_rabin(h,zz[i])) return 0;
    return 1;
}

ll pollard_rho(ll h) {  //h cannot be prime
    ll c = 1919810;
    if(h==4) return 2;
    while(1) {
        auto F = [=](ll x) { return (gsc(x,x,h) + c) % h; };
        c--;
        ll t=0, r=0, p=1, q;
        do {
            for(int i=0;i<128;i++) {
                t = F(t); r = F(F(r));
                if(t==r || (q = gsc(p,abs(t-r),h)) == 0) break;
                p = q;
            }
            ll d = gcd(p,h);
            if(d>1) return d;
        } while(t!=r);
    }
}

void divide(ll h) {
    if(h==1) return;
    if(prime(h)) { f[h]++; return ; }
    ll d = pollard_rho(h);
    // cout<<"h = "<<h<<" d = "<<d<<endl;
    // system("pause");
    divide(d); divide(h/d);
}

void chushihua() {
    f.clear();
}

int main() {
    srand(time(NULL));
	T = read();
	while(T--) {
        chushihua();
    	n = read();
        if(prime(n)) { cout<<"Prime\n"; continue; }
        divide(n);
        // for(auto it=f.begin();it!=f.end();it++) cout<< it->first <<" ^ "<< it->second <<"\n";
        auto it = --f.end();
        cout<< it->first <<endl;
	}
    return 0;
}
