/*
* @author Nickel_Angel (1239004072@qq.com)
* @copyright Copyright (c)
*/

#include <cstdio>
#include <iostream>

struct Matrix
{
    int v[110][110], n;

    Matrix()
    {
        memset(v, 0, sizeof(v));
    }

    Matrix operator * (const Matrix& rhs) const
    {
        Matrix res;
        res.n = n;
        for (int i = 1; i <= n; ++i)
        {
            for (int k = 1; k <= n; ++k)
            {
                for (int j = 1; j <= n; ++j)
                {
                    res.v[i][j] += v[i][k] * rhs.v[k][j];
                }
            }
        }
        return res;
    }

    void print()
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                printf("%d ", v[i][j]);
            }
            puts("");
        }
    }
};

int n, m;
Matrix A, B;

int main()
{
    scanf_s("%d%d", &n, &m);
    memset(A.v, 0, sizeof(A.v));
    memset(B.v, 0, sizeof(B.v));
    A.n = n;
    for (int i = 0, u, v; i < m; ++i)
    {
        scanf_s("%d%d", &u, &v);
        A.v[u][v] = 1;
    }
    B = A;
    for (int i = 1; i <= n; ++i)
    {
        B = A * B;
        printf("%d\n", i + 1);
        B.print();
    }
    return 0;
}
