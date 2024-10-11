#include"header.h"

namespace QR//二次剩余相关，只考虑模数为奇素数的情况
{
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
    //欧拉判别法，判断a是否是p的二次剩余
    int euler(int a,int p)
    {
        if(ksm(a,(p-1)/2,p)==1)return 1;
        else return 0;
    }


    int w,mod;//w^2=(r*r-a) (mod p) , mod=p;
    struct Complex//类似复数的数域
    {
        int x,y;
        Complex(int xx=0,int yy=0)
        {
            x=xx%mod;y=yy%mod;
        }
    };
    Complex operator+(Complex a,Complex b)
    {
        return Complex((a.x+b.x)%mod,(a.y+b.y)%mod);
    }
    Complex operator-(Complex a,Complex b)
    {
        return Complex((a.x-b.x+mod)%mod,(a.y-b.y+mod)%mod);
    }
    Complex operator*(Complex a,Complex b)
    {
        return Complex((a.x*b.x+a.y*b.y%mod*w)%mod,(a.x*b.y+a.y*b.x)%mod);
    }
    Complex power(Complex a,int b)
    {
        Complex ans(1,0);
        while(b>0)
        {
            if(b&1)ans=ans*a;
            a=a*a;
            b>>=1;
        }
        return ans;
    }

    //Cipolla算法求解x^2=a(mod p)
    //返回一个解（-1无解），相反数为另一个解
    int cipolla(int a,int p)
    {
        mod=p;
        srand((unsigned)time(NULL));
        if(a%p==0)return 0;
        if(!euler(a,p))return -1;
        int r;
        do{
            r=rand()%p;
            w=(r*r%p-a+p)%p;
            if(!euler(w,p))break;
        }while(1);
        Complex ans(r,1);
        ans=power(ans,(p+1)/2);
        return ans.x;
    }
}