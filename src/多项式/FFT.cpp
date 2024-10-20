const ll N=3001010;
const ll qwq=303030;
const ll inf=0x3f3f3f3f;
typedef long double db;
const db pi = acos(-1.0);


int n,m;
int r[N];
complex <db> F[N],G[N],ans[N];

void FFT(complex <db> *A,int len,int cl) {
	for(int i=0;i<len;i++) if(i<r[i]) swap(A[i],A[r[i]]);
	for(int k=1;k<len;k<<=1) {
		complex <db> w1( cos(pi/k), cl*sin(pi/k) );
		for(int j=0;j<len;j+=(k<<1)) {
			complex <db> wk(1,0);
			for(int i=0;i<k;i++,wk*=w1) {
				complex <db> x = A[i+j], y = wk*A[i+j+k];
				A[i+j] = x+y; A[i+j+k] = x-y;
			}
		}
	}
	if(cl==-1) for(int i=0;i<len;i++) A[i].real(A[i].real()/len);
}

inline int init(int wo) {
	ll len = 1, L = 0; while(len<wo) len<<=1, L++;
	for(ll i=0;i<len;i++) r[i] = (r[i>>1]>>1) | ((i&1)<<(L-1));
	return len;
}

int main() {
    n = read(); m = read();
    int len = init(n+m+1);
    for(int i=0;i<=n;i++) F[i].real(read());
    for(int i=0;i<=m;i++) G[i].real(read());
    FFT(F,len,1);
	FFT(G,len,1);
	for(int i=0;i<len;i++) ans[i] = F[i] * G[i];
	FFT(ans,len,-1);
	for(int i=0;i<=n+m;i++) cout<<(int)round(ans[i].real())<<" ";
    return 0;
}
