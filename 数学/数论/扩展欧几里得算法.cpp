#include"header.h"

//给出ax+by=gcd(a,b)的一组解
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
