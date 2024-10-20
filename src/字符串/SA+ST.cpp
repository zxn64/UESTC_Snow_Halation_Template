const ll N=2010101;
const ll qwq=N*3;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,Q;
int ob[N];

struct SAST{
	int m;
	char s[N];
	int sa[N],rk[N],tp[N],c[N],h[N];
	int f[N][22];

	void Qsort() {
		memset(c,0,sizeof(c));
		for(int i=1;i<=n;i++) c[rk[i]]++;
		for(int i=1;i<=m;i++) c[i] += c[i-1];
		for(int i=n;i>=1;i--) sa[ c[rk[tp[i]]]-- ] = tp[i];
	}

	void SA() {
		m = 75;
		for(int i=1;i<=n;i++) rk[i] = s[i] - 'a' + 1, tp[i] = i;
		Qsort();
		for(int k = 1; ;k <<= 1) {
			int p = 0;
			for(int i=1;i<=k;i++) tp[++p] = n - k + i;
			for(int i=1;i<=n;i++) if(sa[i] > k) tp[++p] = sa[i] - k;
			Qsort();
			swap(tp,rk);
			rk[sa[1]] = p = 1;
			for(int i=2;i<=n;i++) {
				if(tp[sa[i-1]]==tp[sa[i]] && tp[sa[i-1]+k]==tp[sa[i]+k])
					rk[sa[i]] = p;
				else
					rk[sa[i]] = ++p;
			}
			m = p;
			if(p==n) break;
		}
		int b;
		for(int i=1,l=0;i<=n;h[rk[i++]]=l)
		for(l=(l?l-1:0),b=sa[rk[i]-1];s[i+l]==s[b+l];++l);

		for(int i=1;i<=n;i++) f[i][0] = h[i];
		for(int k=1;k<=18;k++)
			for(int i=1;i+(1<<k)-1<=n;i++)
				f[i][k] = min(f[i][k-1],f[ i+(1<<(k-1)) ][k-1]);
	}

	inline int LCP(int i,int j) {
		if(i<1 || j<1 || i>n || j>n) return 0;
		if(i==j) return n-i+1;
		i = rk[i]; j = rk[j];
		if(i>j) swap(i,j);
		i++;
		int k = ob[j-i+1];
		return min(f[i][k],f[j-(1<<k)+1][k]);
	}

}zheng,dao;

int main() {
	for(int i=2;i<=N-1000;i++) ob[i] = ob[i>>1] + 1;

	n = read(); Q = read();
	scanf("%s",zheng.s+1);
	zheng.SA();

	int x,y;
	while(Q--) {
		x = read(); y = read();
		cout<<zheng.LCP(x,y)<<"\n";
	}
    return 0;
}


/*



*/
