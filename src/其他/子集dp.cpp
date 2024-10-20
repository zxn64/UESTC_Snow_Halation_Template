for(int i=u; i; i=(i-1)&u) f[u] += f[i];   // 枚举子集


// 高维前缀和:
for(int k=0;k<=19;k++)
        for(int i=0;i<=maxn;i++)
            if((i>>k)&1) g[i] += g[i^(1<<k)];   // i 是超集，有第 k 位

// 高维后缀和：
for(int k=0;k<=19;k++)
        for(int i=0;i<=maxn;i++)
            if(!((i>>k)&1)) g[i] += g[i^(1<<k)];   // i 是子集，无第 k 位

// 前缀差分：
for(int k=0;k<=19;k++)
        for(int i=0;i<=maxn;i++)
            if((i>>k)&1) f[i] -= f[i^(1<<k)];  // i 的前缀和减去 i 的子集，就是 i 本身。

// 后缀差分：
for(int k=0;k<=19;k++)
        for(int i=0;i<=maxn;i++)
            if(!((i>>k)&1)) f[i] -= f[i^(1<<k)];  // i 的后缀和减去 i 的超集，就是 i 本身。