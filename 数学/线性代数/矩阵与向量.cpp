#include"header.h"
const int MAXN = 101;
#define T double
//向量直接vector表示

struct matrix//下标从1开始
{
    int n=101,m=101;//默认为100x100矩阵
    matrix(int x,int y)
    {
        n=x;m=y;
    }
    vector<vector<T>> a;
    void init(void)
    {
        for(int i=0;i<=n;i++)a.push_back(vector<T>(m+1));
    }
};
matrix operator+(matrix a,matrix b)
{
    int n=a.n,m=a.m;
    matrix res(n,m);
    res.init();
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)res.a[i][j]=a.a[i][j]+b.a[i][j];
    }
    return res;
}
matrix operator-(matrix a,matrix b)
{
    int n=a.n,m=a.m;
    matrix res(n,m);
    res.init();
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)res.a[i][j]=a.a[i][j]-b.a[i][j];
    }
    return res;
}
matrix operator*(matrix a,matrix b)
{
    int n1=a.n,m1=a.m,n2=b.n,m2=b.m;
    matrix res(n1,m2);
    res.init();
    for(int i=1;i<=n1;i++)
    {
        for(int j=1;j<=m2;j++)
        {
            for(int k=1;k<=m1;k++)res.a[i][j]+=a.a[i][k]*b.a[k][j];
        }
    }
    return res;
}
vector<T> operator*(vector<T> a,T k)//向量数乘
{
    vector<T> res(a.size());
    for(int i=0;i<a.size();i++)res[i]=a[i]*k;
    return res;
}
vector<T> operator-(vector<T> a,vector<T> b)//向量减法
{
    vector<T> res(a.size());
    for(int i=0;i<a.size();i++)res[i]=a[i]-b[i];
    return res;
}
vector<T> operator+(vector<T> a,vector<T> b)//向量减法
{
    vector<T> res(a.size());
    for(int i=0;i<a.size();i++)res[i]=a[i]+b[i];
    return res;
}
void show(matrix a)
{
    for(int i=1;i<=a.n;i++)
    {
        for(int j=1;j<=a.m;j++)
        {
            cout<<a.a[i][j]<<" ";
        }
        cout<<"\n";
    }
}