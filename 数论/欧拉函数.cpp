#include"header.h"
//定义欧拉函数g(n)为小于n的与n互质的数的个数
namespace Euler_Function
{
    const int MAXN = 2e5+10;
    int phi[MAXN];//记录欧拉函数值
    int book[MAXN];

    //求单个数的欧拉函数值
    int euler_phi(int x)
    {
        int ans=x;
        for(int i=2;i*i<=x;i++)
        {
            if(x%i==0)
            {
                ans=ans/i*(i-1);
                while(x%i==0)x/=i;
            }
        }
        if(x>1)ans=ans/x*(x-1);
        return ans;
    }
    vector<int> v;
    //求1~n的欧拉函数值
    void get(int n)//最后结果就是phi数组
    {
        phi[1]=1;book[1]=1;
        for(int i=2;i<=n;i++)
        {
            if(!book[i])
            {
                v.push_back(i);
                phi[i]=i-1;
            }
            for(int j=0;j<v.size();j++)
            {
                if(i*v[j]>n)break;
                book[i*v[j]]=1;
                if(i%v[j]==0)
                {
                    phi[i*v[j]]=v[j]*phi[i];
                    break;
                }
                phi[i*v[j]]=phi[i]*(v[j]-1);
            }
        }
    }
}