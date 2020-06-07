//
// Solved Molecules, basic sliding window technique thanks to interesting restraint (maxw - minw <= u - l), 100%
//

#include                <bits/stdc++.h>
#define MX_N            5001
#define mp              make_pair
#define mod7            1000000007
#define modpi           314159
#define PI              3.141592653589793238
#define pb              push_back
#define FastIO          ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define All(a)          a.begin(),a.end()
#define fi              first
#define se              second
#define ll              long long int
#define ull             unsigned long long int

int kx[8]  =            {+2, +2, -2, -2, +1, +1, -1, -1};
int ky[8]  =            {+1, -1, +1, -1, +2, -2, +2, -2};
int d9x[9] =            {+1, +1, +1, +0, +0, +0, -1, -1, -1};
int d9y[9] =            {+1, +0, -1, +1, +0, -1, +1, +0, -1};
int dx4[4] =            {+0, +0, +1, -1};
int dy4[4] =            {+1, -1, +0, +0};

ll gcd(ull a, ull b){
    return (a==0)?b:gcd(b%a,a);
}

ll lcm(ull a, ull b){
    return a*(b/gcd(a,b));
}

const long long INF = 1e18;

using namespace std;

int main(){
    int n;
    int l, r;
    cin >> n >> l >> r;
    pair<ll, int> a[n];
    for(int i=0;i<n;++i){
        cin >> a[i].fi;
        a[i].se = i;
    }
    sort(a, a+n);
    int L = 0;
    int R = 0;
    ll sum = a[0].fi;
    while(L <= R){
        if(sum > r){
            sum -= a[L].fi;
            ++L;
        }else if(sum < l){
            ++R;
            sum += a[R].fi;
        }else{
            cout << R-L+1 << endl;
            for(int i=L;i<=R;++i){
                cout << a[i].se << ' ';
            }
            cout << endl;
            return 0;
        }
    }
    cout << "0\n";
    return 0;
}
