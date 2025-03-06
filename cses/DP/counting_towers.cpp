#include<bits/stdc++.h>
using namespace std;

long long mod=1e9+7;

//getting tle in some cases
//i-> row state->horizontal(1) or vertical(2) state of i-1 initially state=0;
long long solve(int i,int h, int state,vector<vector<long long>> &dp){
    if(i==h) return 1;
    if(dp[i][state]!=-1) return dp[i][state];
    long long ways=0;
    if(state==0){
        //we can have vertical + horizontal
        ways=ways+solve(i+1,h,1,dp)%mod;
        ways=ways+solve(i+1,h,2,dp)%mod;
    }
    else if(state==2){
        // //we can extend both
        // ways=ways+solve(i+1,h,2);
        // //we can extend left and stop right
        // ways=ways+solve(i+1,h,2);
        // //we can stop left and extend right
        // ways=ways+solve(i+1,h,2);
        // //we can stop both and start vertical
        // ways=ways+solve(i+1,h,2);
        // //we can stop both and start horizontal
        // ways=ways+solve(i+1,h,1);
        //shortform 
        ways=ways+4*solve(i+1,h,2,dp)%mod+solve(i+1,h,1,dp)%mod;
    }
    else{
        // //we can extend horizontal
        // ways=ways+solve(i+1,h,1);
        // //we can stop horizontal and start vertical
        // ways=ways+solve(i+1,h,2);
        // //we can stop horizontal and start horizontal
        // ways=ways+solve(i+1,h,1);
        //shortform
        ways=ways+solve(i+1,h,2,dp)%mod+2*solve(i+1,h,1,dp)%mod;
    }
    return dp[i][state]=ways%mod;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        long long h;
        cin>>h;
        vector<vector<long long>> dp(h,vector<long long>(3,-1));
        cout<<solve(0,h,0,dp)<<endl;
    }
}
