int n,m;
char z[N],s[N<<1];
int p[N<<1];
int R,id;
int ans;

void SAKI() {
	for(int i=1;i<=n;i++) {
		if(i<=R) p[i] = min(p[id*2-i],R-i+1);
		else     p[i] = 1;
		while(s[i+p[i]]==s[i-p[i]]) p[i]++;
		if(i+p[i]-1 > R) R = i+p[i]-1, id = i;
	}
}

int main() {
	scanf("%s",z+1); m = strlen(z+1);
	for(int i=1;i<=m;i++) s[(i<<1)-1] = '#', s[i<<1] = z[i];
	n = m*2 + 1; s[n] = '#'; s[n+1] = '@';
	SAKI();
	cout<<s+1<<"\n";
	for(int i=1;i<=n;i++) cout<<p[i]<<" ";
	return 0;
}