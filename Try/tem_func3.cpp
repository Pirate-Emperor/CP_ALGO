long long qexp(long long a, long long b, long long m) {
    long long res = 1;
    while (b) {
        if (b % 2) res = res * a % m;
        a = a * a % m;
        b /= 2;
    }
    return res;
}

long long solution(long long a, int b, int c) {
    // c*c^(n-1)
    // Sum n 1-a( a-1Cn-1 * c*(c-1)^(n-1)) => c^a * (1+c)^(a-1)
    // Sum n 1-(a-50)( a-1Cn-1 *n* c*(c-1)^(n-1)) => c^(a-b) * (1+c)^(a-1-b)
    long long mod=1e9+7;
    long long all = (qexp(c,a,mod))%mod;
    long long lef = ((a==b)?0:qexp(c,a-b,mod)+((a-b)*qexp(c,a-b-1,mod))%mod)%mod;
    long long resu = all - lef;
    return resu;
    
}
