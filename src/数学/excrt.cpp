ll T;
ll n,m;
ll a[N],b[N];
ll x,y;

ll gsc(ll a,ll b,ll p) {
    ll sum = 0;
    while(b) {
        if(b&1) sum = (sum+a) %p;
        b >>= 1; a = (a<<1) %p;
    }
    return sum;
}

ll exgcd(ll A,ll B) {
    if(!B) { x = y = 0; return A; }
    ll res = exgcd(B,A%B);
    x = y; y = (res - A*x) / B;
    return res;
}

ll excrt() {
    ll M=a[1], res=b[1];
    for(ll i=2;i<=n;i++) {
        ll A = M, B = a[i], C = ((b[i]-res)%B+B)%B;  //Ax=C (mod B)
        ll d = exgcd(A,B);
        if(C%d) return -1;
        B /= d; C /= d;
        x = gsc(x,C,B);
        res += x * M;
        M *= B;
        res = (res%M+M) %M;
    }
    return res;
}

int main() {
    n = read();
    for(ll i=1;i<=n;i++) {
        a[i] = read(); b[i] = read();
    }
    cout<<excrt();
    return 0;
}

/*

5
998244353 469904850
998244389 856550978
998244391 656199240
998244407 51629743
998244431 642142204

99999999999000019

//this case cannot pass


*/

