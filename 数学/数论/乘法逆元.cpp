#include"header.h"
//扩展欧几里得法：需gcd(a,b)=1,x为a模b的逆元
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
