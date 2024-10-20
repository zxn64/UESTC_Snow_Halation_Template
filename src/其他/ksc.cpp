IL int qmul(int x,int y,int mod)
{
    return (x*y-(long long)((long double)x/mod*y)*mod+mod)%mod;
}