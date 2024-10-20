// by Flandre_495  --2023.06.29

const int N=1001010;
const int qwq=2003030;
const int inf=0x3f3f3f3f;

int n,cnt=1,lst=1;
char s[N];
int fa[qwq],ch[qwq][26],len[qwq],siz[qwq];
vector <int> e[qwq];

inline int insert(int c) {
    int u = lst, cur = ++cnt; len[cur] = len[u] + 1;
    for(; !ch[u][c] && u; u=fa[u]) ch[u][c] = cur;
    if(!u) fa[cur] = 1;
    else {
        int v = ch[u][c];
        if(len[v]==len[u]+1) fa[cur] = v;
        else {
            int w = ++cnt; len[w] = len[u] + 1;
            memcpy(ch[w],ch[v],sizeof ch[w]);
            fa[w] = fa[v]; fa[v] = fa[cur] = w;
            for(; ch[u][c]==v && u; u=fa[u]) ch[u][c] = w;
        }
    }
    return cur;
}

void DFS(int u) {
    FOR() {
        int v = e[u][i];
        DFS(v);
        siz[u] += siz[v];
    }
}

int main() {
    scanf("%s",s+1); n = strlen(s+1);
    for(int i=1;i<=n;i++) lst = insert(s[i]-'a'), siz[lst]=1;

    for(int i=2;i<=cnt;i++) e[ fa[i] ].push_back(i);
    DFS(1); 

    ll ans = 0;
    for(int i=2;i<=cnt;i++) if(siz[i]>1) ans = max( ans, (ll)siz[i]*len[i] );
    cout<<ans;
    return 0;
}

/*

aababaaba

*/
