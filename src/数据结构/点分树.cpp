#include<stdio.h>
#include<vector>
using namespace std;

inline int read(){
	int x=0,flag=1; char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')flag=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
	return flag*x;
}

const int N=1e5+7;

int fa[N][20],sz[N],dep[N],Fa[N][20],Dis[N][20],Dep[N],v[N];
vector<int> g[N],C[N][2];
bool vis[N];

inline void swap(int &x,int &y){x^=y^=x^=y;}
int Lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=16;~i;i--)
		if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	if(x==y) return y;
	for(int i=16;~i;i--)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

inline int lowbit(const int &x){return -x&x;}
inline void add(vector<int> &V,int x,int val){
	while(x<(int)V.size())V[x]+=val,x+=lowbit(x);
}
inline int query(vector<int> &V,int x){
	x=min((int)V.size()-1,x);
	int tmp=0;while(x)tmp+=V[x],x-=lowbit(x);return tmp;
}
int dis(int x,int y){return dep[x]+dep[y]-2*dep[Lca(x,y)];}

void dfs(int u){
	dep[u]=dep[fa[u][0]]+1;
	for(int i=1;i<17;i++)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int v:g[u])
		if(v!=fa[u][0]) fa[v][0]=u,dfs(v);
}

void count(int &s,int u,int f){
	s++;
	for(int v:g[u])
		if(v!=f&&!vis[v]) count(s,v,u);
}

void find_rt(int &rt,int &Min,int u,int f,const int &s){
	sz[u]=1; int tmp=0;
	for(int v:g[u])
		if(v!=f&&!vis[v]){
			find_rt(rt,Min,v,u,s);
			sz[u]+=sz[v],tmp=max(sz[v],tmp);
		}
	tmp=max(s-sz[u],tmp);
	if(tmp<Min) Min=tmp,rt=u;
}

void Dfs(int u,int f){
	int s=0,Min,rt;
	count(s,u,u),Min=s,rt=u;
	find_rt(rt,Min,u,u,s),vis[rt]=1;
	C[rt][0].resize(sz[u]+2);
	C[rt][1].resize(sz[u]+2);
	for(int i=0;i<17;i++){
		Fa[rt][i]=i? Fa[f][i-1]:f;
		if(!Fa[rt][i]) break;
		Dis[rt][i]=dis(rt,Fa[rt][i]);
		add(C[Fa[rt][i]][0],Dis[rt][i],v[rt]);
		add(C[i? Fa[rt][i-1]:rt][1],Dis[rt][i],v[rt]);
	}
	for(int v:g[rt])
		if(!vis[v]&&v!=f) Dfs(v,rt);
}

int main(){
//	freopen("P6329_1.in","r",stdin);
//	freopen("mine.txt","w",stdout);
	int n=read(),m=read(),ans=0;
	for(int i=1;i<=n;i++) v[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1);
	Dfs(1,0);
//	for(int i=1;i<=n;i++)
//		printf("Fa[%d]=%d\n",i,Fa[i][0]);
	while(m--){
		int op=read();
		int x=read()^ans,y=read()^ans;
	//	int x=read(),y=read();
		if(!op){
			int p=0;
			ans=query(C[x][0],y)+v[x];
			while(Fa[x][p]){
				if(y>Dis[x][p])
					ans+=query(C[Fa[x][p]][0],y-Dis[x][p])
						-query(C[p? Fa[x][p-1]:x][1],y-Dis[x][p]);
				if(y>=Dis[x][p]) ans+=v[Fa[x][p]];
				p++;
			}
			printf("%d\n",ans);
		}else{
			int p=0;
			while(Fa[x][p]){
				add(C[Fa[x][p]][0],Dis[x][p],y-v[x]);
				add(C[p? Fa[x][p-1]:x][1],Dis[x][p],y-v[x]);
				p++;
			}
			v[x]=y;
		}
	}
}
