//
// Solved using SPFA and very messy "Second-best-distance" logic, but it gets 100%
//

#include                <bits/stdc++.h>
#define MX_N            100001
#define MX_M            1000001
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
int N, M, K;
vector<pair<int, int> > adj[MX_N];
int mass[MX_M];
bool inQ[MX_N];
pair<int, int> d1[MX_N];
pair<int, int> d2[MX_N];
int P[MX_N];

void SPFA(){
    queue<int> Q;
    for(int i=0;i<K;++i){
        Q.push(P[i]);
        inQ[P[i]] = true;
        d1[P[i]] = mp(0, 0);
        d2[P[i]] = mp(0, 0);
    }
    while(!Q.empty()){
        int at = Q.front();
        Q.pop();
        inQ[at] = false;
        for(pair<int, int> temp : adj[at]){
            int to = temp.fi;
            int w = mass[temp.se];
            //Second-Best-Distance Logic
            if(d1[to].fi > d2[at].fi + w){
                if(d1[to].se == at){
                    d1[to].fi = d2[at].fi + w;
                }else{
                    d2[to].fi = d1[to].fi;
                    d2[to].se = d1[to].se;
                    d1[to].fi = d2[at].fi + w;
                    d1[to].se = at;
                }
            }else if(d2[to].fi > d2[at].fi + w){
                if(d1[to].se == at){
                    continue;
                }else{
                    d2[to].fi = d2[at].fi + w;
                    d2[to].se = at;
                }
            }else{
                continue;
            }
            if(!inQ[to]){
                inQ[to] = true;
                Q.push(to);
            }
        }
    }
}

int solve(){
    cin >> N >> M >> K;
    for(int i=1;i<=N;++i){
        inQ[i] = false;
        d1[i] = mp(INT_MAX/2, -1);
        d2[i] = mp(INT_MAX/2, -1);
    }
    for(int i=0;i<M;++i){
        int u, v, w;
        cin >> u >> v >> w;
        ++u, ++v;
        adj[u].pb(mp(v, i));
        adj[v].pb(mp(u, i));
        mass[i] = w;
    }
    for(int i=0;i<K;++i){
        cin >> P[i];
        ++P[i];
    }
    SPFA();
    return d2[1].fi;
}

int main(){
    FastIO;
    cout << solve() << endl;
}
