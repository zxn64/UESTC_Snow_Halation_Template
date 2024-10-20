using namespace std;
const ll N=505050;
const ll qwq=303030;
const ll inf=0x3f3f3f3f;

int n,Q;

struct PLB{

    int d[22], pos[22];

    void insert(int x,int wei) {
        for(int i=21;i>=0;i--) {
            if(!((x>>i)&1)) continue;
            if(!d[i]) {
                d[i] = x;
                pos[i] = wei;
                return ;
            }
            if(pos[i]<wei) {
                swap(pos[i],wei);
                swap(d[i],x);
            }
            x ^= d[i];
        }
    }

    int query_max(int l) {
        int ans = 0;
        for(int i=21;i>=0;i--)
            if(d[i] && pos[i]>=l)
                ans = max(ans,ans^d[i]);
        return ans;
    }

    bool query(int k,int l) {
        for(int i=21;i>=0;i--) {
            if(!(k>>i)) continue;
            if(!d[i] || pos[i]<l) return 0;
            k ^= d[i];
        }
        return 1;
    }

}B[N];


int main() {
    int l,r;
    n = read();
    for(int i=1;i<=n;i++) {
        B[i] = B[i-1];
        B[i].insert(read(),i);
    }
    Q = read();
    while(Q--) {
        l = read(); r = read();
        cout<<B[r].query(l)<<"\n";
    }
    return 0;
}
