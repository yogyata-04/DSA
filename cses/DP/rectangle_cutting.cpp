#include<bits/stdc++.h>
using namespace std;

//this is greedy approach we need to think it in dp way and try all cuts as greedy is not the right approach
// int solve(int a,int b,vector<vector<int>> &dp){
//     if(a==b) return 0;
//     if(dp[a][b]!=-1) return dp[a][b];
//     if(a<b){
//         return dp[a][b]=solve(a,b-a,dp)+1;
//     }
//     else{
//         return dp[a][b]=solve(a-b,b,dp)+1;
//     }
// }

//TLE in two testcases
int solve(int a,int b,vector<vector<int>> &dp){
    if(a==b) return 0;
    if(dp[a][b]!=-1) return dp[a][b];
    //making vertical cuts
    int cuts=INT_MAX;
    for(int i=1;i<b;i++){
        cuts=min(cuts,solve(a,b-i,dp)+solve(a,i,dp)+1);
    }
    //making horizontal cuts
    for(int i=1;i<a;i++){
        cuts=min(cuts,solve(a-i,b,dp)+solve(i,b,dp)+1);
    }
    return dp[a][b]=cuts;
}

int main(){
   int a,b;
   cin>>a>>b;
   vector<vector<int>> dp(a+1,vector<int>(b+1,-1));
   cout<<solve(a,b,dp);
}
