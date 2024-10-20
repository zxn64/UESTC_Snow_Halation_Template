// by Flandre_495   ---2023.06.26

const int N=1001010;
const int qwq=303030;
const int inf=0x3f3f3f3f;

int n,m;
char s[N];
int sa[N],rk[N],tp[N],c[N],h[N];

inline void jipai() {
    for(int i=1;i<=n;i++) c[ rk[i] ]++;
    for(int i=1;i<=m;i++) c[i] += c[i-1];
    for(int i=n;i>=1;i--) sa[ c[rk[tp[i]]]-- ] = tp[i];
    for(int i=1;i<=m;i++) c[i] = 0;
} 

void SA() {
    m = 75;
    for(int i=1;i<=n;i++) rk[i] = s[i] - '0' + 1, tp[i] = i;
    jipai();
    for(int k=1; ;k<<=1) {
        int p = 0;
        for(int i=1;i<=k;i++) tp[++p] = n-k+i;
        for(int i=1;i<=n;i++) if(sa[i]>k) tp[++p] = sa[i]-k;
        jipai();
        swap(tp,rk); //多测改为for
        rk[sa[1]] = p = 1;
        for(int i=2;i<=n;i++)
            if(tp[sa[i-1]]==tp[sa[i]] && tp[sa[i-1]+k]==tp[sa[i]+k])
                rk[ sa[i] ] = p;
            else
                rk[ sa[i] ] = ++p;
        m = p;
        if(p==n) break;
    }
    int o;
    for(int i=1,l=0; i<=n; h[rk[i++]]=l)
        for(l=(l?l-1:0),o=sa[rk[i]-1]; s[i+l]==s[o+l]; ++l) ;
}

int main() {
    scanf("%s",s+1); n = strlen(s+1);
    SA();
    for(int i=1;i<=n;i++) cout<<rk[i]<<" ";
    return 0;
}

