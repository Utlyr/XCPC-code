#include"header.h"
//前缀函数：一个长度为n的字符串，其前缀函数被定义为一个长度为n的数组
//p[i]表示最长真前缀长度
//定义p[0]=0

//得到前缀函数
vector<int> prefix_function(string s)
{
    int n=s.length();
    vector<int> pi(n);
    for(int i=1;i<n;i++)
    {
        int j=pi[i-1];
        while(j>0 && s[i]!=s[j])j=pi[j-1];
        if(s[i]==s[j])j++;
        pi[i]=j;
    }
    return pi;
}

//KMP算法
vector<int> find_occ(string s,string t)//在s中找t的出现位置
{
    string cur=t+"#"+s;
    int sz1=s.size(),sz2=t.size();
    vector<int> v;
    vector<int> lps=prefix_function(cur);
    for(int i=sz2+1;i<=sz1+sz2;i++)
    {
        if(lps[i]==sz2)v.push_back(i-2*sz2);
    }
    return v;
}