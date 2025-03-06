#include<bits/stdc++.h>
using namespace std;

//this is a good question
//initially I approached it like player 1 can move anyways and player2 will choose maximum element
//which is wrong player2 will minimize player1 score instead of maximising it's own

//getting tle in 50% testcases need to do tabulation
int solve(int i,int j,vector<int> vec,vector<vector<int>> &dp){
    if(i>j){
        return 0;
    }
    if(dp[i][j]!=-1) return dp[i][j];
    // Player 1 picks `i` or `j` and Player 2 plays optimally to minimize P1's future score
    int pick_left=vec[i]+min(solve(i+2,j,vec,dp),solve(i+1,j-1,vec,dp));
    int pick_right=vec[j]+min(solve(i,j-2,vec,dp),solve(i+1,j-1,vec,dp));
    return dp[i][j]=max(pick_left,pick_right);
}

int main(){
   int n;
   cin>>n;
   vector<int> vec(n);
   for(int i=0;i<n;i++){
       cin>>vec[i];
   }
   vector<vector<int>> dp(n,vector<int>(n,-1));
   cout<<solve(0,n-1,vec,dp);
}
