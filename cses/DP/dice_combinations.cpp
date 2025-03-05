#include<bits/stdc++.h>
using namespace std;

long long mod=1e9+7;

long long solve(int n,vector<long long> &dp){
    if(n==0) return 1;
    if(dp[n]!=-1) return dp[n]%mod;
    long long sum=0;
    for(int i=1;i<=6;i++){
        if(n-i>=0) sum+=solve(n-i,dp);
    }
    return dp[n]=sum%mod;
}

int main(){
    int n;
    cin>>n;
    vector<long long> dp(n+1,-1);
    cout<<solve(n,dp);
    
}
