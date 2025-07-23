#include"header.h"
constexpr  int MAXN = 4e7+10;
constexpr int mod = 1e9 + 7,inv2=500000004,inv3=333333336;//inv2,inv3跟据公式需要来
double pi=acos(-1.0);

/* min_25筛模板（求积性函数前缀和）
 * 创建于：2025/7/23
 * 要修改部分：g1,g2···,跟据题目把多项式拆解成多个单项式即可
 *			sp1,sp2···,表示拆开的单项式的值的前缀和(只统计素数)
 */
const int N = 2e5+10;//取sqrt(n)即可
int pri[N],cnt=0,sp1[N],sp2[N];
int n,sqr,tot,g1[N],g2[N],w[N],id1[N],id2[N];
bool flag[N];
int func(int x) {
	//要求值的多项式
	return x*(x-1)%mod;
}
void init(int n) {
	flag[1]=1;
	for (int i=1;i<=n;i++) {
		if (!flag[i]) {
			pri[++cnt]=i;

			//计算sp1,sp2···
			sp1[cnt]=(sp1[cnt-1]+i)%mod;
			sp2[cnt]=(sp2[cnt-1]+1ll*i*i)%mod;

		}
		for (int j=1;j<=cnt&&pri[j]*i<=n;j++) {
			flag[i*pri[j]]=1;
			if (i%pri[j]==0)break;
		}
	}
}
int S(int x,int y) {
	if (pri[y]>=x)return 0;
	int k=x<=sqr?id1[x]:id2[n/x];

	//此处跟据多项式对应，比如下面就是x*x-x
	int ans=(g2[k]-g1[k]+mod-(sp2[y]-sp1[y])+mod)%mod;

	for (int i=y+1;i<=cnt&&pri[i]*pri[i]<=x;i++) {
		int pe=pri[i];
		for (int e=1;pe<=x;e++,pe=pe*pri[i]) {
			int xx=pe%mod;
			ans=(ans+func(xx)*(S(x/pe,i)+(e!=1))%mod)%mod;
		}
	}
	return ans%mod;
}
void Solve() {
	cin>>n;
	sqr=sqrt(n);
	init(sqr);
	//处理g(n,0)
	for (int i=1;i<=n;) {
		int j=n/(n/i);
		w[++tot]=n/i;
		int tmp=w[tot]%mod;

		//处理g1,g2,注意g1[tot]为sum(f(tmp))-f(1);
		g1[tot]=(tmp*(tmp+1)/2%mod-1+mod)%mod;
		g2[tot]=(tmp*(tmp+1)/2%mod*(2*tmp+1)%mod*inv3%mod-1+mod)%mod;

		if (n/i<=sqr)id1[n/i]=tot;
		else id2[n/(n/i)]=tot;
		i=j+1;
	}
	for (int i=1;i<=cnt;i++) {
		for (int j=1;j<=tot&&pri[i]*pri[i]<=w[j];j++) {
			int k=w[j]/pri[i]<=sqr?id1[w[j]/pri[i]]:id2[n/(w[j]/pri[i])];
			//下面代码跟据递推式调整，主要是乘号前面的部分
			g1[j]-=pri[i]*(g1[k]-sp1[i-1]+mod)%mod;
			g2[j]-=pri[i]*pri[i]%mod*(g2[k]-sp2[i-1]+mod)%mod;
			g1[j]%=mod,g2[j]%=mod;
			if(g1[j]<0)g1[j]+=mod;
			if(g2[j]<0)g2[j]+=mod;
		}
	}
	//注意积性函数f(1)=1
	cout<<S(n,0)+1<<"\n";
}