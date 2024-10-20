#include<stdio.h>
#define rint register int

typedef long long ll;

const int N=(1<<22)+7;
const int Mod=998244353;
const int G=3;

ll qpow(ll x,int y=Mod-2){
    ll ret=1;
    while(y){
        if(y&1) ret=ret*x%Mod;
        x=x*x%Mod,y>>=1; 
    }
    return ret;
}

const int Gi=qpow(G);

int rk[N];
inline void swap(ll &x,ll &y){x^=y,y^=x,x^=y;}
void NTT(bool op,int n,ll *F){
    for(rint i=0;i<n;i++)
        if(i<rk[i]) swap(F[i],F[rk[i]]);
    for(rint p=2;p<=n;p<<=1){
        rint len=p>>1;
        ll w=qpow(op? G:Gi,(Mod-1)/p);
        for(rint k=0;k<n;k+=p){
            ll now=1;
            for(rint l=k;l<k+len;l++){
                ll t=F[l+len]*now%Mod;
                F[l+len]=(F[l]-t+Mod)%Mod;
                F[l]=(F[l]+t)%Mod;
                now=now*w%Mod;
            }
        }
    }
}

inline void Cop(int n,ll *a,ll *b){for(int i=0;i<n;i++)a[i]=b[i];}
inline void Clear(int n,ll *F){for(int i=0;i<n;i++)F[i]=0;}
inline void Rk(int n){for(int i=0;i<n;i++)rk[i]=(rk[i>>1]>>1)|(i&1? n>>1:0);}

void Mul(ll *X,int n,int m,ll *a,ll *b){
	static ll x[N],y[N];
    Cop(n+1,x,a),Cop(m+1,y,b);
    for(m+=n,n=1;n<=m;n<<=1); Rk(n);
    NTT(1,n,x),NTT(1,n,y);
    for(rint i=0;i<n;i++) x[i]=x[i]*y[i]%Mod;
    NTT(0,n,x); ll inv=qpow(n);
    for(rint i=0;i<=m;i++) X[i]=x[i]*inv%Mod;
    Clear(n,x),Clear(n,y);
}

void Inv(int n,ll *a,ll *b){
	static ll x[N];
	if(n==1){b[0]=qpow(a[0]);return;}
	Inv((n+1)>>1,a,b); int m=n;
	for(n=1;n<(m<<1);n<<=1); Rk(n);
	Clear(n,x),Cop(m,x,a);
	NTT(1,n,x),NTT(1,n,b);
	for(rint i=0;i<n;i++)
		b[i]=b[i]*(2-x[i]*b[i]%Mod+Mod)%Mod;
	NTT(0,n,b); ll inv=qpow(n);
	for(rint i=0;i<m;i++) b[i]=b[i]*inv%Mod;
	for(rint i=m;i<n;i++) b[i]=0;
}

ll a[N],b[N],c[N];

ll calc(int n,int K){
    Clear(n+3,a),Clear(n+3,b);
    a[0]=1,a[1]=Mod-2,a[K+2]=1;
    Inv(n+3,a,b);
    a[0]=1,a[1]=Mod-1,a[K+2]=0;
    Mul(c,n+3,n+3,a,b);
    // printf("[%d %d]\n",n,K);
    // for(int i=1;i<=n+1;i++) printf("%lld ",c[i]);
    // printf("\n");
    return c[n+1];
}

int main(){
    int n=read(),K=read();
    // printf("%lld\n",calc(n,K));
    printf("%lld",(calc(n,K)-calc(n,K-1)+Mod)%Mod);
}