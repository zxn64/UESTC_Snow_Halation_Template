struct Node
{
    ModInt Sum, val, tag;
    int ls, rs, key;
    int l, r, L, R;
} t[N];

int NewNode(int l, int r, ModInt val)
{
    static int cnt = 0;
    t[++cnt] = (Node){0, val, 0, 0, 0, rand(), l, r, l, r};
    t[cnt].Sum = ModInt(r - l + 1) * t[cnt].val;
    return cnt;
}

void update(int id)
{
    t[id].L = t[id].ls ? t[t[id].ls].L : t[id].l;
    t[id].R = t[id].rs ? t[t[id].rs].R : t[id].r;
    t[id].Sum = t[t[id].ls].Sum + t[t[id].rs].Sum + t[id].val * ModInt(t[id].r - t[id].l + 1);
}

void add(int id, ModInt val)
{
    t[id].val += val;
    t[id].Sum += val * ModInt(t[id].R - t[id].L + 1);
    t[id].tag += val;
}

void pd(int id)
{
    if (!t[id].tag)
        return;
    if (t[id].ls)
        add(t[id].ls, t[id].tag);
    if (t[id].rs)
        add(t[id].rs, t[id].tag);
    t[id].tag = 0;
}

int merge(int x, int y)
{
    if (!x || !y)
        return x | y;
    if (t[x].key <= t[y].key)
    {
        pd(x);
        t[x].rs = merge(t[x].rs, y);
        return update(x), x;
    }
    else
    {
        pd(y);
        t[y].ls = merge(x, t[y].ls);
        return update(y), y;
    }
}

void split(int id, int k, bool op, int &x, int &y)
{
    if (!id)
        x = y = 0;
    else
    {
        pd(id);
        if ((!op && t[id].l <= k) || (op && t[id].r <= k))
            x = id, split(t[x].rs, k, op, t[x].rs, y);
        else
            y = id, split(t[y].ls, k, op, x, t[y].ls);
        update(id);
    }
}

int n, m, rt;

void Split(int l, int r, int &x, int &y, int &z)
{
    static int sta[N], tp = 0;
    x = y = z = tp = 0;
    split(rt, l - 1, 0, x, y);
    split(y, r, 1, y, z);
    int now = x;
    while (t[now].rs)
        sta[tp++] = now, now = t[now].rs;
    if (now && t[now].r > r)
    {
        y = NewNode(l, r, t[now].val);
        z = merge(NewNode(r + 1, t[now].r, t[now].val), z);
        t[now].r = l - 1;
        do
        {
            update(now);
        } while (tp && (now = sta[--tp]));
    }
    else
    {
        if (now && t[now].r >= l)
        {
            y = merge(NewNode(l, t[now].r, t[now].val), y);
            t[now].r = l - 1;
            do
            {
                update(now);
            } while (tp && (now = sta[--tp]));
        }
        now = z, tp = 0;
        while (t[now].ls)
            sta[tp++] = now, now = t[now].ls;
        if (now && t[now].l <= r)
        {
            y = merge(y, NewNode(t[now].l, r, t[now].val));
            t[now].l = r + 1;
            do
            {
                update(now);
            } while (tp && (now = sta[--tp]));
        }
    }
}