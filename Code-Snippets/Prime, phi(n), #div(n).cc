int np, prime[N];
bool isp[N];
void sieve(int N) {
    memset(isp, true, sizeof isp);
    isp[0] = isp[1] = false;
    for(int i=2; i<N; i++) if(isp[i]) {
        prime[++np]=i;
        for(int j=2*i; j<N; j+=i) {
            isp[j]=false;
        }
    }
}

inline int pwr(int a, int n) {
    int ans=1;
    while(n) {
        if(n&1) ans=ans*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return ans;
}

int np, prime[N];
bool isprime[N];
void primes(int N) {
    memset(isprime, true, sizeof isprime);
    isprime[0] = isprime[1] = false;
	rep(i,N) if(i>1) {
		if(isprime[i]) prime[++np] = i;
		rep1(j,np) {
			if(i * prime[j] >= N) break;
			isprime[i * prime[j]] = false;
			if(i % prime[j] == 0) break;
		}
	}
}

bool check(int n) {
    if(n<2) return false;
    for(int i=3; i <= sqrt(n); i+=2) if(n%i==0) return false;
    return true;
}

inline int phi(int n) {
    // Calculates Totient(n). Needs prime[]. O(sqrt(n))
    int ans = n;
    for(int i=1; prime[i] <= n/prime[i]; i++) if(n%prime[i]==0) {
        ans -= ans/prime[i];
        while(n%prime[i]==0) n/=prime[i];
    }
    if(n!=1) ans -= ans/n;
    return ans;
}

int phi[N];
inline void phis(int N) {
    phi[1]=1;
    for(int i=2; i<N; i++) if(!phi[i]) {
        phi[i] = i-1;
        for(int j=2*i; j<N; j+=i) {
            if(!phi[j]) phi[j] = j;
            phi[j] = phi[j]/i*(i-1);
        }
    }
}

inline int divnum(int n) {
    // Counts number of divisors of n. Needs prime[]. O(sqrt(n))
    if(n < 1) return 0;
    int ans(1), temp;
    for(int i=1; prime[i] <= n/prime[i]; ++i)
        if(n%prime[i]==0) {
            temp = 1;
            while(n%prime[i]==0) temp++, n/=prime[i];
            ans *= temp;
        }
    ans <<= (n!=1);
    return ans;
}

inline int divsum(int n) {
    // Sum of divisors of n. Needs prime[]. O(sqrt(n))
    if(n < 1) return 0;
    int ans(1), temp, cur;
    for(int i=1; prime[i] <= n/prime[i]; ++i)
        if(n%prime[i]==0) {
            temp = 1, cur = 1;
            while(n%prime[i]==0)
                cur*=prime[i], temp+=cur, n/=prime[i];
            ans *= temp;
        }
    ans *= (n!=1) + n;
    return ans;
}

inline int add(int a, int b, int m) {
	a%=m; if(a<0) a+=m;
	b%=m; if(b<0) b+=m;
	if(a+b<0 or a+b>=m) return (a-m)+b;
	return a+b;
}
inline int mul(int a, int b, int m) {
	a%=m; if(a<0) a+=m;
	b%=m; if(b<0) b+=m;
	int q = ((dbl)a * (dbl)b) / (dbl)m;
	int r = a*b - q*m;
	return (r<0 ? r+m:r);
}

inline int pwr(int a, int n, int m) {
    int ans(1);
    while(n) {
        if(n & 1) ans = mul(ans, a, m);
        n >>= 1;
        a = mul(a, a, m);
    }
    return ans;
}
uint myrand(int n) {
	return rand()*rand()%n*rand()%n;
}
bool ispmiller(int p) { // O(30*logp)
	if(p<2) return false;
	if(p==2) return true;
	if(p%2==0) return false;
	int s=p-1; s>>=__builtin_ctzll(s);
	rep(i,30) {
		int val=pwr(myrand(p-1)+1,s,p), temp=s;
		while(temp!=p-1 and con(val,2,p-2)) {
			val=mul(val,val,p);
			temp<<=1;
		}
		if(val!=p-1 and temp%2==0) return false;
	}
	return true;
}
inline int pollardrho(int n) { // O(n^0.25)
	if(n==1) return 1;
	if(n%2==0) return 2;
	int c=myrand(n-1)+1, x=myrand(n-2)+2, y=x;
	int d=1; while(d==1) {
		x=mul(x,x,n)+c; if(x>=n) x-=n;
		y=mul(y,y,n)+c; if(y>=n) y-=n;
		y=mul(y,y,n)+c; if(y>=n) y-=n;
		d=__gcd(abs(x-y),n);
		if(d==n) return (ispmiller(n) ? n:pollardrho(n));
	}
	return d;
}
