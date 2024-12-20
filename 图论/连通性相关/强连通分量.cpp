#include"./../header.h"
//tarjin算法求强连通分量
struct TARJIN
{
    int n1,tot,sccnt;//sccnt为强连通分量个数
    vector<int> scc,dfn,low;//scc记录i在哪个强连通分量
    vector<int> vis;
    vector<vector<int>> son,sc;//图，sc记录该强连通分量的元
    stack<int> st;
    void init(int n)
    {
        n1=n;
        vis.resize(n+1);scc.resize(n+1);
        dfn.resize(n+1);low.resize(n+1);
        son.resize(n+1);sc.resize(n+1);
        tot=sccnt=0;
    }
    void tarjin(int v)
    {
        dfn[v]=low[v]=++tot;
        st.push(v);vis[v]=1;
        for(auto x:son[v])
        {
            if(!dfn[x]){
                tarjin(x);
                low[v]=min(low[v],low[x]);
            }else if(vis[x])
            {
                low[v]=min(low[v],dfn[x]);
            }
        }
        if(dfn[v]==low[v])
        {
            sccnt++;int u;
            do{
                u=st.top();
                vis[u]=0;
                st.pop();
                scc[u]=sccnt;
                sc[sccnt].push_back(u);
            }while(v != u);
        }
    }
    void Tarjin(void)
    {
        for(int i=1;i<=n1;i++)
        {
            if(!dfn[i])tarjin(i);
        }
    }
};