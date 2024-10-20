#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define FOR() ll le=e[u].size();for(ll i=0;i<le;i++)
#define QWQ cout<<"QwQ\n";
#define ll long long
#include <vector>
#include <queue>
#include <map>

using namespace std;
const ll N=801010;
const ll qwq=303030;
const ll inf=0x3f3f3f3f;
const ll p=167772161, g=3, gi=55924054;

inline ll read() {
    ll sum = 0, ff = 1; char c = getchar();
    while(c<'0' || c>'9') { if(c=='-') ff = -1; c = getchar(); }
    while(c>='0'&&c<='9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return sum * ff;
}

ll f[N],ni[N];
ll rev[N];
ll a[N];
ll c1[N],c2[N],c3[N];

inline ll ksm(ll aa,ll bb) {
    ll sum = 1;
    while(bb) {
        if(bb&1) sum = sum * aa %p;
        bb >>= 1; aa = aa * aa %p;
    }
    return sum;
}

void qiu() {
    f[0] = ni[0] = 1;
    for(ll i=1;i<=N-10;i++) f[i] = f[i-1] * i %p;
    ni[N-10] = ksm(f[N-10],p-2);
    for(ll i=N-11;i>=1;i--) ni[i] = ni[i+1] * (i+1) %p;
}

void NTT(ll *A,ll len,ll cl) {
    for(ll i=0;i<len;i++) if(i<rev[i]) swap(A[i],A[rev[i]]);
    for(ll k=1;k<len;k<<=1) {
        ll g1 = ksm((cl==1)?g:gi, (p-1)/(k<<1));
        for(ll j=0;j<len;j+=(k<<1)) {
            ll gk = 1;
            for(ll i=0;i<k;i++,gk=gk*g1%p) {
                ll x = A[i+j], y = gk*A[i+j+k] %p;
                A[i+j] = (x+y) %p; A[i+j+k] = (x-y+p) %p;
            }
        }
    }
    if(cl==1) return ;
    ll inv = ksm(len,p-2);
    for(int i=0;i<len;i++) A[i] = A[i] * inv %p;
}

inline int init(int wo) {
    ll len = 1, L = 0; while(len<wo) len<<=1, L++;
    for(ll i=0;i<len;i++) rev[i] = (rev[i>>1]>>1) | ((i&1)<<(L-1));
    return len;
}

void PMUL(ll *F,ll *G,ll n,ll m) {  // F -> 1+..+x^n   G -> 1+...+x^m
    ll len = init(n+m+1);
    NTT(F,len,1);
    NTT(G,len,1);
    for(ll i=0;i<len;i++) F[i] = F[i] * G[i] %p;
    NTT(F,len,-1);
}

void solve(ll *F,ll m) {
    if(m==1) { F[1] = 1; return ; }
    if(m&1) {
        solve(F, m-1);
        for(ll i=m;i>=1;i--) F[i] = (F[i-1] + F[i] * (m-1) %p) %p;
        F[0] = F[0] * (m-1) %p;
    }
    else {
        ll n = m/2;
        ll res = 1, *A = c1, *B = c2, *G = c3;
        solve(F, n);
        for(ll i=0;i<=n;i++) {
            A[i] = F[i] * f[i] %p;
            B[i] = res * ni[i] %p;
            res = res * n %p;
        }
        reverse(A, A+n+1);
        PMUL(A, B, n, n);
        for(ll i=0;i<=n;i++) G[i] = ni[i] * A[n-i] %p;
        PMUL(F, G, n, n);
        ll len = 1; while(len < (n+1)<<1) len <<= 1;
        for(ll i=n+1;i<len;i++) A[i] = B[i] = G[i] = 0;
        for(ll i=m+1;i<len;i++) F[i] = 0;
    }
}

int main() {
	qiu();
    ll n;
    n = read();
    solve(a, n);
    for(ll i=0;i<=n;i++) cout<<(a[i]%p+p)%p<<" ";
    return 0;
}
