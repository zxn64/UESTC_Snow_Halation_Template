#include <bits/stdc++.h>
#define ll long long
#define QWQ cout<<"QwQ\n";

using namespace std;
const ll N=1010101;
const ll inf=0x3f3f3f3f;
const ll p=998244353;

ll n;
char s[N];
ll a[N];
ll ha[N],fi[N],base = 2333;

ll ask(ll l,ll r) {
	return (ha[r] - ha[l-1] * fi[r-l+1] %p + p) %p;
}

inline ll lcp(ll x,ll y) {
	ll l=1, r=n-max(x,y)+1, res = 0;
	while(l<=r) {
		ll mid = (l+r) >> 1;
		if(ask(x,x+mid-1) == ask(y,y+mid-1)) l = mid+1, res = mid;
		else r = mid-1;
	}
	return res;
}

inline ll lcs(ll x,ll y) {
	ll l=1, r=min(x,y), res=0;
	while(l<=r) {
		ll mid = (l+r) >> 1;
		if(ask(x-mid+1,x) == ask(y-mid+1,y)) l = mid+1, res = mid;
		else r = mid-1;
	}
	return res;
}

bool cmp(ll l1,ll r1,ll l2,ll r2) {
	ll l = lcp(l1,l2);
	if(l>min(r1-l1,r2-l2)) return r1-l1<r2-l2;
	return a[l1+l]<a[l2+l];
}

struct runs{
	ll i,j,p;
	runs(ll i=0,ll j=0,ll p=0) : i(i), j(j), p(p) {}
	bool operator == (const runs A) const { return i==A.i && j==A.j && p==A.p; }
	bool operator < (const runs A) const { return i==A.i ? j<A.j : i<A.i; }
};
vector <runs> ans;
ll st[N],run[N];
void lyndon() {
	ll r = 0;
	for(ll i=n;i;i--) {
		st[++r] = i;
		for(;r>1 && cmp(i,st[r],st[r]+1,st[r-1]);r--);
		run[i] = st[r];
	}
}

void get_runs()
{
    for(int i=1;i<=n;i++) {
        int l1=i, r1=run[i], l2=l1-lcs(l1-1,r1), r2=r1+lcp(l1,r1+1);
        if(r2-l2+1>=(r1-l1+1)*2) ans.push_back(runs(l2,r2,r1-l1+1));
    }
}

int main() {
	fi[0] = 1;
	for(ll i=1;i<=N-10;i++) fi[i] = fi[i-1] * base %p;
	
	scanf("%s",s+1); n = strlen(s+1);
	for(ll i=1;i<=n;i++) a[i] = s[i]-'a'+1, ha[i] = (ha[i-1] * base %p + a[i]) %p;
	
	// int x,y;      // ask the lcp() and lcs();
	// while(1) {
	// 	cin>>x>>y;
	// 	cout<<lcp(x,y)<<" "<<lcs(x,y)<<"\n";
	// }

	lyndon();
	// for(int i=1;i<=n;i++) cout<<run[i]<<" ";
	get_runs();

	for(ll i=1;i<=n;i++) a[i] = 27-a[i];
	lyndon();
	get_runs();

	sort(ans.begin(), ans.end());
	ans.erase(unique(ans.begin(), ans.end()), ans.end());
	cout<<ans.size()<<"\n";
	for(runs vv : ans) cout<<vv.i<<" "<<vv.j<<" "<<vv.p<<endl;
	return 0;
}