#include<bits/stdc++.h>
using namespace std;
 
long long mod=1e9+7;
 
long long solve(int x,vector<long long> &coins,vector<long long> &dp){
    if(x==0) return 0;
    if(dp[x]!=-1) return dp[x];
    long long minCoins=INT_MAX;
    //Initially I was trying using take, not take and index of coins array i but this lead to wrong answer in one case and tle in one case
    //Better way try all ways based on choices
    //I can pick any coin at given chance so trying all ways
    for(auto it:coins){
        if(x-it>=0){
            minCoins=min(minCoins,solve(x-it,coins,dp)+1);
        }
    }
    return dp[x]=minCoins;
}
 
int main(){
    int n,x;
    cin>>n>>x;
    vector<long long> coins(n);
    for(int i=0;i<n;i++){
        cin>>coins[i];
    }
    vector<long long> dp(x+1,-1);

    int ans=solve(x,coins,dp);
    if(ans<INT_MAX){
        cout<<ans<<endl;
    }
    else {
        cout<<"-1"<<endl;
    }
    
}
