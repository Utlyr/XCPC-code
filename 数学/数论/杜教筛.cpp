#include"header.h"

//杜教筛用于处理一类数论函数的前缀和

//求莫比乌斯函数前缀

const int MAXN = 2e6+10;

int mu[MAXN],p[MAXN],flg[MAXN];//莫比乌斯函数，素数序列，是否为素数
int tot=0;//素数个数
int con=2e6;

void getMu(int n)//得出n内的莫比乌斯函数
{
    mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!flg[i])p[++tot]=i,mu[i]=-1;
        for(int j=1;j<=tot&&i*p[j]<=n;j++)
        {
            flg[i*p[j]]=1;
            if(i%p[j]==0)
            {
                mu[i*p[j]]=0;
                break;
            }
            mu[i*p[j]]=-mu[i];
        }
    }
}
//考虑杜教筛求莫比乌斯函数前缀，欧拉函数前缀用迪利克雷卷积求得
map<int,int> pre_mu,pre_phi;//记录

int getsummu(int n)
{
    if(n<=con)return mu[n];
    if(pre_mu[n]!=0)return pre_mu[n];
    int sum=0,i=2;
    while(i<=n)
    {
        int j=n/(n/i);
        sum+=(j-i+1)*getsummu(n/i);
        i=j+1;
    }
    pre_mu[n]=1-sum;
    return 1-sum;
}

int getsumphi(int n)
{
    if(pre_phi[n]!=0)return pre_phi[n];
    int ans=0,i=1;
    while(i<=n)
    {
        int j=n/(n/i);
        ans+=(getsummu(j)-getsummu(i-1))*(n/i)*(n/i);
        i=j+1;
    }
    pre_phi[n]=(ans+1)/2;
    return (ans+1)/2;
}