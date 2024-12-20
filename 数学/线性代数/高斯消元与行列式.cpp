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
                for(int k=1;k<=i-1;k++)
                {
                    if(abs(a.a[j][k])>=esp)
                    {
                        f=0;
                        break;
                    }
                }
                if(f){tmp=j;break;}
                else continue;
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

int ksm(int a,int b,int p)
{
    int ans=1;
    while(b)
    {
        if(b&1)ans=ans*a%p;
        b>>=1;
        a=a*a%p;
    }
    return ans;
}
matrix GaussMod(matrix a,int p)//模意义下进行高斯消元(对方阵进行)
{
    int n=a.n,m=a.m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)a.a[i][j]=(a.a[i][j]%p+p)%p;
    }
    for(int i=1;i<=m;i++)
    {
        int tmp=-1;
        for(int j=1;j<=n;j++)
        {
            if(abs(a.a[j][i])!=0)//不为0
            {
                int f=1;
                for(int k=1;k<=i-1;k++)
                {
                    if(abs(a.a[j][k]) != 0)
                    {
                        f=0;
                        break;
                    }
                }
                if(f){tmp=j;break;}
                else continue;
            }
        }
        if(tmp==-1)continue;
        for(int j=1;j<tmp;j++)
        {
            if(abs(a.a[j][i])==0)continue;
            a.a[j]=a.a[j]-a.a[tmp]*(a.a[j][i]*ksm(a.a[tmp][i],p-2,p));
            for(int k=1;k<=m;k++)
            {
                a.a[j][k]=(a.a[j][k]%p+p)%p;
            }
        }
        for(int j=tmp+1;j<=n;j++)
        {
            if(abs(a.a[j][i])==0)continue;
            a.a[j]=a.a[j]-a.a[tmp]*(a.a[j][i]*ksm(a.a[tmp][i],p-2,p));
            for(int k=1;k<=m;k++)
            {
                a.a[j][k]=(a.a[j][k]%p+p)%p;
            }
        }
    }
    return a;
}
int det(matrix a,int p)
{
    a = GaussMod(a,p);
    int ans=1;
    for(int i=1;i<=a.n;i++)
    {
        int tmp=0;
        for(int j=1;j<=a.m;j++)
        {
            tmp=max(tmp,a.a[i][j]);
        }
        ans=ans*tmp%p;
    }
    return ans;
}

int detSample(matrix a,int p)
{
    int n=a.n,ans=1,v=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            while(a.a[i][i])
            {
                int x=a.a[j][i]/a.a[i][i];
                for(int k=i;k<=n;k++)
                {
                    a.a[j][k]=(a.a[j][k]-x*a.a[i][k]%p+p)%p;
                }
                Swap(a.a[i],a.a[j]);v=-v;
            }
            Swap(a.a[i],a.a[j]);v=-v;
        }
    }
    for(int i=1;i<=n;i++)ans=ans*a.a[i][i]%p;
    return (ans*v+p)%p;
}