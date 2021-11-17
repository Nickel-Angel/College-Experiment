/*
* @author Nickel_Angel (1239004072@qq.com)
* @copyright Copyright (c)
*/

#include <algorithm>
#include <cstdio>
#include <iostream>

const int maxn = 1e5 + 10;
const int maxm = 2e5 + 10;

int n, m;

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
            printf("%d %d %d\n", e[i].from, e[i].to, e[i].val);
            ++cnt;
            if (cnt == n - 1)
                break;
        }
    }
    printf("%d\n", res);
}

int main()
{
    scanf_s("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf_s("%d%d%d", &e[i].from, &e[i].to, &e[i].val);
    }
    kruskal();
    return 0;
}
