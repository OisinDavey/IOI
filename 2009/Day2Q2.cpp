//
// Solution that runs in O(N*N*LogN), gets 84% due to WA not TLE, can't find bug
//

#include                <bits/stdc++.h>
#define MX_N            821
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

//Global Variables
int N, S;
ll maxtime = -1;
pair<int, int> source;
pair<int, int> dest;
char G[MX_N][MX_N];
ll B[MX_N][MX_N];

bool valid(int& x, int& y){
    return (x >= 0 && x < N && y >=0 && y < N);
}

//FillB Variables
bool inB[MX_N][MX_N];

void fillB(){
    queue<pair<int, int> > Q;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            if(G[i][j] == 'H'){
                B[i][j] = 0;
                Q.push(mp(i, j));
                inB[i][j] = true;
            }else{
                B[i][j] = (INF-1);
                inB[i][j] = false;
            }
        }
    }
    while(!Q.empty()){
        pair<int, int> at = Q.front();
        Q.pop();
        inB[at.fi][at.se] = false;
        for(int i=0;i<4;++i){
            int x = at.fi + dx4[i];
            int y = at.se + dy4[i];
            if(valid(x, y)){
                if(G[x][y] != 'T' && B[x][y] > (1 + B[at.fi][at.se])){
                    B[x][y] = S + B[at.fi][at.se];
                    if(!inB[x][y]){
                        inB[x][y] = true;
                        Q.push(mp(x, y));
                    }
                }
            }
        }
    }
}

//canReach Variables
bool inD[MX_N][MX_N];
ll mass[MX_N][MX_N];

bool canReach(ll time){
    queue<pair<int, int> > Q;
    memset(inD, 0, sizeof(inD));
    memset(mass, -1, sizeof(mass));
    Q.push(source);
    inD[source.fi][source.se] = true;
    mass[source.fi][source.se] = time;
    while(!Q.empty()){
        pair<int, int> at = Q.front();
        Q.pop();
        inD[at.fi][at.se] = false;
        if(mass[at.fi][at.se] >= B[at.fi][at.se]){
            continue;
        }
        if(at == dest){
            return true;
        }
        for(int i=0;i<4;++i){
            int x = at.fi + dx4[i];
            int y = at.se + dy4[i];
            if(valid(x, y)){
                if(G[x][y] != 'T' && (mass[x][y] == -1 || mass[x][y] > mass[at.fi][at.se] + 1)){
                    mass[x][y] = mass[at.fi][at.se] + 1;
                    if(!inD[x][y]){
                        inD[x][y] = true;
                        Q.push(mp(x, y));
                    }
                }
            }
        }
    }
    return false;
}

int Bsearch(){
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            if(G[i][j] != 'T'){
                maxtime = max(maxtime, B[i][j]);
            }
        }
    }
    ll L = 0;
    ll R = maxtime+1;
    while(L < R){
        ll M = L + (R - L + 1)/2;
        if(canReach(M)){
            L = M;
        }else{
            R = M - 1;
        }
    }
    return L;
}

int main(){
    FastIO;
    cin >> N >> S;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            cin >> G[i][j];
            if(G[i][j] == 'M')
                source = mp(i, j);
            if(G[i][j] == 'D')
                dest = mp(i, j);
        }
    }
    fillB();
    ll ans = Bsearch();
    if(canReach(ans))
        cout << floor((double)ans/(double)S) << endl;
    else
        cout << -1 << endl;
}

