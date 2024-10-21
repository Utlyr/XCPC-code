#include"header.h"
typedef long long ll;

map<ll, ll> mp;
ll a, b, p, ans;

ll exgcd(ll a, ll b, ll& x, ll& y) {  //求逆元和 gcd 都可以使用扩欧，非常方便 QwQ
	if(!b) {
		x = 1, y = 0;
		return a;
	}
	ll ans = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return ans;
}

ll inv(ll a, ll p) {  //求 a 模 p 的逆元
	ll x, y;
	exgcd(a, p, x, y);
	return (x % p + p) % p;
}

ll qpow(ll a, ll b, ll p) {  //快速幂
	ll ans = 1;
	while(b) {
		if(b & 1) ans = (ans * a) % p;
		a = (a * a) % p; b >>= 1;
	}
	return ans;
}

ll BSGS(ll a, ll b, ll p) {  //BSGS 主体，不解释了
	ll unit = (ll)ceil(sqrt(p)), tmp = qpow(a, unit, p);

	for(int i = 0; i <= unit; ++i)
		mp[b] = i, b = (b * a) % p;

	b = 1;

	for(int i = 1; i <= unit; ++i) {
		b = (b * tmp) % p;
		if(mp[b]) return i * unit - mp[b];
	}

	return -1;
}

ll exBSGS(ll a, ll b, ll p) {
    //特判几个特殊情况
    for(int i=0;i<=5;i++)
    {
        if(qpow(a,i,p)%p==b%p)
        {
            return i;
        }
    }
	ll x, y, g = exgcd(a, p, x, y), k = 0, tmp = 1;
	while(g != 1) {  //当 gcd(a, p) 不为 1 时，就不断除以 gcd(a, p) 直到 a 与 p 互质
		if(b % g) return -1;  //b 不能被 gcd(a, p) 整除，当然不互质
		++k, b /= g, p /= g, tmp = tmp * (a / g) % p;
		if(tmp == b) return k;
		g = exgcd(a, p, x, y);
	}
	//用传统 BSGS 来解决问题
	ll ans = BSGS(a, b * inv(tmp, p) % p, p);
	if(ans == -1) return -1;
	return ans + k;
}