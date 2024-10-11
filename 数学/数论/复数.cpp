#include"header.h"

struct Complex
{
    double x,y;
    Complex(double xx=0,double yy=0)
    {
        x=xx;y=yy;
    }
};
Complex operator+(Complex a,Complex b)
{
    return Complex(a.x+b.x,a.y+b.y);
}
Complex operator-(Complex a,Complex b)
{
    return Complex(a.x-b.x,a.y-b.y);
}
Complex operator*(Complex a,Complex b)
{
    return Complex(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);
}
Complex operator/(Complex a,Complex b)
{
    return Complex((a.x*b.x+a.y*b.y)/(b.x*b.x+b.y*b.y),(a.y*b.x-a.x*b.y)/(b.x*b.x+b.y*b.y));
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