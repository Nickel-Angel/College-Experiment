/*
* @author Nickel_Angel (1239004072@qq.com)
* @copyright Copyright (c) 2021
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

int n, a[1010];

int main()
{
    scanf_s("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf_s("%d", a + i);
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i < n; ++i)
    {
        for (int j = i; j <= n; ++j)
            printf("%d%c", a[j], " \n"[j == n]);
        a[i + 1] += a[i];
        for (int j = i + 1; j < n; ++j)
        {
            if (a[j] > a[j + 1])
                std::swap(a[j], a[j + 1]);
            else
                break;
        }
    }
    printf("%d\n", a[n]);
    return 0;
}