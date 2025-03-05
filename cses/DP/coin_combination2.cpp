#include<bits/stdc++.h>
using namespace std;
 
int mod=1e9+7;

//TLE because of memoization
int solve(int i,int x,vector<int> &coins,vector<vector<int>> &dp){
    if(i>=coins.size()) return 0;
    if(x==0) return 1;
    if(dp[i][x]!=-1) return dp[i][x];
    int take=0;
    if(x-coins[i]>=0) take=solve(i,x-coins[i],coins,dp)%mod;
    int nottake=solve(i+1,x,coins,dp)%mod;
    return dp[i][x]=(take+nottake)%mod;
}
 
int main(){
    int n,x;
    cin>>n>>x;
    vector<int> coins(n);
    for(int i=0;i<n;i++){
        cin>>coins[i];
    }
    vector<vector<int>> dp(n,vector<int>(x+1,-1));

    cout<<solve(0,x,coins,dp);
    
}
