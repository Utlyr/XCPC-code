#include"header.h"
#include<complex>
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