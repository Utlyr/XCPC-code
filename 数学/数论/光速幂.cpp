#include"header.h"

int p = 998244353;
const int BL = 1<<16;
int qp[BL+10][2]; //0:a^t%p 1:a^is%p
int base;
void init(int a)
{
    base = sqrt(p);
    qp[0][0]=qp[0][1]=1;
    for(int i=1;i<=base;i++)qp[i][0]=qp[i-1][0]*a%p;
    for(int i=1;i<=base;i++)qp[i][1]=qp[i-1][1]*qp[base][0]%p;
}

int phi(int x)
{
	int res=x;
	for(int i=2;i*i<=x;i++)
	{
		if(x%i==0) res=res/i*(i-1);
		while(x%i==0) x/=i;
	}
	if(x>1) res=res/x*(x-1);
	return res;
}

int ask(int b)//return a^b%p
{
    b%=phi(p);//这里phi(p)可以预处理
    return qp[b%base][0]*qp[b/base][1]%p;
}