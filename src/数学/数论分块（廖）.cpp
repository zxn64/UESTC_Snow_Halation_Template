#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

ll G(ll n,ll k)
{
    ll res = n * k;
    for(ll l=1,r;l<=n;l=r+1)
    {
        if(k/l>0)r=min(n,k/(k/l));
        else r = n;
        res -= (l + r) * (r - l + 1) / 2ll * (k / l);
    }
    return res;
}
int main()
{
    ios::sync_with_stdio(false);
    ll x,y;
    cin>>x>>y;
    cout<<G(x,y)<<endl;
    return 0;
}