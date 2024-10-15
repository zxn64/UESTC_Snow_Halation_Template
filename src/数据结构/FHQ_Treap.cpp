#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

const int N = 5e5 + 7;

struct FHQ_TREAP
{
    struct Node
    {
        int ls, rs, key, sz, val;
        Node(int l_ = 0, int r_ = 0, int key_ = 0, int sz_ = 0, int val_ = 0)
            : ls(l_), rs(r_), key(key_), sz(sz_), val(val_)
        {
            if (!key)
                key = rand() + 1;
        }
    };

    vector<Node> t;
    stack<int> pool;
    int nd_cnt, rt, x, y, z;

    FHQ_TREAP()
    {
        srand(114514);
        t.push_back(Node());
        rt = nd_cnt = 0;
    }

    int node(int x)
    {
        Node tmp(0, 0, 0, 1, x);
        if (!pool.empty())
        {
            int id = pool.top();
            pool.pop();
            t[id] = tmp;
            return id;
        }
        else
        {
            t.push_back(tmp);
            return ++nd_cnt;
        }
    }

    void update(int id)
    {
        t[id].sz = 1 + t[t[id].ls].sz + t[t[id].rs].sz;
    }

    int merge(int x, int y)
    {
        if (!x || !y)
            return x + y;
        if (t[x].key < t[y].key)
        {
            t[x].rs = merge(t[x].rs, y);
            update(x);
            return x;
        }
        else
        {
            t[y].ls = merge(x, t[y].ls);
            update(y);
            return y;
        }
    }

    void split(int id, int k, int &x, int &y)
    {
        if (!id)
            x = y = 0;
        else
        {
            if (t[id].val <= k)
                x = id, split(t[id].rs, k, t[id].rs, y);
            else
                y = id, split(t[id].ls, k, x, t[id].ls);
            update(id);
        }
    }

    void Insert(int val)
    {
        z = node(val);
        split(rt, val - 1, x, y);
        rt = merge(x, merge(z, y));
    }

    void Delete(int val)
    {
        split(rt, val - 1, x, y);
        split(y, val, y, z);
        pool.push(y);
        y = merge(t[y].ls, t[y].rs);
        rt = merge(merge(x, y), z);
    }

    int get_rank(int val)
    {
        split(rt, val - 1, x, y);
        int tmp = t[x].sz + 1;
        rt = merge(x, y);
        return tmp;
    }

    int get_kth(int rk)
    {
        int id = rt;
        while (1)
        {
            if (rk <= t[t[id].ls].sz)
                id = t[id].ls;
            else if (rk == t[t[id].ls].sz + 1)
                return t[id].val;
            else
            {
                rk -= (t[t[id].ls].sz + 1);
                id = t[id].rs;
            }
        }
    }

    int get_pre(int val)
    {
        split(rt, val - 1, x, y);
        int id = x;
        while (t[id].rs)
            id = t[id].rs;
        rt = merge(x, y);
        return t[id].val;
    }

    int get_suc(int val)
    {
        split(rt, val, x, y);
        int id = y;
        while (t[id].ls)
            id = t[id].ls;
        rt = merge(x, y);
        return t[id].val;
    }

} T;