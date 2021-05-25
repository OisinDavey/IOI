
//
// ~oisín~ C++ Template
//

#include                <bits/stdc++.h>
#include                "combo.h"
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

string guess_sequence(int N){
    if(N == 1){
        int temp1 = press("A");
        int temp2 = press("B");
        int temp3 = press("X");
        if(temp1)
            return "A";
        else if(temp2)
            return "B";
        else if(temp3)
            return "X";
        else
            return "Y";
    }
    //Find first character
    string S = "";
    if(1){
        int temp1 = press("AB");
        if(temp1 == 0){
            int temp2 = press("X");
            if(temp2 == 1){
                S += 'X';
            }else{
                S += 'Y';
            }
        }else{
            int temp2 = press("A");
            if(temp2 == 1){
                S += 'A';
            }else{
                S += 'B';
            }
        }
    }
    string CharSet = "";
    if(S[0] == 'A'){
        CharSet = "BXY";
    }else if(S[0] == 'B'){
        CharSet = "AXY";
    }else if(S[0] == 'X'){
        CharSet = "ABY";
    }else{
        CharSet = "ABX";
    }
    for(int i=1;i<(N-1);++i){
        string testString = S + CharSet[0] + S + CharSet[1] + CharSet[0] + S + CharSet[1] + CharSet[1] + S + CharSet[1] + CharSet[2];
        int temp1 = press(testString);
        if(temp1 == S.size()){
            S += CharSet[2];
        }else if(temp1 == S.size()+1){
            S += CharSet[0];
        }else{
            S += CharSet[1];
        }
    }
    if(1){
        string testString = S + CharSet[0] + S + CharSet[1];
        int temp1 = press(testString);
        if(temp1 == S.size()){
            S += CharSet[2];
        }else{
            int temp2 = press(S + CharSet[0]);
            if(temp2 == S.size()){
                S += CharSet[1];
            }else{
                S += CharSet[0];
            }
        }
    }
    return S;
}
