const int N=2020200;
const int qwq=303030;
const int inf=0x3f3f3f3f;

int n,Q;
int a[N];
int ob[N],ma[N][22];


int ask(int l,int r) {
    int k = ob[r-l+1];
    return max(ma[l][k], ma[r-(1<<k)+1][k]);
}

void built() {
    ob[0] = -1; for (int i=1;i<=N-10;i++) ob[i] = ob[i>>1] + 1;
    for (int k=1;k<=21;k++)
        for (int i=1;i+(1<<(k-1))<=n;i++)
            ma[i][k] = max(ma[i][k-1], ma[i+(1<<(k-1))][k-1]);
}

int main() {
    int x,y;
    n = read(); Q = read();
    for(int i=1;i<=n;i++) a[i] = read(), ma[i][0] = a[i];
    built();
    while(Q--) {
        x = read(); y = read();
        cout<<ask(x,y)<<"\n";
    }
    return 0;
}