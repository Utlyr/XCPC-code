#include"header.h"
//st表，处理RMQ问题
struct STTable
{
    vector<int> Log;
    vector<vector<int>> arr;
    int n;
    void init(int n1)
    {
        n=n1;
        Log.resize(n1+1);
        for(int i=2;i<=n;i++)Log[i]=Log[i/2]+1;
        arr.resize(Log[n]+1);
    }
    void build(vector<int>&a)
    {
        arr[0].resize(n+1);
        for(int i=1;i<=n;i++)arr[0][i]=a[i];
        for(int i=1;i<=Log[n];i++)
        {
            arr[i].resize(n+1);
            for(int j=1;j+(1<<i)-1<=n;j++)
            {
                arr[i][j]=min(arr[i-1][j],arr[i-1][j+(1<<i-1)]);
            }
        }
    }
    int ask(int l,int r)
    {
        int s=Log[r-l+1];
        return min(arr[s][l],arr[s][r-(1<<s)+1]);
    }
};