typedef long double db;
const ll N=2010;
const ll qwq=2030303;
const ll inf=0x3f3f3f3f3f3f3f3f;


ll n,m,ans;
ll mpx[N],mpy[N],visx[N],visy[N],lx[N],ly[N];
ll li[N][N],slack[N],pre[N];

void BFS(ll u) {
	ll x,y=0,yy=0,d;
	memset(pre,0,sizeof(pre));
	memset(slack,0x3f,sizeof(slack));
	mpy[y] = u;
	while(1) {
		x = mpy[y]; d = inf; visy[y] = 1;
		for(int i=1;i<=n;i++) {
			if(visy[i]) continue;
			if(slack[i] > lx[x]+ly[i]-li[x][i]) {
				slack[i] = lx[x]+ly[i]-li[x][i];
				pre[i] = y;
			}
			if(slack[i]<d) {
				d = slack[i];
				yy = i;
			}
		}
		for(int i=0;i<=n;i++) {
			if(visy[i]) lx[mpy[i]] -= d, ly[i] += d;
			else slack[i] -= d;
		}
		y = yy;
		if(mpy[y]==-1) break;
	}
	while(y) {
		mpy[y] = mpy[pre[y]];
		y = pre[y];
	}
}

int main() {
	ll x,y,z;
	n = read(); m = read();
	memset(li,-0x3f,sizeof(li));
	memset(mpy,-1,sizeof(mpy));
	for(ll i=1;i<=m;i++) {
		x = read(); y = read(); z = read();
		li[x][y] = max(li[x][y], z);
	}

	for(ll i=1;i<=n;i++) {
		memset(visy,0,sizeof(visy));
		BFS(i);
	}

	ll ans = 0;
	for(ll i=1;i<=n;i++) ans += li[mpy[i]][i];
	cout<<ans<<"\n";
	for(ll i=1;i<=n;i++) cout<<mpy[i]<<" ";
	return 0;
}