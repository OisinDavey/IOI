//
// ~oisín~ C++ Template
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

int dp[3001][3001];

int rectangle(int R,int C,int H,int W,int Q[3001][3001]){
    int l = 1;
    int r = R*C;
    while(l < r){
        int m = l + (r-l)/2;
        for(int i=0;i<R;++i){
            for(int j=0;j<C;++j){
                if(m < Q[i][j]){
                    dp[i][j] = +1;
                }else if(m > Q[i][j]){
                    dp[i][j] = -1;
                }else{
                    dp[i][j] = 0;
                }
                if(i > 0){
                    dp[i][j] += dp[i-1][j];
                }
                if(j > 0){
                    dp[i][j] += dp[i][j-1];
                }
                if(i > 0 && j > 0){
                    dp[i][j] -= dp[i-1][j-1];
                }
            }
        }
        bool good = false;
        for(int i=H-1;i<R;++i){
            for(int j=W-1;j<C;++j){
                int x = i-H;
                int y = j-W;
                int sum = dp[i][j];
                if(x >= 0){
                    sum -= dp[x][j];
                }
                if(y >= 0){
                    sum -= dp[i][y];
                }
                if(x >= 0 && y >= 0){
                    sum += dp[x][y];
                }
                if(sum <= 0){
                    good = true;
                }
            }
        }
        if(good){
            r = m;
        }else{
            l = m+1;
        }
    }
    return l;
}

int Q[3001][3001];

int main(){
    int n, m, h, w;
    cin >> n >> m >> h >> w;
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            cin >> Q[i][j];
        }
    }
    cout << rectangle(n,m,h,w,Q) << endl;
}
