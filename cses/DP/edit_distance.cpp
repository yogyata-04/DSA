#include<bits/stdc++.h>
using namespace std;

int solve(int i,int j,string &str1, string &str2,vector<vector<int>> &dp){
    if(i==str1.size() || j==str2.size()){
        int rem1=str1.size()-i;
        int rem2=str2.size()-j;
        return max(rem1,rem2);
    }
    if(dp[i][j]!=-1) return dp[i][j];
    //condition 1 i==j
    int ans=INT_MAX;
    if(str1[i]==str2[j]){
        ans=min(ans,solve(i+1,j+1,str1,str2,dp));
    }
    else{
        //move to next of str1
        ans=min(ans,1+solve(i+1,j,str1,str2,dp));
        //move to next of str2
        ans=min(ans,1+solve(i,j+1,str1,str2,dp));
        //move to next of str1 and str2 and change current
        ans=min(ans,1+solve(i+1,j+1,str1,str2,dp));
    }
    return dp[i][j]=ans;
}

int main(){
   string str1,str2;
   cin>>str1>>str2;
   int n=str1.size();
   int m=str2.size();
   vector<vector<int>> dp(n,vector<int>(m,-1));
   cout<<solve(0,0,str1,str2,dp)<<endl;
   
}
