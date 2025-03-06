#include<bits/stdc++.h>
using namespace std;

void solve(int i,vector<int> &coins, int curr_sum,set<int> &st,vector<vector<bool>> &dp){
    if(i==coins.size()){
        return;
    }
  //keep track of visited states so that we do not follow same path again 
    if(dp[i][curr_sum]==true) return;
    dp[i][curr_sum]=true;
    //take current
    st.insert(curr_sum+coins[i]);
    solve(i+1,coins,curr_sum+coins[i],st,dp);
    //not take current
    solve(i+1,coins,curr_sum,st,dp);
}

int main(){
   int n;
   cin>>n;
   int sum=0;
   vector<int> coins(n);
   for(int i=0;i<n;i++){
       cin>>coins[i];
       sum+=coins[i];
   }
   set<int> st;
   vector<vector<bool>> dp(n,vector<bool>(sum+1,false));
   solve(0,coins,0,st,dp);
   cout<<st.size()<<endl;
   for(auto it:st){
       cout<<it<<" ";
   }
}
