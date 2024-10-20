#include <bits/stdc++.h>
#define ll long long
#define ls L[now]
#define rs R[now]

typedef double db;
using namespace std;
const ll N=101010;
const ll inf=0x3f3f3f3f3f3f3f3f;

ll n;
ll Q;
struct E{
	ll k,b; // kx + b
	ll id;
}d[N],t[N*64],ling;
ll L[N*64],R[N*64],tot,rt;
ll max_X = 1e9;

ll calc(E wo,ll x) { return wo.k*x + wo.b; }

void outing(E wo) {
	cout<<" k="<<wo.k<<" b="<<wo.b<<" id="<<wo.id<<"\n";
}

void insert(ll &now,ll l,ll r,E v) {
	if(!now) { now = ++tot; t[now] = ling; }
	ll mid = l+r >> 1, p1 = calc(t[now],mid), p2 = calc(v,mid);
	// cout<<"t : "; outing(t[now]);
	// cout<<"v : "; outing(v);
	// cout<<endl;
	if(p1<p2 || (p1==p2 && t[now].id>v.id)) swap(t[now], v);
	if(l==r) return ;
	if(t[now].k > v.k) insert(ls, l, mid, v);
	else               insert(rs, mid+1, r, v);
}

E query(ll &now,ll l,ll r,ll x) {
	if(!now) return ling;
	if(l==r) return t[now];
	ll mid = l+r >> 1;
	E res = t[now];
	if(x<=mid) res = query(ls, l, mid, x);
	else       res = query(rs, mid+1, r, x);
	ll ct = calc(t[now],x), cr = calc(res,x);
	if(ct>cr || (ct==cr && t[now].id<res.id)) return t[now];
	else                                      return res;
}

int main() {
	ll x;
	ling.b = -inf;
	n = read();
	for(ll i=1;i<=n;i++) {
		d[i].k = read(); d[i].b = read(); d[i].id = i;
		insert(rt, -max_X, max_X, d[i]);
	}
	Q = read();
	while(Q--) {
		x = read();
		E res = query(rt, -max_X, max_X, x);
		cout<<res.id<<" "<<calc(res,x)<<"\n";
	}
	return 0;
}