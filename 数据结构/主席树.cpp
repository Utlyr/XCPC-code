#include"header.h"
//可持久化权值线段树，使用前对数据进行离散化
struct ChairTree
{
    #define sum(x) tree[x].val
    #define ls(x) tree[x].l
    #define rs(x) tree[x].r
    int n,cnt;
    vector<int> root;//根的位置
    vector<int> a;//原始数据
    struct node{
        int l,r;
        int val;
    };
    vector<node> tree;
    void init(int n1)
    {
        //这里乘的数至少为log(n)+1
        n=n1;root.resize(n1+1);
        a.resize(n1+1);tree.resize(n1*20);
        cnt=0;
    }
    void pushup(int x){sum(x)=sum(ls(x))+sum(rs(x));}
    void update(int last,int now,int pos,int k,int l,int r)
    {
        //上个版本的根，现在版本的根，修改的位置，加k，当前节点表示区间[l,r]
        if(l==r)
        {
            sum(now)=sum(last)+k;
        }
        else
        {
            ls(now)=ls(last);rs(now)=rs(last);
            int mid=(l+r)>>1;
            if(pos<=mid)
            {
                ls(now)=++cnt;update(ls(last),ls(now),pos,k,l,mid);
            }
            else
            {
                rs(now)=++cnt;update(rs(last),rs(now),pos,k,mid+1,r);
            }
            pushup(now);
        }
    }
    void update(int last,int now,int pos)
    {
        update(last,now,pos,1,0,n);
    }
    void built(void)
    {
        for(int i=1;i<=n;i++)
        {
            root[i]=++cnt;
            update(root[i-1],root[i],a[i]);
        }
    }
    int Kth(int last,int now,int k,int l,int r)
    {
        if(l==r)return l;
        int mid=l+r>>1;
        int val=sum(ls(now))-sum(ls(last));
        if(val>=k)return Kth(ls(last),ls(now),k,l,mid);
        else return Kth(rs(last),rs(now),k-val,mid+1,r);
    }
    int Kth(int last,int now,int k)
    {
        return Kth(last,now,k,0,n);
    }
    int ask(int l,int r,int k)
    {
        return Kth(root[l-1],root[r],k);//返回的是离散化后的下标
    }
};