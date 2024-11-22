#include"header.h"
namespace TreeLength
{
    const int MAXN = 1e5+10;
    int n,d=0;//结点数，直径
    int dp[MAXN];
    vector<int> son[MAXN];
    void dfs(int u,int fa)
    {
        for(auto v:son[u])
        {
            if(v==fa)continue;
            dfs(v,u);
            d=max(d,dp[u]+dp[v]+1);
            dp[u]=max(dp[u],dp[v]+1);
        }
    }
}