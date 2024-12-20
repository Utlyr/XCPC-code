#include"header.h"
//笛卡尔树是一个特殊的二叉搜索树
//有数组a
//构造二叉树满足中序遍历序号有序，同时满足大（小）根堆的性质
//用一个单调栈即可实现

namespace DkrTree//假设数据是排列,小根堆笛卡尔树
{
    const int MAXN = 1e6+10;
    int a[MAXN],p[MAXN],l[MAXN],r[MAXN];//l[i],r[i]为i，左右儿子
    int n;
    //a是原数组，p[a[i]]=i
    void build(void)
    {
        stack<int> st;
        for(int i=1;i<=n;i++)
        {
            int t=0;
            while(st.size() && st.top()>a[i])
            {
                t=st.top();
                st.pop();
            }
            if(st.size())
            {
                r[p[st.top()]]=i;
            }
            l[i]=p[t];
            st.push(a[i]);
        }
    }
}