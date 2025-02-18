#include<bits/stdc++.h>
using namespace std;

//*********************************************1D DP***********************************************

//climbing stairs
//if no memoization then TC->O(2^n)
//dp solution -TC->O(2*n) SC->O(n+n(recursion stack space))
int solve(int n,vector<int> &dp){
    if(n<=1) return dp[n]=1;
    if(dp[n]!=-1) return dp[n];
    return dp[n]=solve(n-1,dp)+solve(n-2,dp);
}
//tabulation solution
int climbStairs(int n) {
    if(n<=1) return 1;
    int n0=1;
    int n1=1;
    for(int i=2;i<=n;i++){
        int temp=n1;
        n1=n0+n1;
        n0=temp;
    }
    return n1;
    //vector<int> dp(n+1,-1);
    //int temp=solve(n,dp);
    //return dp[n];
}

//frogjump can jump 1 step or 2 step. Give minimum energy required to reach step n. Energy req for each jump is equal to abs difference between height of steps
//dp solution ->O(2*n) SC->O(n+n(recursive stack space))
int solve(int n,vector<int> heights,vector<int> &dp){
    if(n<=1) return dp[n]=0;
    if(dp[n]!=-1) return dp[n];
    int step1=solve(n-1,heights)+abs(heights[n-1]-heights[n-2]);
    int step2=INT_MAX;
    if(n>2) step2=solve(n-2,heights)+abs(heights[n-1]-heights[n-3]);
    return dp[n]=min(step1,step2);
}

int frogjump(int n,vector<int> heights){
    vector<int> dp(n+1,-1);
    int temp=solve(n,heights,dp);
    return dp[n];
}

//frog jump with k distance - here we can jump [1,k] jumps
//dp solution - TC->O(n*k) SC->O(n+n)
int solve(int n,vector<int> heights,vector<int> &dp,int k){
    if(n<=1) return dp[n]=0;
    if(dp[n]!=-1) return dp[n];
    int min_energy=INT_MAX;
    for(int i=1;i<=k;i++){
        if(n-i>0) min_energy=min(min_energy,solve(n-i,heights)+abs(heights[n-i]-heights[n-i-1]))
    }
    return dp[n]=min_energy;
}


//House robber - houses form linear arrangement (clear this out in the beginning in interviews whether such selection process is applied on linear or circular arrangement)
//dp approach
//TC->O(2*N) SC->O(n+n)
int solve(int index, vector<int> nums, vector<int> &dp){
    if(index==0) return dp[0]=nums[0];
    if(index<0) return 0;
    if(dp[index]!=-1) return dp[index];
    //rob
    int take=solve(index-2,nums,dp)+nums[index];
    //not rob
    int nottake=solve(index-1,nums,dp);
    return dp[index]=max(take,nottake);
}

int rob(vector<int>& nums) {
    vector<int> dp(nums.size(),-1);
    solve(nums.size()-1,nums,dp);
    return dp[nums.size()-1];
}
//TC->O(n) SC->O(1)
//tabulation and space optimization
int rob(vector<int>& nums) {
    // vector<int> dp(nums.size(),-1);
    // solve(nums.size()-1,nums,dp);
    // return dp[nums.size()-1];
    int n=nums.size();
    if(n==0) return 0;
    int rob0=0; //not robbing house0 
    int rob1=nums[0]; //robbing house0
    int ans=max(rob0,rob1);
    for(int i=1;i<n;i++){
        //previous optimal case
        int temp=max(rob1,rob0);
        //rob - take previous non robbing optimal case
        rob1=rob0+nums[i];
        //not rob - take previous optimal case
        rob0=temp;
    }
    //update answer with maximum of both cases
    ans=max(rob0,rob1);
    return ans;
}

//House robber 2 - houses form circular arrangement
//dp solution
//TC->O(2*2*N) SC->O(N)
int solve(int index, vector<int> nums, vector<vector<int>> &dp,int visn){
    if(index==0) {
        if(visn==0) return dp[visn][0]=nums[0];
        return dp[visn][0]=0;
    }
    if(index<0) return 0;
    if(dp[visn][index]!=-1) return dp[visn][index];
    //take
    int take=0;
    if(index==nums.size()-1) take=solve(index-2,nums,dp,1)+nums[index];
    else{
        take=solve(index-2,nums,dp,visn)+nums[index];
    }
    //not take
    int nottake=solve(index-1,nums,dp,visn);
    return dp[visn][index]=max(take,nottake);
}
//tabulation solution
//TC->O(2N) SC->O(1)
int rob(vector<int>& nums) {
    // int n=nums.size();
    // vector<vector<int>> dp(2,vector<int> (n,-1));
    // solve(nums.size()-1,nums,dp,0);
    
    // return max(dp[0][nums.size()-1],dp[1][nums.size()-1]);
    // vector<int> dp(nums.size(),-1);
    // solve(nums.size()-1,nums,dp);
    // return dp[nums.size()-1];
    int n=nums.size();
    if(n==0) return 0;
    if(n==1) return nums[0];
    int rob0=0; //not robbing house0 
    int rob1=nums[0]; //robbing house0
    int ans=max(rob0,rob1);
    //JUST TAKING MAXIMUM FOR [0,N-1] case
    for(int i=1;i<n-1;i++){
        //previous optimal case
        int temp=max(rob1,rob0);
        //rob - take previous non robbing optimal case
        rob1=rob0+nums[i];
        //not rob - take previous optimal case
        rob0=temp;
    }
    //update answer with maximum of both cases
    ans=max(rob0,rob1);

    //TAKING MAXIMUM FOR [1,N] case
    rob0=0; //not robbing house1
    rob1=nums[1]; //robbing house1
    int ans2=max(rob0,rob1);
    for(int i=2;i<n;i++){
        //previous optimal case
        int temp=max(rob1,rob0);
        //rob - take previous non robbing optimal case
        rob1=rob0+nums[i];
        //not rob - take previous optimal case
        rob0=temp;
    }
    ans2=max(rob0,rob1);
    ans=max(ans,ans2);
    return ans;
}
//memoization (2 times function call)
//remember the edge case when only one element in array
int solve(int index, vector<int> nums, vector<int> &dp){
    if(index==0) {
        return dp[0]=max(0,nums[0]);
    }
    if(index<0) return 0;
    if(dp[index]!=-1) return dp[index];
    //take
    int take=solve(index-2,nums,dp)+nums[index];
    //not take
    int nottake=solve(index-1,nums,dp);
    return dp[index]=max(take,nottake);
}
int rob(vector<int>& nums) {
    int n=nums.size();
    
    //EDGE CASE
    if(n==1) return nums[0];
    
    vector<int> dp(n,-1);
    int ans1=solve(n-2,nums,dp);
    vector<int> dp2(n,-1);
    //need to handle edge case when only one element
    // int temp=nums[0];
    // nums[0]=INT_MIN;
    vector<int> vec(nums.begin()+1,nums.end());
    int ans2=solve(n-2,vec,dp2);
    // nums[0]=temp;
    cout<<ans1<<" "<<ans2;
    return max(ans1,ans2);
}

int main(){
    
}
