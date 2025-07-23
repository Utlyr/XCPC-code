#include"header.h"

struct SegmentTree//线段树，以加法为例，根节点为1
{
	vector<int> a;//原始数据
	struct node
	{
		int l,r,sum,lazy;//[l,r]区间
	};//点结构
	vector<node> tree;
	SegmentTree(int n)
	{
		tree.resize(n*4+4);
		a.resize(n+1);
	}
	SegmentTree(vector<int> arr)
	{
		a=arr;tree.resize(arr.size()*4);
	}
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
};

struct DSGT//动态开点线段树
{
	vector<int> a;//原始数据
	vector<int> ls,rs;
	int cnt;
	struct node
	{
		int l,r,sum,lazy;//[l,r]区间
	};//点结构
	vector<node> tree;
	DSGT(int n)
	{
		tree.resize(n*2+4);
		a.resize(n+1);
		ls.resize(2*n+1);rs.resize(2*n+1);
		cnt=1;
	}
	DSGT(vector<int> arr)
	{
		a=arr;tree.resize(arr.size()*4);
		ls.resize(2*arr.size()+1);rs.resize(2*arr.size()+1);
		cnt=1;
	}
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
		tree[ls[root]].lazy+=tree[root].lazy;
		tree[rs[root]].lazy+=tree[root].lazy;
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
		ls[root]=++cnt;
		rs[root]=++cnt;
		build(l,mid,ls[root]);
		build(mid+1,r,rs[root]);
		tree[root].sum=tree[ls[root]].sum+tree[rs[root]].sum;
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
		if(l<=mid)sum+=getsum(l,r,ls[root]);
		if(r>=mid+1)sum+=getsum(l,r,rs[root]);
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
		if(l<=mid)update(l,r,c,ls[root]);
		push_down(ls[root]);
		if(r>=mid+1)update(l,r,c,rs[root]);
		push_down(rs[root]);
		tree[root].sum=tree[ls[root]].sum+tree[rs[root]].sum;
	}
};

struct info{//节点信息
    int mx;
};

struct node{//标签
    
};
using tag=node;
info operator+(const info &a,const info &b){

}
tag operator+(const tag &a,const tag &b){

}
//将标记f放置到标记a上并且把改标签影响传递到x上
void apply(info &x,tag &a,tag f){
    //x+=f;把f的影响放到x上
    //a+=f;把f的影响放到a上
}
template<class info,class tag>
struct LazySegmentTree{//base0
    int n;
    vector<info> tree;
    vector<tag> lazy;
    LazySegmentTree(){}//初始化空树
    LazySegmentTree(int n,info _init=info()){//下面参数为n+1则base1
        init(vector<info>(n+1,_init));//初始化成info成_init
    }
    LazySegmentTree(const vector<info> &_init){init(_init);}

    void init(const vector<info> &_init){
        n=(int)_init.size()-1;//减1则base1
        tree.assign((n<<2)+1,info());//开4倍大小，先初始化成默认值
        lazy.assign((n << 2) + 1, tag());
        function<void(int,int,int)> build=[&](int p,int l,int r){//建树，[l,r]对应节点为p
            if(l==r){
                tree[p]=_init[l-1];//删去减1则base1
                return;
            }
            int m=(l+r)/2;
            build(2*p,l,m);
            build(2*p+1,m+1,r);
            pushup(p);
        };
        build(1,1,n);
    }
    void apply(int p,const tag &v){//在p节点放置lazy标记
        ::apply(tree[p],lazy[p],v);
    }
    void pushup(int p){//用子节点维护父节点 注意lazy标记的值
        tree[p]=tree[2*p]+tree[2*p+1];
    }
    void pushdown(int p){//下放lazy标记
        apply(2*p,lazy[p]);
        apply(2*p+1,lazy[p]);
        lazy[p]=tag();//标记下放，并删去该节点的标记
    }
    //单点修改
    void modify(int x,const info &v,int p,int l,int r){
        if(l==r){
            tree[p]=v;
            return;
        }
        int m=(l+r)/2;
        pushdown(p);
        if(x<=m){
            modify(x,v,2*p,l,m);
        }
        else{
            modify(x,v,2*p+1,m+1,r);
        }
        pushup(p);
    }
    void modify(int x,const info &v){
        modify(x,v,1,1,n);
    }
    
    //区间修改，将[x,y]的值修改为v
    void modify(int x,int y,const tag &v,int p,int l,int r){
        if(y<l||r<x){//该区间不在修改区间内，无需修改
            return ;
        }
        if (x<=l&&r<=y){//该区间包含在修改区间，放置lazy标记
            apply(p,v);
            return ;
        }
        int m=(l+r)/2;
        pushdown(p);//下放标记
        modify(x,y,v,2*p,l,m);
        modify(x,y,v,2*p+1,m+1,r);
        pushup(p);//维护当前节点
    }
    void modify(int x,int y,const tag &v){
        modify(x,y,v,1,1,n);
    }
    //区间询问 query（l，r）;
    info query(int x,int y,int p,int l,int r){
        if(y<l||r<x){//该区间不在询问区间内，返回空值
            return info();
        }
        if(x<=l&&r<=y){//该区间包含在询问区间，返回信息
            return tree[p];
        }
        int m=(l+r)/2;
        pushdown(p);//要往下查询，所以下放标记
        return query(x,y,2*p,l,m)+query(x,y,2*p+1,m+1,r);
    }
    info query(int x,int y){
        return query(x,y,1,1,n);
    }
};