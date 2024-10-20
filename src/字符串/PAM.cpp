struct PAM {
	int a[N];
	int cnt=1, lst=0;
	int ch[N][26],fail[N],len[N],dep[N];

	int getfail(int i,int x) {
		while(a[i-len[x]-1] != a[i]) x = fail[x];
		return x;
	}

	void built() {
		len[1] = -1; fail[0] = 1;
		a[0] = -2333;
		for(int i=1;i<=n;i++) {
			int u = getfail(i,lst), c = a[i];
			if(!ch[u][c]) {
				int w = getfail(i,fail[u]);
				len[++cnt] = len[u] + 2;
				fail[cnt] = ch[w][c];
				dep[cnt] = dep[ fail[cnt] ] + 1;
				ch[u][c] = cnt;
			}
			lst = ch[u][c];
		}
	}
} P;