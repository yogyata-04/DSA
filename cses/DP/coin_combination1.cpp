#include<bits/stdc++.h>
using namespace std;
 
int mod=1e9+7;

//here permutations of similar set will be treated different so we need to have all ways, that's why we ran loop for all coins on each x value and not just take,not take - we will use take/not take concept when different permutations of similar combination are treated as 1
long long solve(int x,vector<int> &coins,vector<int> &dp){
    if(x==0) return 1;
    if(dp[x]!=-1) return dp[x];
    int ans=0;
    //I can pick any coin at given chance so trying all ways
    for(auto it:coins){
        if(x-it>=0){
            ans=(ans+solve(x-it,coins,dp))%mod;
        }
    }
    return dp[x]=ans;
}
 
int main(){
    int n,x;
    cin>>n>>x;
    vector<int> coins(n);
    for(int i=0;i<n;i++){
        cin>>coins[i];
    }
    vector<int> dp(x+1,-1);

    cout<<solve(x,coins,dp);
    
}
