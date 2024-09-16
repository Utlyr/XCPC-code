#include"header.h"
//线性时间筛出素数
namespace Euler
{
    const int MAXN = 1e6+10;
    bool isprime[MAXN];
    int prime[MAXN];
    int n;//上限
    int cnt;//素数个数
    void euler(void)
    {
        memset(isprime,true,sizeof(isprime));
        isprime[1]=false;
        for(int i=2;i<=n;i++)
        {
            if(isprime[i])prime[++cnt]=i;
            for(int j=1;j<=cnt && i*prime[j]<=n;j++)
            {
                isprime[i*prime[j]]=false;
                if(i%prime[j]==0)break;
            }
        }
    }
}