#include"header.h"
//给出ax+by=gcd(a,b)的一组解（这里用来求逆元,x是a的逆元）
//注意x可能为负数，x=(x+b)%b即可；
int exgcd(int a,int b,int &x,int &y)
{
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    int d=exgcd(b,a%b,x,y);
    int k=x;
    x=y;
    y=k-a/b*y;
    return d;
}

//求解一元线性同余方程组

const int MAXN = 2e5+10;
int a[MAXN],r[MAXN];//r为模数数组

int CRT(int k)//k为方程数目
{
    int n=1,ans=0;
    for(int i=1;i<=k;i++)n=n*r[i];
    for(int i=1;i<=k;i++)
    {
        int m=n/r[i],m1,x,y;
        exgcd(m,r[i],x,y);
        m1=(x+r[i])%r[i];//注意x才是结果
        ans+=m*m1*a[i];
        ans%=n;
    }
    return ans;
}


//扩展中国剩余定理（模数不互质的情况）
int excrt(int k)//k为方程数目
{
    int ma=a[1],mp=r[1];
    for(int i=2;i<=k;i++)
    {
        int x,y;
        if((ma-a[i])%__gcd(mp,r[i])!=0)return -1;
        exgcd(mp,r[i],x,y);
        if(x<0)x=(x+r[i])%r[i];
        x=x*(a[i]-ma)/__gcd(mp,r[i]);
    }
}