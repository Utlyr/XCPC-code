#include"../header.h"
/*
1.在一张连通的无向图中，对于两个点 u 和 v，如果无论删去哪条边（只能删去一条）都不能使它们不连通，我们就说 u 和 v 边双连通。
2.在一张连通的无向图中，对于两个点 u 和 v，如果无论删去哪个点（只能删去一个，且不能删 u 和 v 自己）都不能使它们不连通，我们就说 u 和 v 点双连通。
*/
//Tarjin算法求边双连通分量
//这里有一个点只能在一个双连通分量中
struct DoubleLineTarjin//注意重边，可用unordered_map处理
{
    int n,tot,cnt;//cnt为边双个数
    vector<int> dfn,low;
    vector<vector<int>> son,scc;//图，边双
    stack<int> st;
    void init(int n1)
    {
        n=n1;tot=cnt=0;
        dfn.resize(n1+1);low.resize(n1+1);
        son.resize(n1+1);scc.resize(n1+1);
    }
    void pop(int pos)
    {
        cnt++;
        int tmp=-1;
        while(tmp!=pos)
        {
            scc[cnt].push_back((tmp=st.top()));
            st.pop();
        }
    }
    void tarjin(int x,int fat)
    {
        dfn[x]=low[x]=++tot;
        st.push(x);
        for(auto y:son[x])
        {
            if(y==fat)continue;
            if(!dfn[y])
            {
                tarjin(y,x);
                low[x]=min(low[x],low[y]);
                if(low[y]>dfn[x])pop(y);
            }
            else low[x]=min(low[x],dfn[y]);
        }
    }
    void Tarjin(void)
    {
        for(int i=1;i<=n;i++)
        {
            if(!dfn[i])tarjin(i,-1),pop(i);
        }
    }
};