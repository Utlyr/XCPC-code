#include"header.h"
namespace Heavy_Path_Decomposition 
{ 
    const int MAXN = 1e5+10; 
    vector<int> e[MAXN];//记录边 
    int son[MAXN],top[MAXN],sz[MAXN],fa[MAXN],dep[MAXN]; 
    //重儿子，链顶，子树大小，父节点，深度 
    int dfn[MAXN],rak[MAXN];//结点的dfs序和dfs序对应的点 
    void dfs1(int x,int fat)//得到son,sz,fa,dep; 
    { 
        if(fat==0)dep[x]=1; 
        else dep[x]=dep[fat]+1; 
        if(e[x].size()==1 && e[x][0]==fat) 
        {    
            sz[x]=1; 
            fa[x]=fat; 
            return; 
        } 
        for(auto y:e[x]) 
        { 
            if(y==fat)continue; 
            dfs1(y,x); 
            sz[x]+=sz[y]; 
            if(sz[y]>sz[son[x]])son[x]=y; 
        } 
        fa[x]=fat; 
        sz[x]+=1; 
    } 
    int cnt=1; 
    void dfs2(int x,int t)//得到top 
    { 
        top[x]=t; 
        dfn[x]=cnt++; 
        rak[cnt-1]=x; 
        if(son[x]==0)return;//没有儿子 
        dfs2(son[x],t);//搜重儿子 
        for(auto y:e[x]) 
        { 
            if(y==son[x] || y==fa[x])continue; 
            dfs2(y,y); 
        } 
    }
}