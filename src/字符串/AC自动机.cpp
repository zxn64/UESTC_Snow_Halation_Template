const int N=101010;
const int qwq=1003030;
const int inf=0x3f3f3f3f;

int n,m;
int cnt;
char s[qwq];
struct T{
    int to[26];
    int fail;
}f[qwq];
vector <int> e[qwq];
vector <int> g[qwq];
bool vis[qwq];
int ans;

void chushihua() {
    for(int i=0;i<=cnt;i++) e[i].clear(), g[i].clear(); //记得从零开始
    cnt = 0;
    memset( f,0,sizeof(f) );
}

inline void AC() {
    queue <int> q; q.push(0);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i=0;i<26;i++) {
            int v = f[u].to[i];
            if(v) {
                if(u) f[v].fail = f[ f[u].fail ].to[i];
                q.push(v);
            }
            else f[u].to[i] = f[ f[u].fail ].to[i];
        }
    }
    for(int i=1;i<=cnt;i++) e[ f[i].fail ].push_back(i);
    return ;
}

int main() {
    n = read();
    for(int k=1;k<=n;k++) {
        scanf("%s",s); int len = strlen(s);
        int u = 0;
        for(int i=0;i<len;i++) {
            int v = s[i]-'a';
            if(!f[u].to[v]) f[u].to[v] = ++cnt;
            u = f[u].to[v];
        }
        g[u].push_back(k);
    }
    AC();
    for(int i=1;i<=cnt;i++) cout<<"i = "<<i<<" fail = "
        <<f[i].fail<<" a = "<<f[i].to[0]<<" b = "<<f[i].to[1]<<"\n";


    return 0;
}
