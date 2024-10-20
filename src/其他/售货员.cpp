#define ls now<<1
#define rs now<<1|1
using namespace std;
const int N=1044*1044;
const int qwq=2003030;
const int inf=0x3f3f3f3f;

int n,tot;
int w[23][23];
int f[N][21];
int ans=inf;


int main() {
	n = read(); tot = (1<<n)-1;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) w[i][j] = read();

	memset(f,0x3f,sizeof(f));
	f[1][1] = 0;
	for(int i=3;i<=tot;i++) {
		for(int j=1;j<=n;j++) {
			if((i>>j-1)&1)
			for(int k=1;k<=n;k++)
				if((i>>k-1)&1)
					f[i][j] = min(f[i][j], f[i^(1<<j-1)][k]+w[j][k]);
		}
	}
	// cout<<f[tot][n]; 终点ｎ结束
	// cout<<MIN{ f[tot][i] }; 任意点结束
	// cout<<MIN{ w[1][i]+f[tot][i] }; 返回 1 结束
	return 0;
}

/*



*/
