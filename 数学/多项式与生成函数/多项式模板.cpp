#include"header.h"
double pi = acos(-1.0);
const int mod=998244353,g=3,ig=332748118;//模数，原根，ig是g的逆元
//一般多项式长度不超过8e6可以用上面的模数
const int MAXN = 4e6+10;
int inv2=(mod+1)/2;

vector<int> t1(MAXN),t2(MAXN),t3(MAXN),t4(MAXN);

int ksm(int a,int b)
{
    int ans=1;
    while(b>0)
    {
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}

void fft(vector<complex<double>> &a,int n,int mode)//mode为-1或者1
{
    if(n==1)return;
    vector<complex<double>> a1(n/2),a2(n/2);
    for(int i=0;i<n;i+=2)
    {
        a1[i>>1]=a[i];a2[i>>1]=a[i+1];
    }
    fft(a1,n>>1,mode);
    fft(a2,n>>1,mode);
    complex<double> Wn{cos(2.0*pi/n),mode*sin(2.0*pi/n)},k{1,0};//单位根,k次根

    for(int i=0;i<(n>>1);i++,k=k*Wn)
    {
        a[i]=a1[i]+k*a2[i];
        a[i+(n>>1)]=a1[i]-k*a2[i];
    }
}


//mode=1为DFT，mode=0为逆变换
//注意所有运算要在模mod意义下进行
/*
****** for(int i=0;i<limit;++i)rev[i]=(rev[i/2]/2+(i%2)*limit/2);
       rev数组处理方法，limit为数组元素上限，是2的幂次
*/
int rev[2100000];

int getl(int len)
{
    int n=1;
    while(n<=len)n<<=1;
    for(int i=0;i<n;i++)rev[i]=(rev[i>>1]>>1)|((i&1)?(n>>1):0);
    return n;
}
void NTT(vector<int> &x,int n,int mode)//每次NTT前调用getl进行初始化rev,n为2的幂次
{
    for(int i=0;i<n;i++)if(i<rev[i])swap(x[i],x[rev[i]]);
    for(int len=1;len<n;len<<=1)
    {
        int Wn=ksm(mode?g:ig,(mod-1)/(2*len));
        for(int i=0;i<n;i+=2*len)
        {
            int W=1,X,Y;
            for(int j=i;j<i+len;j++)
            {
                X=x[j];Y=W*x[j+len]%mod;
                x[j]=(X+Y)%mod;x[j+len]=(X-Y+mod)%mod;
                W=(W*Wn)%mod;
            }
        }
    }
    if(!mode)
    {
        int invs=ksm(n,mod-2);
        for(int i=0;i<n;i++)x[i]=(x[i]*invs)%mod;
    }
}

void polymul(vector<int> &a,vector<int> &b,vector<int> &c,int n,int m)//n为deg(a)，m为deg(b)  // c = a * b
{
    int limit=1,len=0;
    limit=getl(n+m);
    for(int i=0;i<=n;i++)t1[i]=a[i];
    for(int i=0;i<=m;i++)t2[i]=b[i];
    NTT(t1,limit,1);NTT(t2,limit,1);
    for(int i=0;i<limit;i++)t1[i]=t1[i]*t2[i]%mod;
    NTT(t1,limit,0);
    for(int i=0;i<=m+n;i++)c[i]=t1[i];
}

//以下所有的n均为2的幂次，即先求一次getl(deg(f)+1);
void polyinv(vector<int> &f,vector<int> &g,int n)//求f的乘法逆元，f->g
{
    if(n==1){g[0]=ksm(f[0],mod-2);return;}
    polyinv(f,g,n>>1);
    int l=getl(n);
    for(int i=0;i<n;i++)t1[i]=f[i],t2[i]=g[i];
    for(int i=n;i<l;i++)t1[i]=t2[i]=0;
    NTT(t1,l,1);NTT(t2,l,1);
    for(int i=0;i<l;i++)t1[i]=t1[i]*t2[i]%mod*t2[i]%mod;
    NTT(t1,l,0);
    for(int i=0;i<n;i++)g[i]=(2*g[i]-t1[i]+mod)%mod;
}

//n=getl(deg(f)+1)
void polysqrt(vector<int> &f,vector<int> &g,int n)
{
    if(n==1){g[0]=1;return;}//这里根据题目确定
    polysqrt(f,g,n>>1);
    int l=getl(n<<1);
    for(int i=0;i<n;i++)t3[i]=f[i],t4[i]=0;
    for(int i=n;i<l;i++)t3[i]=t4[i]=0;
    polyinv(g,t4,n);l=getl(n<<1);
    NTT(t3,l,1);NTT(t4,l,1);
    for(int i=0;i<l;i++)t3[i]=t3[i]*t4[i]%mod;
    NTT(t3,l,0);
    for(int i=0;i<n;i++)g[i]=(g[i]+t3[i])*inv2%mod;
}

//多项式对数函数
//n=getl(def(f)+1)
void polyln(vector<int> &f,vector<int> &g,int n)//g=ln(f) 一定要有[0]f=1否则没有符合条件的
{
    g[0]=0;
    polyinv(f,t3,n);//求逆
    for(int i=0;i<n-1;i++)t4[i]=f[i+1]*(i+1)%mod;//求导
    int limit=n<<1;
    NTT(t3,limit,1);NTT(t4,limit,1);
    for(int i=0;i<limit;i++)t3[i]=t3[i]*t4[i]%mod;
    NTT(t3,limit,0);
    for(int i=1;i<n;i++)g[i]=t3[i-1]*ksm(i,mod-2)%mod;//积分
    for(int i=0;i<limit;i++)t3[i]=t4[i]=0;//求完后更新t3,t4为0，不然exp会错
}

vector<int> t5(MAXN),t6(MAXN);
//多项式指数函数
//n=getl(def(f)+1)
void polyexp(vector<int> &f,vector<int> &g,int n)//g=exp(f) 一定要有[0]f=0,否则没有符合条件的
{
    if(n==1){g[0]=1;return;}
    polyexp(f,g,n>>1);
    polyln(g,t5,n);
    int l=getl(n<<1);
    for(int i=0;i<n;i++)t6[i]=f[i];
    for(int i=n;i<l;i++)t5[i]=t6[i]=0;
    NTT(t5,l,1);NTT(t6,l,1);NTT(g,l,1);
    for(int i=0;i<l;i++)g[i]=g[i]*(1-t5[i]+t6[i]+mod)%mod;
    NTT(g,l,0);
    for(int i=n;i<l;i++)g[i]=0;
}