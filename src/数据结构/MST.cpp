struct MST
{
    const int N = 5e4 + 7;
    int fa[N], rk[N];
    MST(int n)
    {
        for (int i = 1; i <= n; i++)
            fa[i] = i, rk[i] = 1;
    }
    int find(int x)
    {
        if (fa[x] == x)
            return x;
        return fa[x] = find(fa[x]);
    }
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y)
            return;
        if (rk[x] < rk[y])
            swap(x, y);
        rk[x] = max(rk[x], rk[y] + 1);
        fa[y] = x;
    }
} T;