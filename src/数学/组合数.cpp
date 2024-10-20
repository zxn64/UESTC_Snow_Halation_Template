ll f[N],ni[N];

inline ll ksm(ll aa,ll bb) {
    ll sum = 1;
    while(bb) {
        if(bb&1) sum = sum * aa %p;
        bb >>= 1; aa = aa * aa %p;
    }
    return sum;
}

inline ll C(ll aa,ll bb) { return f[aa] * ni[bb] %p * ni[aa-bb] %p; }

void qiu() {
    f[0] = ni[0] = 1;
    for(ll i=1;i<=N-10;i++) f[i] = f[i-1] * i %p;
    ni[N-10] = ksm(f[N-10],p-2);
    for(ll i=N-11;i>=1;i--) ni[i] = ni[i+1] * (i+1) %p;
}