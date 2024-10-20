const int N=101010;
const int qwq=303030;
const int inf=0x3f3f3f3f;
typedef double db;

int n,cnt;
struct D{
	double x,y;
	D(double xx=0,double yy=0) { x=xx, y=yy; }
} d[N],st[N];
D  operator - (D A,D B) { return {A.x-B.x,A.y-B.y}; }
db operator ^ (D A,D B) { return A.x*B.y - B.x*A.y; }
inline bool cmp(D aa,D bb) { return (aa.x==bb.x) ? (aa.y<bb.y) : (aa.x<bb.x); }
double ans;

double ju(D aa,D bb) { return sqrt( (aa.x-bb.x)*(aa.x-bb.x) + (aa.y-bb.y)*(aa.y-bb.y) ); }

void TUBAO() {
	st[1] = d[1]; st[2] = d[2]; cnt = 2;
	for(int i=3;i<=n;i++) {
		while(cnt>1 && ((st[cnt]-st[cnt-1])^(d[i]-st[cnt-1]))<=0) cnt--;
		st[++cnt] = d[i];
	}
	st[++cnt] = d[n-1];
	for(int i=n-2;i>=1;i--) {
		while(cnt>1 && ((st[cnt]-st[cnt-1])^(d[i]-st[cnt-1]))<=0) cnt--;
		st[++cnt] = d[i];
	}
}

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&d[i].x,&d[i].y);
	sort(d+1,d+n+1,cmp);
	if(n==1) { cout<<0; return 0; }
	TUBAO();
	for(int i=2;i<=cnt;i++) ans += ju(st[i],st[i-1]);
	printf("%.2lf",ans);
	return 0;
}
