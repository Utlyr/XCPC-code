#include"header.h"

//有向无环图拓扑排序
struct Tupo
{
    int n;
    vector<vector<int>> son;
    vector<int> in;//记录入度
    vector<int> ans;//记录拓扑序
    void init(int n1)
    {
        n=n1;
        son.resize(n1+1);in.resize(n1+1);
    }
    void add(int u,int v)//添加u->v的有向边
    {
        son[u].push_back(v);
        in[v]++;
    }
    void tupo(void)
    {
        queue<int> q;
        for(int i=1;i<=n;i++)
        {
            if(in[i]==0)q.push(i);
        }
        while(q.size())
        {
            int t=q.front();q.pop();
            ans.push_back(t);
            for(auto x:son[t])
            {
                in[x]--;
                if(in[x]==0)q.push(x);
            }
        }
    }
};