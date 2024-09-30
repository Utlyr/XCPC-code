#include"header.h"
#define ll long long
//pos为当前数位，pre为前面的数位记录，st为当前结果，lead记录前导0，limit记录上限;S
ll dfs(int pos,int pre,int st,……,int lead,int limit)//记搜
{
	if(pos>len) return st;//剪枝
	if((dp[pos][pre][st]……[……]!=-1&&(!limit)&&(!lead))) return dp[pos][pre][st]……[……];//记录当前值
	ll ret=0;//暂时记录当前方案数
	int res=limit?a[len-pos+1]:9;//res当前位能取到的最大值
	for(int i=0;i<=res;i++)
	{
        //有前导0并且当前位也是前导0
		if((!i)&&lead) ret+=dfs(……,……,……,i==res&&limit);
        //有前导0但当前位不是前导0，当前位就是最高位
		else if(i&&lead) ret+=dfs(……,……,……,i==res&&limit); 
		else if(根据题意而定的判断) ret+=dfs(……,……,……,i==res&&limit);
	}
	if(!limit&&!lead) dp[pos][pre][st]……[……]=ret;//当前状态方案数记录
	return ret;
}
ll part(ll x)//把数按位拆分
{
	len=0;
	while(x) a[++len]=x%10,x/=10;
	memset(dp,-1,sizeof dp);//初始化-1（因为有可能某些情况下的方案数是0）
	return dfs(……,……,……,……);//进入记搜
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%lld",&l,&r);
	    if(l) printf("%lld",part(r)-part(l-1));//[l,r](l!=0)
	    else printf("%lld",part(r)-part(l));//从0开始要特判
	}
	return 0;
}