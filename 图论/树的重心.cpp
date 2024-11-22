#include"header.h"
namespace Centroid//树的重心 
{ 
    //默认从1~n 
    //centroid[root]即为整棵树的重心 
    int root;//根节点 
    const int Maxn=300010; 
    int siz[Maxn];//记录节点大小 
    int weigth[Maxn];//记录节点重量，即所有子树中大小的最大值 
    int centroid[Maxn];//记录重心（以当前节点向下的子树)
    int totcen[3],tot=0;//记录整棵树的重心 
    int fa[Maxn],n;//n为节点数,fa记录父节点 
    vector<int> son[Maxn]; 
    void dfs(int u)//得到centroid数组 
    { 
        siz[u]=1,centroid[u]=u; 
        for(auto v:son[u]) 
        { 
            dfs(v); 
            siz[u]+=siz[v]; 
            weigth[u]=max(weigth[u],siz[v]); 
        } 
        for(auto v:son[u]) 
        { 
            int p=centroid[v]; 
            while(p != u) 
            { 
                if(max(weigth[p],siz[u]-siz[p])<=siz[u]/2) 
                { 
                    centroid[u]=p; 
                    break; 
                } 
                else 
                { 
                    p=fa[p]; 
                } 
            } 
        } 
    } 
    void get(void)//得到整棵树的所有重心 
    { 
        dfs(root); 
        for(int i=1;i<=n;i++) 
        { 
            if(max(weigth[i],n-siz[i])<=n/2) 
            { 
                totcen[++tot]=i; 
            } 
        } 
    }
}