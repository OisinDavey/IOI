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

void allocate_tickets(vector<vector<int> > s);

//void allocate_tickets(vector<vector<int> > s){
//    for(vector<int>& v : s){
//        for(int x : v){
//            cout << x << ' ';
//        }
//        cout << endl;
//    }
//    cout << endl;
//    return;
//}

ll find_maximum(int k, vector<vector<int> > x){
    int n = x.size();
    int m = x[0].size();
    vector<vector<int> > ans;
    for(int i=0;i<n;++i){
        vector<int> tmp;
        for(int j=0;j<m;++j){
            tmp.pb(-1);
        }
        ans.pb(tmp);
    }

    pair<ll, int> rows[n][m];
    priority_queue<pair<ll, int> > minus[n], none[n];
    priority_queue<pair<ll, int> > over;//Gain, i pos
    char state[n][m];
    ll res = 0ll;
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            rows[i][j].fi = x[i][j];
            rows[i][j].se = j;
        }
        sort(rows[i], rows[i]+m);
        reverse(rows[i], rows[i]+m);
        for(int j=m-k;j<m;++j){
            minus[i].push({rows[i][j].fi, rows[i][j].se});//val, j pos
            res -= rows[i][j].fi;
            state[i][rows[i][j].se] = '-';
        }
        for(int j=0;j<m-k;++j){
            none[i].push({rows[i][j].fi, rows[i][j].se});//val, j pos
            state[i][rows[i][j].se] = 'o';
        }
        if(!none[i].empty()){
            over.push({none[i].top().fi + minus[i].top().fi, i});
        }else{
            over.push({2ll*minus[i].top().fi, i});
        }
    }

    int cnt = k*n/2;
    while(cnt--){
        auto p = over.top();
        over.pop();
        int i = p.se;
        int j_minus = minus[i].top().se;
        minus[i].pop();
        res += p.fi;
        if(!none[i].empty()){
            int j_none = none[i].top().se;
            none[i].pop();

            none[i].push({x[i][j_minus], j_minus});
            if(!minus[i].empty()){
                over.push({none[i].top().fi + minus[i].top().fi, i});
            }

            state[i][j_none] = '+';
            state[i][j_minus] = 'o';
        }else{
            if(!minus[i].empty()){
                over.push({2ll*minus[i].top().fi, i});
            }

            state[i][j_minus] = '+';
        }
    }

    vector<int> P[n], M[n];
    pair<int, int> reg[n];
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            if(state[i][j] == '+'){
                P[i].pb(j);
            }
            if(state[i][j] == '-'){
                M[i].pb(j);
            }
        }
        reg[i] = {P[i].size(), i};
    }

//    for(int i=0;i<n;++i){
//        for(int j=0;j<m;++j){
//            cout << state[i][j];
//        }
//        cout << endl;
//    }
//    cout << endl;

    for(int i=0;i<k;++i){
        sort(reg, reg+n);
        reverse(reg, reg+n);
        for(int j=0;j<n/2;++j){
            int id = reg[j].se;
            ans[id][P[id].back()] = i;
            P[id].pop_back();
            --reg[j].fi;
        }
        for(int j=n/2;j<n;++j){
            int id = reg[j].se;
            ans[id][M[id].back()] = i;
            M[id].pop_back();
        }
    }
    allocate_tickets(ans);
    return res;
}

//int main(){
//    int k;
//    int n, m;
//    cin >> k >> n >> m;
//    vector<vector<int> > v;
//    for(int i=0;i<n;++i){
//        vector<int> tmp;
//        for(int j=0;j<m;++j){
//            int x;
//            cin >> x;
//            tmp.pb(x);
//        }
//        v.pb(tmp);
//    }
//    cout << find_maximum(k, v) << endl;
//}
