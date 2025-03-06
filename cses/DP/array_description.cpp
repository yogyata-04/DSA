#include<bits/stdc++.h>
using namespace std;

int mod=1e9+7;

int solve(int i,vector<int> &vec,int m,int last,vector<vector<int>> &dp){
    
    if(i==vec.size()){
        return 1;
    }
    //I used last to be -1 when at 0th index which led to segmentation fault in dp so changed it to 0
    if(dp[i][last]!=-1) return dp[i][last];
    int ways=0;
    if(vec[i]==0){
        //try all combos possible 
        for(int j=1;j<=m;j++){
            if(last==0 || abs(j-last)<=1){
                ways=(ways+solve(i+1,vec,m,j,dp))%mod;
            }
        }
    }
    else if(last!=0 && abs(last-vec[i])>1) return 0; // remember to use condition last!=0 as it might be possible this is the first element and it is not 0
    else ways=(ways+solve(i+1,vec,m,vec[i],dp))%mod;
    return dp[i][last]=ways;
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<int> vec(n);
    for(int i=0;i<n;i++){
        cin>>vec[i];
    }
    vector<vector<int>> dp(n,vector<int>(101,-1));
    cout<<solve(0,vec,m,0,dp);
}
