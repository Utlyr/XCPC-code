#include"header.h"

namespace SegmentTree//线段树，以加法为例，根节点为1
{
	const int MAXN = 1e5+5;
	int a[MAXN];//原始数据
	struct node
	{
		int l,r,sum,lazy;//[l,r]区间
	};//点结构
	node tree[MAXN*4];
	void push_down(int root)//将root处标记向下传递
	{
		if(tree[root].l == tree[root].r)
		{
			tree[root].sum+=tree[root].lazy;
			tree[root].lazy=0;//清空标记
			return;
		}
		tree[root].sum+=tree[root].lazy*(tree[root].r-tree[root].l+1);
		//传递标记
		tree[root*2].lazy+=tree[root].lazy;
		tree[root*2+1].lazy+=tree[root].lazy;
		tree[root].lazy=0;
	}

	//递归建树
	void build(int l,int r,int root)
	{
		tree[root].l=l;tree[root].r=r;tree[root].lazy=0;
		if(l==r)
		{
			tree[root].sum=a[tree[root].l];
			return;
		}
		int mid=(l+r)/2;
		build(l,mid,root*2);
		build(mid+1,r,root*2+1);
		tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
	}

	//区间查询
	int getsum(int l,int r,int root)
	{
		if(l<=tree[root].l && r>=tree[root].r)
		{
			push_down(root);
			return tree[root].sum;
		}
		push_down(root);
		int sum=0,mid=(tree[root].l+tree[root].r)/2;
		if(l<=mid)sum+=getsum(l,r,root*2);
		if(r>=mid+1)sum+=getsum(l,r,root*2+1);
		return sum;
	}
	//区间更新
	void update(int l,int r,int c,int root)//[l,r]加c
	{
		if(l<=tree[root].l && r>=tree[root].r)
		{
			tree[root].lazy+=c;
			push_down(root);
			return;
		}
		int mid=(tree[root].l+tree[root].r)/2;
		push_down(root);
		if(l<=mid)update(l,r,c,root*2);
		push_down(root*2);
		if(r>=mid+1)update(l,r,c,root*2+1);
		push_down(root*2+1);
		tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
	}
}