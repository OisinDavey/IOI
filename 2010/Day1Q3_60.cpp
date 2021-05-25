//
// ~oisín~ C++ Template
//

#include                <bits/stdc++.h>
#define MX_N            9006001 
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

int fenw[MX_N];

void update(int at, int val){
    while(at < 9006001){
        fenw[at] += val;
        at += (at)&(-at);
    }
    return;
}

int query(int at){
    int res = 0;
    while(at > 0){
        res += fenw[at];
        at -= (at)&(-at);
    }
    return res;
}

int find_kth(int k){
    ++k;
    int L = 1;
    int R = 9006000;
    while(L < R){
        int M = L + (R-L)/2;
        if(query(M) >= k){
            R = M;
        }else{
            L = M+1;
        }
    }
    return L;
}

int rectangle(int R,int C,int H,int W,int Q[3001][3001]){
    memset(fenw, 0, sizeof(fenw));
    int best = 2147483647;
    for(int i=0;i<H;++i){
        for(int j=0;j<W;++j){
            update(Q[i][j], +1);
        }
    }
    for(int i=0;i+H-1<R;++i){
        if(i%2 == 0){
            for(int j=0;j+W-1<C;++j){
                best = min(best, find_kth(H*W/2));
                if(j+W == C && i+H < R){
                    for(int k=j;k<C;++k){
                        update(Q[i][k], -1);
                        update(Q[i+H][k], +1);
                    }
                }else if(j+W != C){
                    for(int k=0;k<H;++k){
                        update(Q[i+k][j], -1);
                        update(Q[i+k][j+W], +1);
                    }
                }
            }
        }else{
            for(int j=C-W-1;j >= -1;--j){
                best = min(best, find_kth(H*W/2));
                if(j == -1 && i+H < R){
                    for(int k=0;k<W;++k){
                        update(Q[i][k], -1);
                        update(Q[i+H][k], +1);
                    }
                }else if(j != -1){
                    for(int k=0;k<H;++k){
                        update(Q[i+k][j+W], -1);
                        update(Q[i+k][j], +1);
                    }
                }
            }
        }
    }
    best = min(best, find_kth(H*W/2));
    return best;
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
