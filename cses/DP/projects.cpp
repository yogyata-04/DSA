#include<bits/stdc++.h>
using namespace std;

long long solve(int i,int can_start,vector<vector<long long>> vec,vector<vector<long long>> dp){
    if(i==vec.size()){
        return 0;
    }
    if(dp[i][can_start+1]!=-1) return dp[i][can_start];
    long long take=0;
    if(can_start==-1 || vec[i][0]>=vec[can_start][1]+1){
        //can start this project then
        take=solve(i+1,i,vec,dp)+vec[i][2];
    }
    long long nottake=solve(i+1,can_start,vec,dp);
    //again did mistake of not including -1 case
    return dp[i][can_start+1]=max(take,nottake);
}

int main(){
    int n;
    cin>>n;
    long long a,b,c;
    vector<vector<long long>> vec(n,vector<long long>(3));
    for(int i=0;i<n;i++){
        cin>>a>>b>>c;
        vec[i][0]=a;
        vec[i][1]=b;
        vec[i][2]=c;
    }
    sort(vec.begin(),vec.end());
    vector<vector<long long>> dp(n,vector<long long>(n+1,-1));
    cout<<solve(0,-1,vec,dp);
}
