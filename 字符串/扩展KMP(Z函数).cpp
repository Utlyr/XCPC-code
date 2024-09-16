#include"header.h"
//定义z[i]表示s与s[i]开头的字符串的LCP（最长公共前缀）
//定义z[0]=0

//线性算法
vector<int> z_function(string s)
{
    int n=s.length();
    vector<int> z(n);
    for(int i=1,l=0,r=0;i<n;i++)
    {
        if(i<=r&&z[i-1]<r-i+1)
        {
            z[i]=z[i-1];
        }
        else
        {
            z[i]=max(0ll,r-i+1);
            while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
        }
        if(i+z[i]-1>r)l=i,r=i+z[i]-1;
    }
    return z;
}