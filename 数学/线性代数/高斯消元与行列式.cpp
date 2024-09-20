#include"header.h"
#include<矩阵与向量.cpp>
//利用增广矩阵进行高斯消元（可以直接输入）
//高斯消元可以用于求行列式的值，转化为对角线即可

const double esp = 1e-9;//处理精度问题

matrix operator+(matrix a,vector<int> b)//得到增广矩阵
{
    matrix res(a.n,a.m+1);
    for(int i=1;i<=a.n;i++)
    {
        for(int j=1;j<=res.m;j++)
        {
            if(j==res.m)
            {
                res.a[i][j]=b[i];
            }
            else res.a[i][j]=a.a[i][j];
        }
    }
    return res;
}

matrix Gauss(matrix a)
{
    int n=a.n,m=a.m-1;
    for(int i=1;i<=m;i++)
    {
        int tmp=-1;
        for(int j=1;j<=n;j++)
        {
            if(abs(a.a[j][i])>=esp)//不为0
            {
                int f=1;
                for(int k=1;k<=j-1;k++)
                {
                    if(abs(a.a[k][i])>=esp)
                    {
                        f=0;
                        break;
                    }
                }
                if(f)tmp=j;
                break;
            }
        }
        if(tmp==-1)continue;
        for(int j=1;j<tmp;j++)
        {
            if(abs(a.a[j][i])<esp)continue;
            a.a[j]=a.a[j]-a.a[tmp]*(a.a[j][i]/a.a[tmp][i]);
        }
        for(int j=tmp+1;j<=n;j++)
        {
            if(abs(a.a[j][i])<esp)continue;
            a.a[j]=a.a[j]-a.a[tmp]*(a.a[j][i]/a.a[tmp][i]);
        }
    }
    return a;
}