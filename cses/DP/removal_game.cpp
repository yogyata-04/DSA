#include<bits/stdc++.h>
using namespace std;
 
//this is a good question
//initially I approached it like player 1 can move anyways and player2 will choose maximum element
//which is wrong player2 will minimize player1 score instead of maximising it's own
long long solve(int i,int j,vector<long long> &vec,vector<vector<long long>> &dp){
    if(i>j){
        return 0;
    }
    if(dp[i][j]!=-1) return dp[i][j];
    // Player 1 picks `i` or `j` and Player 2 plays optimally to minimize P1's future score
    long long pick_left=vec[i]+min(solve(i+2,j,vec,dp),solve(i+1,j-1,vec,dp));
    long long pick_right=vec[j]+min(solve(i,j-2,vec,dp),solve(i+1,j-1,vec,dp));
    return dp[i][j]=max(pick_left,pick_right);
}
 
int main(){
   int n;
   cin>>n;
   vector<long long> vec(n);
   for(int i=0;i<n;i++){
       cin>>vec[i];
   }
   vector<vector<long long>> dp(n,vector<long long>(n,-1));
   cout<<solve(0,n-1,vec,dp);
}
