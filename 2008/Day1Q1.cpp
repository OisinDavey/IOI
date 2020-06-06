//
// ~oisín~ C++ Template
//

#include                <bits/stdc++.h>
#define MX_N            500001
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

static const int ALPH_SIZE = 27;

int glit = 0;

int desc[MX_N];
char val[MX_N];
int edge[MX_N][ALPH_SIZE];
bool last[MX_N];

int ans;

int create(char v){
    ans = glit++;
    for(int i=0;i<ALPH_SIZE;++i)
        edge[ans][i] = -1;
    val[ans] = v;
    last[ans] = 0;
    desc[ans] = 0;
    return ans;
}

string ins;
vector<char> outp;
int root;

void insert(int at, int pos){
    if(pos == ins.size()){
        desc[at] = 0;
        return;
    }
    if(edge[at][ins[pos] - (int)'a'] == -1){
        edge[at][ins[pos] - (int)'a'] = create(ins[pos]);
    }
    insert(edge[at][ins[pos] - (int)'a'], pos+1);
    desc[at] = max(desc[at], 1+desc[edge[at][ins[pos] - (int)'a']]);
}

int maxdesc;
int best;

void getlast(int at){
    last[at] = 1;
    maxdesc = -1;
    best = -1;
    for(int i=0;i<ALPH_SIZE;++i){
        if(edge[at][i] == -1){
            continue;
        }
        if(maxdesc < desc[edge[at][i]]){
            best = edge[at][i];
            maxdesc = desc[edge[at][i]];
        }
    }
    if(maxdesc == -1)
        return;
    getlast(best);
}


void PrintGraph(int at){
    if(at != root){
        if(val[at] == ('z' + 1))
            outp.pb('P');
        else
            outp.pb(val[at]);
    }
    int L = -1;
    for(int i=0;i<ALPH_SIZE;++i){
        if(edge[at][i] == -1){
            continue;
        }
        if(last[edge[at][i]]){
            L = edge[at][i];
            continue;
        }
        PrintGraph(edge[at][i]);
    }
    if(L != -1){
        PrintGraph(L);
    }
    if(val[at] == ('z' + 1) || last[at] || at == root){
        return;
    }
    outp.pb('-');
}

int main(){
    FastIO;
    int n;
    cin >> n;
    root = create('R');
    for(int i=0;i<n;++i){
        cin >> ins;
        ins += ('z' + 1);
        insert(root, 0);
    }
    getlast(root);
    PrintGraph(root);
    cout << outp.size() << endl;
    for(char& c : outp)
        cout << c << endl;
}
