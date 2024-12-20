#include"./../header.h"
//tarjin算法求割点
struct CutPointTarjin
{
    vector<int> dfn,low,cp;//cp为割点
    int tot,cnt;//cnt为割点数量
    vector<bool> flag;//记录是否已经是割点
    vector<vector<int>> son;//邻接链表存图
    int root,n1;
    void init(int n)
    {
        dfn.resize(n+1);low.resize(n+1);
        son.resize(n+1);
        tot=0;cnt=0;n1=n;
        flag.resize(n+1,false);
    }
    void tarjin(int x)
    {
        dfn[x]=low[x]=++tot;
        int col=0;//记录子树个数
        for(auto y:son[x])
        {
            if(!dfn[y])
            {
                col++;
                tarjin(y);
                low[x]=min(low[x],low[y]);
                if(x==root&&col>=2||x!=root&&dfn[x]<=low[y])
                {
                    if(!flag[x]){
                        cnt++;cp.push_back(x);flag[x]=true;
                    }
                }
            }
            else low[x]=min(low[x],dfn[y]);
        }
    }
    void Tarjin(void)
    {
        for(int i=1;i<=n1;i++)
        {
            root=i;
            if(!dfn[i])tarjin(i);
        }
    }
};

//Tarjin算法求割边
struct CutLineTarjin
{
    vector<int> dfn,low,fa;//fa[i]为i的父节点
    vector<bool> isb;//如果isb[i]==true则（i，fa[i]）为一条割边
    int cnt,n,tot;
    vector<vector<int>> son;
    void init(int n1)
    {
        n=n1;tot=0;
        dfn.resize(n1+1);low.resize(n1+1);
        fa.resize(n1+1);isb.resize(n1+1,false);
        son.resize(n1+1);cnt=0;
    }
    void tarjin(int x,int fat)
    {
        dfn[x]=low[x]=++tot;
        for(auto y:son[x])
        {
            if(y==fat)continue;//反向边跳过
            if(!dfn[y])
            {
                fa[y]=x;
                tarjin(y,x);
                low[x]=min(low[x],low[y]);
                if(low[y]>dfn[x])
                {
                    cnt++;isb[y]=true;
                }
            }
            else low[x]=min(low[x],dfn[y]);
        }
    }
    void Tarjin(void)
    {
        for(int i=1;i<=n;i++)
        {
            if(!dfn[i])tarjin(i,-1);
        }
    }
};