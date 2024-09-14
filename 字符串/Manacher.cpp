#include"header.h"
//用于求d1,d2数组，d1[i]表示以i为中心的奇回文串个数
//d2[i]表示以i为中心的偶回文串个数
//由d1,d2可以求得回文子串的个数
namespace Manacher
{
    //使用0索引
    const int MAXN = 1e5+10;
    string s;//要求的字符串
    int n;
    int d1[MAXN],d2[MAXN];
    void get1(void)
    {
        for(int i=0,l=0,r=-1;i<n;i++)
        {
            int k=(i>r)?1:min(d1[l+r-i],r-i+1);
            while(0<=i-k && i+k<n && s[i-k]==s[i+k])
            {
                k++;
            }
            d1[i]=k--;
            if(i+k>r)
            {
                l=i-k;
                r=i+k;
            }
        }
    }
    void get2(void)
    {
        for(int i=0,l=0,r=-1;i<n;i++)
        {
            int k=(i>r)?0:min(d2[l+r-i+1],r-i+1);
            while(0<=i-k && i+k<n && s[i-k-1]==s[i+k])
            {
                k++;
            }
            d2[i]=k--;
            if(i+k>r)
            {
                l=i-k-1;
                r=i+k;
            }
        }
    }
}