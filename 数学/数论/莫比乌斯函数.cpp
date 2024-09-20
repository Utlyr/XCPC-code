#include"header.h"
//线性筛求莫比乌斯函数

const int MAXN = 1e6+10;
int mu[MAXN],p[MAXN],flg[MAXN];//莫比乌斯函数，素数序列，是否为素数
int tot=0;//素数个数

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