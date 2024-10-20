const int p=998244353;

int n,m;
int du[345];
int a[345][345];


int ksm(int aa,int bb) {
    int sum = 1;
    while(bb) {
        if(bb&1) sum = sum * aa %p;
        bb >>= 1; aa = aa * aa %p;
    }
    return sum;
}

int det() {
    int res = 1, cl = 1;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j] = (a[i][j] + p) %p;
    for(int i=1;i<=n;i++) {
        if(!a[i][i])
            for(int j=i+1;j<=n;j++)
                if(a[j][i]) { cl ^= 1; for(int k=i;k<=n;k++) swap(a[j][k],a[i][k]); break; }
        if(!a[i][i]) return 0;
        (res *= a[i][i]) %= p;
        int ni = ksm(a[i][i],p-2); for(int j=i;j<=n;j++) (a[i][j] *= ni) %= p;
        for(int j=1;j<=n;j++) {
            if(i!=j) {
                int bei = a[j][i];
                for(int k=i;k<=n;k++)
                    a[j][k] = (a[j][k] - a[i][k] * bei %p +p) %p;
            }
        }
    }
    return cl ? res : -res;
}

int main() {
    int x,y;
    n = read(); m = read();
    for(int i=1;i<=m;i++) {
        x = read(); y = read();
        du[x]++; du[y]++;
        a[x][y]--; a[y][x]--;
    }
    for(int i=1;i<=n;i++) a[i][i] = du[i];
    // for(int i=1;i<=n;i++) {
    //     for(int j=1;j<=n;j++) cout<<a[i][j]<<" ";
    //         cout<<endl;
    // }

    // 无向图：   L(n) = D(n) - A(n);
    // 有向图根向：L(n) = D_out(n) - A(n);   //k为根去掉第k行
    // 有向图叶向：L(n) = D_in(n) - A(n);
    n--;  //去一行
    cout<<det();
    return 0;
}