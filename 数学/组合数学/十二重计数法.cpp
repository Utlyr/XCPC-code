#include"header.h"
const int MAXN = 1e5+10;
const int p = 998244353;
int ksm(int a,int b)
{
    int ans=1;
    while(b>0)
    {
        if(b&1)ans=ans*a%p;
        a=a*a%p;
        b>>=1;
    }
    return ans;
}
int a[MAXN],inv[MAXN];//阶乘与逆元
int c(int n,int m)//组合数
{
    if(m<0 || m>n)return 0;
    return a[n]*inv[m]%p*inv[n-m];
}
//有n个球和m个盒子，要全部装进盒子里。还有一些限制条件，那么有多少种方法放球？

//1.球之间互不相同，盒子之间也互不相同。
int count1(int n,int m)
{
    return ksm(m,n);
}

//2.球之间互不相同，盒子之间互不相同，每个盒子至多装一个球。
int count2(int n,int m)
{
    if(n>m)return 0;
    return c(m,n)*a[n]%p;
}

//3.球之间互不相同，盒子之间互不相同，每个盒子至少装一个球。(对有几个空盒进行容斥)
int count3(int n,int m)
{
    if(m>n)return 0;
    int ans=0,f=1;
    for(int i=0;i<=m;i++)
    {
        ans=(ans+f*c(m,i)*ksm(i,n))%p;
        f*=-1;
    }
    return ans;
}

//4.球之间互不相同，盒子全部相同。(第二类斯特林数（行）)
int count4(int n,int m)
{

}