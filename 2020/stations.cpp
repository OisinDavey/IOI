//
// ~oisín~ C++ Template
//

#include                <bits/stdc++.h>
#define MX_N            1005
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

vector<int> adj[MX_N];
int glit = 0;
int in[MX_N], out[MX_N];
int p[MX_N];
int l[MX_N];

void fill(int at, int d){
    in[at] = glit++;
    for(int to : adj[at]){
        if(p[at] == to){
            continue;
        }
        p[to] = at;
        fill(to, d+1);
    }
    out[at] = glit++;
    l[at] = (d%2)?out[at]:in[at];
    return;
}

vector<int> label(int n, int k, vector<int> u, vector<int> v){
    for(int i=0;i<n;++i){
        adj[i] = {};
    }
    for(int i=0;i<n-1;++i){
        adj[u[i]].pb(v[i]);
        adj[v[i]].pb(u[i]);
    }
    fill(0, 0);
    int tmp[n];
    int rank[glit+1];
    memcpy(tmp, l, sizeof(tmp));
    sort(tmp, tmp+n);
    for(int i=0;i<n;++i){
        rank[tmp[i]] = i;
    }
    vector<int> ans;
    for(int i=0;i<n;++i){
        ans.pb(rank[l[i]]);
    }
    return ans;
}

int find_next_station(int s, int t, vector<int> c){
    if(s < c.front()){
        if(t < s){
            return c.back();
        }else{
            int lo = 0;
            int hi = c.size()-1;
            while(lo < hi){
                int mid = lo + (hi-lo)/2;
                if(t <= c[mid]){
                    hi = mid;
                }else{
                    lo = mid+1;
                }
            }
            return c[lo];
        }
    }else{
        if(t > s){
            return c.front();
        }else{
            int lo = 0;
            int hi = c.size()-1;
            while(lo < hi){
                int mid = lo + (hi-lo+1)/2;
                if(t >= c[mid]){
                    lo = mid;
                }else{
                    hi = mid-1;
                }
            }
            return c[lo];
        }
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> u, v;
    for(int i=0;i<n-1;++i){
        int a, b;
        cin >> a >> b;
        u.pb(a);
        v.pb(b);
    }
    vector<int> ans = label(n, 1000, u, v);
    for(int i=0;i<n;++i){
        cout << ans[i] << ' ';
    }
    cout << endl;
    while(true){
        int s, t;
        cin >> s >> t;
        vector<int> neighbors;
        int cnt;
        cin >> cnt;
        while(cnt--){
            int val;
            cin >> val;
            neighbors.pb(val);
        }
        cout << find_next_station(s, t, neighbors) << endl;
    }
}
