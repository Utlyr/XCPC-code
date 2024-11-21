#include"header.h"
//不带懒标记（单点修改，区间查询)
template<class node>
struct SGT
{
    #define l(p) p<<1
    #define r(p) p<<1|1
    int n;
    vector<node> tree;
    SGT(){}
    SGT(int _n,node _v=node())
    {
        init(_n,_v);
    }
    template<class T>
    SGT(vector<T> _init)//base 1
    {
        init(_init);
    }
    void init(int _n,node _v=node())
    {
        init(vector(_n+1,_v));//base 1
    }
    template<class T>
    void build(vector<T>&a,int p,int l,int r)
    {
        if(l==r)
        {
            tree[p]=a[l];
            return;
        }
        int mid=(l+r)>>1;
        build(a,l(p),l,mid);
        build(a,r(p),mid+1,r);
        pushup(p);
    }
    template<class T>
    void init(vector<T> _init)//此处_init是base 1的
    {
        n=_init.size()-1;
        tree.assign(n<<2,node());
        build(_init,1,1,n);
    }
    void pushup(node p)
    {
        tree[p]=tree[l(p)]+tree[r(p)];
    }

    void modify(int p,int l,int r,int x,const node &v)
    {
        if(l==r)
        {
            tree[p]=v;
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid)modify(l(p),l,mid,x,v);
        if(x>mid)modify(r(p),mid+1,r,x,v);
        pushup(p);
    }

    void modify(int x,const node &v)
    {
        modify(1,1,n,x,v);
    }
    node query(int p,int l,int r,int x,int y)
    {
        if(x>r || y<l)return node();
        if(x>=l && y<=r)return tree[p];
        int mid=(x+y)>>1;
        return query(l(p),l,mid,x,y)+query(r(p),mid+1,r,x,y);
    }
    node query(int l,int r)
    {
        return query(1,1,n,l,r);
    }
};
struct node
{
    int val;
};
node operator+(node a,node b)
{
    node c;
    c.val=a.val+b.val;
    return c;
}

//带懒标记，支持区间修改
struct LSGT
{

};