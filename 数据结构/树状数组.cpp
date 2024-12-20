#include"header.h"
//树状数组
struct TreeArray
{
    int n;
    vector<int> a;
    int lowbit(int x)
    {
        return x&(-x);
    }
    void init(int n1)
    {
        n=n1;a.resize(n1+1);
    }
    void add(int pos,int k)//pos位置加k
    {
        for(int i=pos;i<=n;i+=lowbit(i))
        {
            a[i]+=k;
        }
    }
    int ask(int pos)
    {
        int ans=0;
        for(int i=pos;i>=1;i-=lowbit(i))ans+=a[i];
        return ans;
    }
    int ask(int l,int r)
    {
        return ask(r)-ask(l-1);
    }
};