/**
    Recurrence: f(n+1) = f(n) + f(n-1)
    Given: f(0) = a, f(1) = b
    Matrix Equation: A * X = B
    A = |1 1| X = |f(0)| B = |f(0) + f(1)|
        |1 0|     |f(1)|     |     f1    |
    Find f(n+1) = B = A^n * X
    How To Use?
    1. Caunsigned long long buildMatrix() and store values accordingly
    2. Find B = bigMatMod(A, n - 1)
    3. Find B = multiply(B, X)
    4. Now, f(n) = B.m[0][0]
**/

#include<bits/stdc++.h>
#define MXR 5 /// Change here
#define MXC 5

using namespace std;

unsigned long long mod;

struct matrix{
    int R, C;
    unsigned long long m[MXR][MXC];
    matrix()
    {
        memset(m, 0, sizeof(m));
    }
    matrix(int r, int c)
    {
        R = r;
        C = c;
        memset(m, 0, sizeof(m));
    }

    void clear(int r, int c)
    {
        R = r;
        C = c;
    }

    matrix operator * (const matrix b)
    {
        matrix res(R, b.C);
        if(C == b.R)
        {
            for(int r1 = 0; r1 < R; r1++){
                for(int c1 = 0; c1 < C; c1++){
                    res.m[r1][c1] = 0;
                    for(int k = 0; k < C; k++){
                        res.m[r1][c1] += ((m[r1][k] * b.m[k][c1]) % mod); /// mod here if needed
                        res.m[r1][c1] %= mod; /// mod here if needed
                    }
                }
            }
            return res;
        }
        printf("error!!!!!!!!!!!!!!\n");
        return res;
    }

    matrix operator + (const matrix b)
    {
        matrix res(R, C);
        if(R==b.R && C==b.C)
        {
            for(int i = 0; i < R; i++)
                for(int j = 0; j < C; j++)
                    res.m[i][j] = (m[i][j] + b.m[i][j]) % mod;
            return res;
        }
        printf("error!!!!!!!!!!!!!!\n");
        return res;
    }

    matrix operator * (const long long val)
    {
        matrix res(R, C);
        for(int r1 = 0; r1 < R; r1++)
            for(int c1 = 0; c1 < C; c1++)
                res.m[r1][c1] = (m[r1][c1] * val) % mod;

        return res;
    }

    matrix identity()
    {
        matrix temp;
        temp.R=R;
        temp.C=C;
        for(int i = 0; i < R; i++)
            temp.m[i][i]=1;

        return temp;
    }

    matrix pow(unsigned long long pow)
    {
        matrix temp=(*this);
        matrix ret=(*this).identity();
        while(pow)
        {
            if(pow % 2 == 1)
                ret = ret * temp;
            temp = temp * temp;
            pow /= 2;
        }
        return ret;
    }

    void setv(int v)
    {
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                m[i][j] = v;
    }

    void print()
    {
        printf("-----------------------------\n");
        printf("Row :: %d, Column :: %d\n", R, C);
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j)
                cout << m[i][j] << " ";
            cout << endl;
        }
        printf("-----------------------------\n");
    }

};

matrix bigMatMod(matrix a, unsigned long long p)
{
    if(p == 1) return a;
    if(p%2 == 1) {
        return (a * bigMatMod(a, p-1));
    }
    else {
        matrix res = bigMatMod(a, p/2);
        return (res * res);
    }
}

matrix A, B, C, R, X;

unsigned long long t, n, a, m, b, p, cas; /// f(0) = a, f(1) = b

void buildMatrix()
{
    /// Set row column accordingly
    A.clear(2, 2);
    B.clear(2, 1);
    X.clear(2, 1);

    /// Store initial values in the matrix
    A.m[0][0] = 1;
    A.m[0][1] = 1;
    A.m[1][0] = 1;
    A.m[1][1] = 0;

    X.m[0][0] = b;
    X.m[1][0] = a;
}

int main()
{
    cin>>t;
    while(t--){
        cin>>a>>b>>n>>p;

        /// base cases

        if(n==0) printf("Case %lld: %lld\n",++cas,a);
        else if(n==1) printf("Case %lld: %lld\n",++cas,b);

        else{
            mod=1;
            for(int i=1; i<=p; i++) mod*=10;

            buildMatrix();
            B = A.pow(n - 1);    //A.print();
            B = B * X;

            printf("Case %lld: %lld\n",++cas,B.m[0][0]);
        }
    }
    return 0;
}





/*
#include<bits/stdc++.h>
#define mod 1000000007
#define MXR 5 /// Change here
#define MXC 5

using namespace std;

struct matrix{
    int R, C;
    unsigned long long m[MXR][MXC];
    matrix(){}
    matrix(int r, int c){
        R = r;
        C = c;
    }

    void clear(int r, int c){
        R = r;
        C = c;
    }

    void print(){
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j)
                cout << m[i][j] << " ";
            cout << endl;
        }
    }
};

matrix multiply(matrix a, matrix b){
    matrix res(a.R, b.C);
    for(int r1 = 0; r1<a.R; r1++){
        for(int c1 = 0; c1<a.C; c1++){
            res.m[r1][c1] = 0;
            for(int k = 0; k<a.C; k++){
                res.m[r1][c1] += ((a.m[r1][k]*b.m[k][c1])%mod); /// mod here if needed
                res.m[r1][c1] %= mod; /// mod here if needed
            }
        }
    }
    return res;
}

matrix bigMatMod(matrix a, unsigned long long p){
    if(p == 1) return a;
    if(p%2 == 1) {
        return multiply(a, bigMatMod(a, p-1));
    }
    else {
        matrix res = bigMatMod(a, p/2);
        return multiply(res, res);
    }
}

matrix A, B, C, R, X;
unsigned long long t, n, a, m, b, p, cas; /// f(0) = a, f(1) = b

int main()
{
    cin>>t;
    while(t--){
        cin>>n>>a>>m>>b>>p;

        /// check initial values; f(0), f(1)

        /// Set row column accordingly
        A.clear(2, 2);
        B.clear(2, 1);
        C.clear(2, 2);
        R.clear(2, 2);

        /// Store initial values in the matrix
        A.m[0][0] = 1;
        A.m[0][1] = 1;
        A.m[1][0] = 1;
        A.m[1][1] = 0;

        X.m[0][0] = 1;
        X.m[1][0] = 1;

        B = bigMatMod(A,n);
        C = bigMatMod(A,m);

        unsigned long long x1 = B.m[1][0];
        unsigned long long y1 = B.m[0][0];
        unsigned long long x2 = C.m[1][0];
        unsigned long long y2 = C.m[0][0];

        if(x1*y2-x2*y1==0){
            printf("Case %lld: Impossible\n",++cas);
            continue;
        }

        unsigned long long x = (a*y2-b*y1)/(x1*y2-x2*y1);
        unsigned long long y = (a*x2-b*x1)/(y1*x2-y2*x1);

        R = bigMatMod(A,p);

        unsigned long long res = ((R.m[1][0]*x)%mod + (R.m[0][0]*y)%mod) %mod;

        unsigned long long dx = (a*y2-b*y1)%(x1*y2-x2*y1);
        unsigned long long dy = (a*x2-b*x1)%(y1*x2-y2*x1);

        if(x<0 || y<0 || dx || dy){
            printf("Case %lld: Impossible\n",++cas);
        }
        else{
            printf("Case %lld: %lld\n",++cas,res);
        }
    }
    return 0;
}
*/





/*#include<bits/stdc++.h>
using namespace std;

int m[2][2]={{1,1},{1,0}};

void multiply(int f[2][2],int m[2][2])
{
    int w=(f[0][0]*m[0][0])%10+(f[0][1]*m[1][0])%10;
    int x=(f[0][0]*m[0][1])%10+(f[0][1]*m[1][1])%10;
    int y=(f[1][0]*m[0][0])%10+(f[1][1]*m[1][0])%10;
    int z=(f[1][0]*m[0][1])%10+(f[1][1]*m[1][1])%10;
    f[0][0]=w%10;
    f[0][1]=x%10;
    f[1][0]=y%10;
    f[1][1]=z%10;
}

void power(int f[2][2],int n)
{
    if(n == 0 || n == 1)
        return;
    power(f,n/2);
    multiply(f,f);
    if(n%2!=0)
        multiply(f,m);
}

int fib(int f[2][2],int n)
{
    power(f,n);
    return f[0][0];
}

int main()
{
    int n;
    while(cin>>n){
        int f[2][2]={{1,1},{1,0}};
        cout<<fib(f,n-1)<<endl;
    }
    return 0;
}
*/
