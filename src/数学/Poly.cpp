#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long ll;

const int N = 1 << 22;
const int M = 3e6 + 7;
const int Mod = 998244353;

int rk[N];

inline ll ModRead()
{
    ll x = 0, flag = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            flag = 0;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = ((x << 1) + (x << 3) + c - 48) % Mod;
        c = getchar();
    }
    return flag ? x : -x;
}

ll qpow(ll x, ll y = Mod - 2)
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

const ll G = 3ll;
const ll Gi = qpow(3ll);
const ll inv2 = qpow(2ll);

void NTT(const bool &op, const int &n, vector<ll> &F)
{
    for (int i = 0; i < n; i++)
        if (i < rk[i])
            swap(F[i], F[rk[i]]);
    for (int p = 2; p <= n; p <<= 1)
    {
        int len = p >> 1;
        ll w = qpow(op ? G : Gi, (Mod - 1) / p);
        for (int k = 0; k < n; k += p)
        {
            ll now = 1;
            for (int l = k; l < k + len; l++)
            {
                ll t = F[l + len] * now % Mod;
                F[l + len] = (F[l] - t + Mod) % Mod;
                F[l] = (F[l] + t) % Mod;
                now = now * w % Mod;
            }
        }
    }
}

inline void Rk(const int &n)
{
    for (int i = 0; i < n; i++)
        rk[i] = (rk[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
}

void print(const vector<ll> &X)
{
    for (const ll &v : X)
        cout << v << " ";
    cout << "!!!\n";
}

void Mul(vector<ll> &X, vector<ll> &a, vector<ll> &b)
{
    static vector<ll> x, y;
    int n = a.size() - 1, m = b.size() - 1;
    x = a, y = b;
    for (m += n, n = 1; n <= m; n <<= 1)
        ;
    Rk(n);
    x.resize(n), y.resize(n);
    NTT(1, n, x), NTT(1, n, y);
    for (int i = 0; i < n; i++)
        x[i] = x[i] * y[i] % Mod;
    NTT(0, n, x);
    ll inv = qpow(n);
    X.resize(m + 1);
    for (int i = 0; i <= m; i++)
        X[i] = x[i] * inv % Mod;
}

void Inv(int n, vector<ll> &a, vector<ll> &b)
{
    static vector<ll> x;
    if (n == 1)
    {
        b.resize(1);
        b[0] = qpow(a[0]);
        return;
    }
    Inv((n + 1) >> 1, a, b);
    const int m = n;
    for (n = 1; n < (m << 1); n <<= 1)
        ;
    Rk(n);
    x = a;
    x.resize(n), b.resize(n);
    for (int i = m; i < n; i++)
        x[i] = 0;
    NTT(1, n, x), NTT(1, n, b);
    for (int i = 0; i < n; i++)
        b[i] = b[i] * (2ll - x[i] * b[i] % Mod + Mod) % Mod;
    NTT(0, n, b);
    ll inv = qpow(n);
    b.resize(m);
    for (int i = 0; i < m; i++)
        b[i] = b[i] * inv % Mod;
}

void Ln(vector<ll> &a, vector<ll> &b)
{
    static vector<ll> x;
    const int n = a.size();
    Inv(n, a, x);
    b.resize(n);
    for (int i = 0; i < n - 1; i++)
        b[i] = a[i + 1] * (i + 1) % Mod;
    b[n - 1] = 0;
    Mul(x, b, x);
    for (int i = 1; i < n; i++)
        b[i] = x[i - 1] * qpow(i) % Mod;
    b[0] = 0;
}

void Exp(int n, vector<ll> &a, vector<ll> &b)
{
    static vector<ll> x, y;
    if (n == 1)
    {
        b.resize(1);
        b[0] = 1;
        return;
    }
    Exp((n + 1) >> 1, a, b);
    int m = n;
    for (n = 1; n < (m << 1); n <<= 1)
        ;
    y = a;
    y.resize(n);
    for (int i = m; i < n; i++)
        y[i] = 0;
    b.resize(m), Ln(b, x);
    b.resize(n), x.resize(n);
    NTT(1, n, x), NTT(1, n, y), NTT(1, n, b);
    for (int i = 0; i < n; i++)
        b[i] = (1ll - x[i] + y[i] + Mod) % Mod * b[i] % Mod;
    NTT(0, n, b);
    ll inv = qpow(n);
    b.resize(m);
    for (int i = 0; i < m; i++)
        b[i] = b[i] * inv % Mod;
}

void Sqrt(int n, vector<ll> &a, vector<ll> &b)
{
    static vector<ll> x, y;
    if (n == 1)
    {
        b.resize(1);
        b[0] = 1;
        return;
    }
    Sqrt((n + 1) >> 1, a, b);
    int m = n;
    for (n = 1; n < (m << 1); n <<= 1)
        ;
    b.resize(m), Inv(m, b, x);
    y = a, y.resize(m);
    Mul(y, x, y);
    for (int i = 0; i < m; i++)
        b[i] = (b[i] + y[i]) % Mod * inv2 % Mod;
}

void Kpow(vector<ll> &a, const ll &k)
{
    static vector<ll> x;
    const int n = a.size();
    Ln(a, x);
    x.resize(n + 1);
    for (int i = 0; i <= n; i++)
        x[i] = x[i] * k % Mod;
    Exp(n + 1, x, a);
}