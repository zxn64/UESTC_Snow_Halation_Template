#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;
typedef double db;

const int N = 2e5 + 7;
const ll M = 1e10;
const int Mod = 1e9 + 7;

ll Lim, lim;
ll lis[N];
int mp[N][2], cnt = 0, lpf[N], pcnt = 0, pri[N];

ll G[N][2], Fprime[N];

ll qpow(ll x, ll y)
{
    ll ret = 1;
    while (y)
    {
        if (y & 1)
            ret = ret * x % Mod;
        x = x * x % Mod, y >>= 1;
    }
    return ret;
}

inline const int Id(const ll &x)
{
    return x <= lim ? mp[x][0] : mp[Lim / x][1];
}

inline const ll f(const ll &x)
{
    return x % Mod * ((x - 1ll) % Mod) % Mod;
}

const ll inv2 = qpow(2ll, Mod - 2);
const ll inv6 = qpow(6ll, Mod - 2);

ll F(const ll n, const int k)
{
    if (n < pri[k] || n <= 1)
        return 0;
    ll ans = (Fprime[Id(n)] - Fprime[Id(pri[k - 1])] + Mod) % Mod;
    for (int i = k; i <= pcnt && 1ll * pri[i] * pri[i] <= n; i++)
        for (ll pw = pri[i]; pw <= n / pri[i]; pw *= pri[i])
            ans = (ans + f(pw) * F(n / pw, i + 1) % Mod + f(pw * pri[i])) % Mod;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while(T--)
    {
        cin >> Lim;
        pri[0] = 1;
        lim = sqrtl(Lim);
        cnt = pcnt = 0;
        for (int i = 2; i <= lim; i++)
            lpf[i] = 0;
        for (int i = 2; i <= lim; i++)
        {
            if (!lpf[i])
            {
                lpf[i] = ++pcnt;
                pri[pcnt] = i;
            }
            for (int j = 1; j <= lpf[i] && 1ll * i * pri[j] <= lim; j++)
                lpf[i * pri[j]] = j;
        }
        for (ll l = 1, r = 0, v; l <= Lim; l = r + 1)
        {
            r = Lim / (Lim / l);
            lis[++cnt] = v = Lim / l;
            (v <= lim ? mp[v][0] : mp[Lim / v][1]) = cnt;
            G[cnt][0] = (v + 2ll) % Mod * ((v - 1ll) % Mod) % Mod * inv2 % Mod;
            G[cnt][1] = v % Mod * ((v + 1) % Mod) % Mod * ((2ll * v + 1ll) % Mod) % Mod * inv6 % Mod;
            G[cnt][1] = (G[cnt][1] + Mod - 1ll) % Mod;
        }
        ll v;
        for (int k = 1; k <= pcnt; k++)
        {
            const ll pw = (ll)pri[k] * pri[k];
            for (int i = 1; pw <= lis[i]; i++)
            {
                const int id1 = Id(lis[i] / pri[k]);
                const int id2 = Id(pri[k - 1]);
                G[i][0] = (G[i][0] - pri[k] * ((G[id1][0] - G[id2][0] + Mod) % Mod) % Mod + Mod) % Mod;
                G[i][1] = (G[i][1] - 1ll * pri[k] * pri[k] % Mod * ((G[id1][1] - G[id2][1] + Mod) % Mod) % Mod + Mod) % Mod;
            }
        }
        for (int i = 1; i <= cnt; i++)
            Fprime[i] = (G[i][1] - G[i][0] + Mod) % Mod;
        cout << (F(Lim, 1) + 1ll) % Mod << "\n";
    }
}