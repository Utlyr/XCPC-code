#include "快速数论变换.cpp"
const int MAXN = 4e6+10;

//a为原始多项式数组，b为求逆后的结果
vector<int> a(MAXN),b(MAXN),F(MAXN);
void ployinvNTT(vector<int> &G,int n)//多项式求逆(mod x^n) ,最后G为结果数组 ,传入b
{
    if(n==1)
    {
        G[0]=ksm(a[0],mod-2);return;
    }
    ployinvNTT(G,n+1>>1);
    int limit=1,len=0;
    while(limit<(n<<1))
    {
        limit<<=1;++len;
    }

    //两种初始化方法
    for(int i=1;i<limit;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<len-1);
    //for(int i=0;i<limit;++i)rev[i]=(rev[i/2]/2+(i%2)*limit/2);
    for(int i=0;i<n;i++)F[i]=a[i];
    for(int i=n;i<limit;i++)F[i]=0;
    NTT(G,limit,1);NTT(F,limit,1);
    for(int i=0;i<limit;i++)
    {
        G[i]=(2-F[i]*G[i]%mod+mod)%mod*G[i]%mod;
    }
    NTT(G,limit,0);
    for(int i=n;i<limit;i++)G[i]=0;
}