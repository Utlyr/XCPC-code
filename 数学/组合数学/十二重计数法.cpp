#include"header.h"
#include"C:\Users\34065\Desktop\mygit\XCPC-code\数学\多项式与生成函数\多项式模板.cpp"

int ksm(int a,int b,int p)
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
void init(int n)
{
    a[0]=1;
    for(int i=1;i<=4e5;i++)a[i]=a[i-1]*i%mod;
    inv[0]=1,inv[(int)4e5]=ksm(a[(int)4e5],mod-2,mod);
    for(int i=4e5-1;i>=1;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int c(int n,int m)//组合数
{
    if(m<0 || m>n)return 0;
    return a[n]*inv[m]%mod*inv[n-m]%mod;
}
//有n个球和m个盒子，要全部装进盒子里。还有一些限制条件，那么有多少种方法放球？

//1.球之间互不相同，盒子之间也互不相同。
int count1(int n,int m)
{
    return ksm(m,n,mod);
}

//2.球之间互不相同，盒子之间互不相同，每个盒子至多装一个球。
int count2(int n,int m)
{
    if(n>m)return 0;
    return c(m,n)*a[n]%mod;
}

//3.球之间互不相同，盒子之间互不相同，每个盒子至少装一个球。(对有几个空盒进行容斥)
int count3(int n,int m)
{
    if(m>n)return 0;
    int ans=0,f=1;
    for(int i=0;i<=m;i++)
    {
        
        if((m-i)%2==1)ans=(ans+(mod-c(m,i)*ksm(i,n,mod)%mod)%mod)%mod;
        else ans=(ans+(c(m,i)*ksm(i,n,mod)%mod)%mod+mod)%mod;
    }
    return ans;
}


//4.球之间互不相同，盒子全部相同。（第二类斯特林数行的和）
int count4(int n,int m)
{
    int limit=getl((n+1)<<1);
    vector<int> f1(limit),g1(limit);
    int sign=1;
    for(int i=0;i<=n;i++)
    {
        f1[i]=(sign*inv[i]+mod)%mod;
        g1[i]=ksm(i,n,mod)*inv[i]%mod;
        sign*=-1;
    }
    NTT(f1,limit,1);NTT(g1,limit,1);
    for(int i=0;i<limit;i++)f1[i]=f1[i]*g1[i]%mod;
    NTT(f1,limit,0);
    int ans=0;
    for(int i=0;i<=min(m,n);i++)ans=(ans+f1[i])%mod;
    return ans;
}

//5.球之间互不相同，盒子全部相同，每个盒子最多装一个。
int count5(int n,int m)
{
    if(n<=m)return 1;
    else return 0;
}

//6.球之间互不相同，盒子全部相同，每个盒子最少装一个。
int count6(int n,int m)
{
    if(m>n)return 0;
    int ans=0,f=1;
    for(int i=0;i<=m;i++)
    {
        if((m-i)%2==1)ans=(ans+(mod-inv[m-i]*inv[i]%mod)*ksm(i,n,mod)%mod+mod)%mod;
        else ans=(ans+inv[m-i]*inv[i]%mod*ksm(i,n,mod)%mod+mod)%mod;
    }
    return ans;
}

//7.球相同，盒子不同
int count7(int n,int m)
{
    return c(n+m-1,m-1);
}

//8.球全部相同，盒子之间互不相同，每个盒子至多装一个球。
int count8(int n,int m)
{
    if(n>m)return 0;
    return c(m,n);
}

//9.球全部相同，盒子之间互不相同，每个盒子至少装一个球。
int count9(int n,int m)
{
    if(m>n)return 0;
    return c(n-1,m-1);
}
vector<int> f1(MAXN),g1(MAXN);
//10.球全部相同，盒子全部相同
int count10(int n,int m)
{
    int limit=getl(n+1);
    for(int i=1;i<=m;i++)
    {
        for(int j=i;j<=n;j+=i)
        {
            f1[j]+=ksm(j/i,mod-2);
        }
    }
    polyexp(f1,g1,limit);
    int t=g1[n];
    for(int i=0;i<limit;i++)f1[i]=g1[i]=0;
    return t;
}

//11.球全部相同，盒子全部相同，每个盒子至多装一个球。
int count11(int n,int m)
{
    if(m<n)return 0;
    return 1;
}

//12.球全部相同，盒子全部相同，每个盒子至少装一个球。
int count12(int n,int m)
{
    if(m>n)return 0;
    return count10(n-m,m);
}