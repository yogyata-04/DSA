#include<bits/stdc++.h>
using namespace std;

int mod=1e9+7;

int solve(int i,vector<int> &vec,int last,vector<vector<int>> &dp){
    if(i==vec.size()) return 0;
    if(dp[i][last+1]!=-1) return dp[i][last+1];
    //take if larger than last
    int take=0;
    if(last==-1 || vec[i]>vec[last]){
        take=1+solve(i+1,vec,i,dp);
    }
    //not take - larger than last/smaller than last
    int nottake=solve(i+1,vec,last,dp);
    return dp[i][last+1]=max(take,nottake);
}

int main(){
    int n;
    cin>>n;
    vector<int> vec(n);
    for(int i=0;i<n;i++){
        cin>>vec[i];
    }
    vector<vector<int>> dp(n,vector<int>(n+1,-1)); //index,prev_index
    //I was thinking how to store element as it is of size 10^9 so yes we can store in such cases remember it
    cout<<solve(0,vec,-1,dp);
}
