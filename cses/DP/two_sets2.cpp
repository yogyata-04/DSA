#include<bits/stdc++.h>
using namespace std;

int mod=1e9+7;

int solve(int i,int n,int req_sum,vector<vector<int>> &dp){
    if(req_sum==0) return 1;
    if(i==n) return 0;
    if(dp[i][req_sum]!=-1) return dp[i][req_sum];
    int take=0;
    if(req_sum>=i){
        take=solve(i+1,n,req_sum-i,dp)%mod;
    }
    int nottake=solve(i+1,n,req_sum,dp)%mod;
    return dp[i][req_sum]=(take+nottake)%mod;
}

int main(){
    int n;
    cin>>n;
    int sum=(n*(n+1))/2;
    if(sum%2==1) cout<<0<<endl;
    else{
        vector<vector<int>> dp(n,vector<int>(sum/2+1,-1));
        cout<<solve(1,n,sum/2,dp);
    }
}
