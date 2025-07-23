#include"header.h"
const int MAXN = 1e6+10;
/*
 *  SA板子,oldrk开二倍空间
 *  id用于第二维数据基数排序
 *  s为要处理的字符串,字符串base1
 */
int sa[MAXN],rk[MAXN],oldrk[MAXN<<1],id[MAXN],key1[MAXN],cnt[MAXN];
int height[MAXN];
string s;
bool cmp(int x,int y,int w) {
	return oldrk[x]==oldrk[y]&&oldrk[x+w]==oldrk[y+w];//表示两维数据都相等
}
void SA() {
	int n=s.length()-1;//s是base1的字符串，n是其实际长度
	int m=128;//第一次rk的范围在char内
	/* 对长度为1的字符串基数排序得到初始sa和rk */
	for (int i=1;i<=n;i++)++cnt[rk[i]=s[i]];
	for (int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
	for (int i=n;i>=1;i--)sa[cnt[rk[i]]--]=i;
	int p;
	for (int w=1;;w<<=1,m=p) {
		p=0;
		for (int i=n;i>=n-w+1;i--)id[++p]=i;//先处理第二位溢出的，放在最前面(实际也是得到第一维的下标)
		for (int i=1;i<=n;i++)if (sa[i]>w)id[++p]=sa[i]-w;//对应的第一维下标

		//开始处理第一维
		for (int i=1;i<=m;i++)cnt[i]=0;
		for (int i=1;i<=n;i++)++cnt[key1[i]=rk[id[i]]];//放到桶内
		for (int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
		//得到新的sa数组
		for (int i=n;i>=1;i--)sa[cnt[key1[i]]--]=id[i];
		for (int i=1;i<=n;i++)oldrk[i]=rk[i];
		//得到新的rk数组
		p=0;
		for (int i=1;i<=n;i++) rk[sa[i]]=cmp(sa[i],sa[i-1],w)?p:++p;
		if (p==n)break;
	}
}
/*
 * height[i]=LCP(suf(sa[i-1]),suf(sa[i]));
 * 复杂度O(n)
 */
void getH() {
	int n=s.length()-1;//s base1
	for (int i=1,k=0;i<=n;++i) {
		if (rk[i]==0)continue;
		if (k)--k;
		while (s[i+k]==s[sa[rk[i]-1]+k])++k;
		height[rk[i]]=k;
	}
}