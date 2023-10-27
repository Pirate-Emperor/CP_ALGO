// C++ program for modular multiplication without
// any overflow
#include<iostream>
using namespace std;

typedef long long int ll;

// To compute (a * b) % mod
ll mulmod(ll a, ll b, ll mod)
{
    ll res = 0; // Initialize result
    a = a % mod;
    while (b > 0)
    {
        // If b is odd, add 'a' to result
        if (b % 2 == 1)
            res = (res + a) % mod;

        // Multiply 'a' with 2
        a = (a * 2) % mod;

        // Divide b by 2
        b /= 2;
    }

    // Return result
    return res % mod;
}

// Driver program
int main()
{
   ll a = 25000000000000000, b = 50000000000000001;
   cout << mulmod(a, b, 100000000000000000);
   return 0;
}
