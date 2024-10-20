const int N=1010101;
const int qwq=303030;
const int inf=0x3f3f3f3f;


int n,m;
struct E{
    int to,id;
};
vector <E> e[N];
int vis[N],cur[N];
int st[N],cnt;

void EULER(int u) {
    for(int i=cur[u];i<e[u].size();i=cur[u]) {
        cur[u]=i+1;
        int v = e[u][i].to, id = e[u][i].id;
        if(vis[id]) continue;
        vis[id] = 1;
        EULER(v);
        st[++cnt] = u;
    }
}

int main() {
    int x,y;
    n = read(); m = read();
    for(int i=1;i<=m;i++) {
        x = read(); y = read();
        e[x].push_back({y,i});
        e[y].push_back({x,i});
    }

    EULER(1);
    for(int i=cnt;i>=1;i--) cout<<st[i]<<" ";
    cout<<1<<"\n";
    return 0;
}


/*

7 8
1 2
2 3
3 4
4 5
5 1
3 6
6 7
7 3

*/