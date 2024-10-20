struct Hash {
    ll p=998244353, m1=2333, m2=13331;
    ll f1[N], f2[N];
    ll h[N][N], a[N][N];

    void init() {
        f1[0] = f2[0] = 1;
        for(int i=1;i<=n;i++) f1[i] = f1[i-1] * m1 %p;
        for(int i=1;i<=m;i++) f2[i] = f2[i-1] * m2 %p;
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=m;j++) {
                h[i][j] = (h[i-1][j]*m1%p + h[i][j-1]*m2%p - h[i-1][j-1]*m1%p*m2%p + a[i][j] + p) %p;
            }
        }
    }
    
    ll calc(ll i,ll j,ll I,ll J) {
        i--; j--;
        ll X = f1[I-i], Y = f2[J-j];
        return (h[I][J] - h[i][J]*X%p - h[I][j]*Y%p + h[i][j]*X%p*Y%p + 2*p) %p;
    }
};
