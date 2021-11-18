/*
* @author Nickel_Angel (1239004072@qq.com)
* @copyright Copyright (c) 2021
*/

#include <algorithm>
#include <cstdio>
#include <iostream>

const int maxn = 1e5 + 10;
const int maxm = 2e5 + 10;

int n, m, val[1010][1010], ans[maxn][3];

class union_find_set
{
private:
    int fa[maxn], height[maxn];

    int find(int x)
    {
        return fa[x] == x ? x : (fa[x] = find(fa[x]));
    }

public:
    inline void init(int n)
    {
        for (int i = 1; i <= n; ++i)
        {
            fa[i] = i;
            height[i] = 1;
        }
    }

    inline bool unite(int x, int y)
    {
        int fx = find(x), fy = find(y);
        if (fx == fy)
            return false;
        if (height[fx] == height[fy])
            ++height[fx];
        if (height[fx] < height[fy])
            std::swap(fx, fy);
        fa[fy] = fx;
        return true;
    }

    inline bool judge(int x, int y)
    {
        return find(x) == find(y);
    }
}S;

struct edge
{
    int from, to, val;
}e[maxm];

inline void kruskal()
{
    S.init(n);
    std::sort(e + 1, e + m + 1, [&](edge x, edge y) {return x.val < y.val; });
    int cnt = 0, res = 0;
    for (int i = 1; i <= m; ++i)
    {
        if (S.unite(e[i].from, e[i].to))
        {
            res += e[i].val;
            ++cnt;
            ans[cnt][0] = e[i].from, ans[cnt][1] = e[i].to, ans[cnt][2] = e[i].val;
            if (cnt == n - 1)
                break;
        }
    }
    if (cnt < n - 1)
    {
        puts("Invaild input!");
        return;
    }
    for (int i = 1; i <= cnt; ++i)
        printf("%d %d %d\n", ans[i][0], ans[i][1], ans[i][2]);
    printf("%d\n", res);
}

int main()
{
    int opt;
    scanf_s("%d%d", &opt, &n);
    if (opt == 1)
    {
        m = 0;
        for (int i = 1, x; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                scanf_s("%d", &x);
                if (x)
                {
                    e[++m].from = i;
                    e[m].to = j;
                    e[m].val = x;
                }
            }
        }
    }
    else if (opt == 2)
    {
        scanf_s("%d", &m);
        for (int i = 1; i <= m; ++i)
            scanf_s("%d%d%d", &e[i].from, &e[i].to, &e[i].val);
    }
    if (m < n - 1 || (opt != 1 && opt != 2))
    {
        puts("Invaild input!");
        return 0;
    }
    kruskal();
    return 0;
}
