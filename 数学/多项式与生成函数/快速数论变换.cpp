#include"header.h"

const int mod=998244353,g=3,ig=332748118;//模数，原根，ig是g的逆元
//一般多项式长度不超过8e6可以用上面的模数

int ksm(int a,int b)
{
    int ans=1;
    while(b>0)
    {
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}

int rev[2100000];
//mode=1为DFT，mode=0为逆变换
//注意所有运算要在模mod意义下进行
/*
****** for(int i=0;i<limit;++i)rev[i]=(rev[i/2]/2+(i%2)*limit/2);
       rev数组处理方法，limit为数组元素上限，是2的幂次
*/
void NTT(vector<int> &x,int n,int mode)
{
    for(int i=0;i<n;i++)if(i<rev[i])swap(x[i],x[rev[i]]);
    for(int len=1;len<n;len<<=1)
    {
        int Wn=ksm(mode?g:ig,(mod-1)/(2*len));
        for(int i=0;i<n;i+=2*len)
        {
            int W=1,X,Y;
            for(int j=i;j<i+len;j++)
            {
                X=x[j];Y=W*x[j+len]%mod;
                x[j]=(X+Y)%mod;x[j+len]=(X-Y+mod)%mod;
                W=(W*Wn)%mod;
            }
        }
    }
    if(!mode)
    {
        int invs=ksm(n,mod-2);
        for(int i=0;i<n;i++)x[i]=(x[i]*invs)%mod;
    }
}