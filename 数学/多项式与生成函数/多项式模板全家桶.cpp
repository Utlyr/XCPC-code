#include"header.h"

//快速傅里叶变换
namespace FFT
{
    const int MAXN = 1e6+10;
    //complex<double> z{a,b} 表示a+bi
    double pi = acos(-1.0);

    //n必须为2的幂
    //a为系数数组 或者 点值数组
    //如果被卡常，可改为数组
    void fft(vector<complex<double>> &a,int n,int mode)
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

    //多项式乘法（fft实现）
    vector<complex<double>> a(MAXN),b(MAXN);//系数数组
    void multiple(){
        int n,m;
        cin>>n>>m;
        int limit = ceil(log2(max(n,m)));
        limit++;
        limit = (1<<limit);
        for(int i=0;i<=n;i++)
        {
            double tmp;cin>>tmp;
            a[i]=complex<double>{tmp,0};
        }
        for(int i=0;i<=m;i++)
        {
            double tmp;cin>>tmp;
            b[i]=complex<double>{tmp,0};
        }
        fft(a,limit,1);
        fft(b,limit,1);
        for(int i=0;i<limit;i++)a[i]*=b[i];
        fft(a,limit,-1);

        //此处对结果输出，m+n+1项多项式
        for(int i=0;i<=m+n;i++)
        {
            cout<<(int)((a[i].real()/limit)+0.5)<<" ";
        }
    }
}

//快速数论变换
namespace NTT
{
    const int mod=998244353,g=3,ig=332748118;//模数，原根，ig是g的逆元
    //一般多项式长度不超过8e6可以用上面的模数

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

    int rev[2100000];
    //mode=1为DFT，mode=0为逆变换
    //注意所有运算要在模mod意义下进行
    /*
    ****** for(int i=0;i<limit;++i)rev[i]=(rev[i/2]/2+(i%2)*limit/2);
        rev数组处理方法，limit为数组元素上限，是2的幂次
    */
    void ntt(vector<int> &x,int n,int mode)
    {
        for(int i=0;i<n;i++)if(i<rev[i])swap(x[i],x[rev[i]]);
        for(int len=1;len<n;len<<1)
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
}

//多项式求乘法逆元
namespace Ployinv//(NTT实现)
{
    const int MAXN = 4e6+10;
    using namespace NTT;
    //a为原始多项式数组，b为求逆后的结果
    vector<int> a(MAXN),b(MAXN),F(MAXN);
    void ployinvNTT(vector<int> &G,int n)//多项式求逆(mod x^n) ,最后b为结果数组 ,传入b
    {
        if(n==1)
        {
            G[0]=ksm(a[0],mod-2);return;
        }
        ployinvNTT(G,n+1>>1);
        int limit=1,len=0;
        while(limit<(n<<1))
        {
            limit<<=1;++len;
        }

        //两种初始化方法
        for(int i=1;i<limit;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<len-1);
        //for(int i=0;i<limit;++i)rev[i]=(rev[i/2]/2+(i%2)*limit/2);
        for(int i=0;i<n;i++)F[i]=a[i];
        for(int i=n;i<limit;i++)F[i]=0;
        ntt(G,limit,1);ntt(F,limit,1);
        for(int i=0;i<limit;i++)
        {
            G[i]=(2-F[i]*G[i]%mod+mod)%mod*G[i]%mod;
        }
        ntt(G,limit,0);
        for(int i=n;i<limit;i++)G[i]=0;
    }
}


