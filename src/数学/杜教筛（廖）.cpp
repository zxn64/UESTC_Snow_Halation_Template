#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2123456;
ll prime[maxn],mu[maxn],sum[maxn],vis[maxn],cnt;
map<ll,ll> mp;
void init()
{
    mu[1] = 1;
    for(int i=2;i<maxn;++i){
        if(!vis[i])prime[++cnt] = i,mu[i] = -1;
        for(int j=1;j<=cnt&&i*prime[j]<maxn;++j){
            vis[i*prime[j]] = 1;
            if(i%prime[j]) mu[i*prime[j]] = - mu[i];
            else{
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
    for(int i=1;i<maxn;++i)sum[i] = sum[i-1] + mu[i];
}
ll S_mu(ll x)
{
    if(x < maxn) return sum[x];
    if(mp.find(x) != mp.end()) return mp[x];
    ll res = 1ll;
    for(ll l=2,r;l<=x;l=r+1){
        r = x/(x/l);
        res -= S_mu(x/l) * (r - l + 1);
    }
    return mp[x] = res;
}
ll S_phi(ll x)
{
    ll res = 0;
    for(ll l=1,r;l<=x;l=r+1){
        r = x/(x/l);
        res += (S_mu(r) - S_mu(l-1)) * (x / l) * (x / l);
    }
    return (res - 1) / 2 + 1;
}
int main()
{
    ios::sync_with_stdio(false);
    init();
    ll T,x;
    cin>>T;
    while(T--){
        cin>>x;
        cout<<S_phi(x)<<" "<<S_mu(x)<<'\n';
    }
    return 0;
}