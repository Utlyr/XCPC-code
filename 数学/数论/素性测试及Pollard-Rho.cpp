#include"header.h"

namespace MillerRabin{
    #define ull unsigned long long
    #define lb long double
    #define ll long long
    ll prime[10]={2,3,5,7,11,13,17,19,23,29};
    /*ll ksc(ll a, ll b, ll c)//乘法，模c
    {
        ll ans = 0, res = a;
        while(b)
        {
            if(b & 1)
                ans = (ans + res) % c;
            res = (res + res) % c;
            b >>= 1;
        }
        return ans;
    }*/
    inline ll ksc(ull x, ull y, ll p)
    {  // O(1)快速乘（防爆long long）
        return (x * y - (ull)((lb)x / p * y) * p + p) % p;
    }
    ll ksm(ll a,ll b,ll c)//快速幂
    {
        ll ans=1;
        while(b>0)
        {
            if(b&1)ans=ksc(ans,a,c);
            a=ksc(a,a,c);
            b>>=1;
        }
        return ans;
    }
    bool Miller_Rabin(ll x)//判断素数
    {
        ll i,j,k;
        ll s=0,t=x-1;
        if(x==2)return true;
        if(x<2 || !(x&1))return false;
        while(!(t&1))
        {
            s++;
            t>>=1;
        }
        for(int i=0;i<10 && prime[i]<x;i++)
        {
            ll a=prime[i];
            ll b=ksm(a,t,x);
            for(int j=1;j<=s;j++)
            {
                k=ksc(b,b,x);
                if(k==1 && b!=1 && b!=x-1)return false;
                b=k;
            }
            if(b != 1)return false;
        }
        return true;
    }
}

namespace Pollard_Rho
{
    using namespace MillerRabin;
    //srand((unsigned)time(NULL));
    #define ll long long

    inline ll rho(ll p)//求p的非平凡因子
    {
        ll x,y,z,c,g;
        ll i,j;
        while(1)
        {
            y=x=rand()%p;//随机生成
            z=1;
            c=rand()%p;
            i=0,j=1;
            while(++i)
            {
                x=(ksc(x,x,p)+c)%p;
                z=ksc(z,abs(y-x),p);
                if(x== y || !z)break;
                if(!(i%127) || i==j)
                {
                    g=__gcd(z,p);
                    if(g>1)return g;
                    if(i==j)y=x,j<<=1;
                }
            }
        }
    }

    inline void findmax(ll p,ll& ans)//找p的最大非平凡素因子
    {//如果p==ans说明p是质数
        if(p<=ans)return;
        if(Miller_Rabin(p))
        {
            ans=p;
            return;
        }
        ll pi=rho(p);
        while(p%pi==0)p/=pi;
        return findmax(pi,ans),findmax(p,ans);
    }
}