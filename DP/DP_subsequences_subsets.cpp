#include<bits/stdc++.h>
using namespace std;

//subset sum equal target
//DP SOLUTION
bool solve(int ind,vector<int>& arr, int target,vector<vector<int>> &dp){
    if(target==0) return true;
    if(ind==0) return target==arr[0];
    if(dp[ind][target]!=-1) return dp[ind][target];
    bool take=false;
    if(target-arr[ind]>=0) take=solve(ind-1,arr,target-arr[ind],dp);
    int nottake=solve(ind-1,arr,target,dp);
    return dp[ind][target]=take|nottake;
}
//TABULATION
bool isSubsetSum(vector<int>& arr, int k) {
    int n=arr.size();
    vector<vector<int>> dp(n,vector<int>(k+1,0));
    //return solve(n-1,arr,k,dp);
    for(int i=0;i<n;i++){
        dp[i][0]=1; //dp[i][sum=0]=true
    }
    //this condition is important as else there might be issue of out of bound error
    
    if(arr[0]<=k) dp[0][arr[0]]=1;
    for(int ind=1;ind<n;ind++){
        for(int target=1;target<=k;target++){
            int take=false;
            if(arr[ind]<=target) take=dp[ind-1][target-arr[ind]];
            int nottake=dp[ind-1][target];
            dp[ind][target]=take|nottake;
        }
    }
    return dp[n-1][k];
}
//SPACE OPTIMIZATION
bool isSubsetSum(vector<int>& arr, int k) {
    int n=arr.size();
    vector<int> dp(k+1,0);
    dp[0]=1; //dp[i][sum=0]=true
    //this condition is important as else there might be issue of out of bound error
    if(arr[0]<=k) dp[arr[0]]=1;
    for(int ind=1;ind<n;ind++){
        vector<int> temp(k+1,0);
        //remember to add this condition after creating temp vector
        temp[0]=true;
        for(int target=1;target<=k;target++){
            int take=false;
            if(arr[ind]<=target) take=dp[target-arr[ind]];
            int nottake=dp[target];
            temp[target]=take|nottake;
        }
        dp=temp;
    }
    return dp[k];
}

//partition equal subset sum
//if sum odd->not possible else target required=sum/2, this now becomes same as subset sum equal target
//memoisation 
bool solve(int ind,vector<int>& arr, int target,vector<vector<int>> &dp){
    if(target==0) return true;
    if(ind==0) return target==arr[0];
    if(dp[ind][target]!=-1) return dp[ind][target];
    bool take=false;
    if(target-arr[ind]>=0) take=solve(ind-1,arr,target-arr[ind],dp);
    int nottake=solve(ind-1,arr,target,dp);
    return dp[ind][target]=take|nottake;
}
bool canPartition(vector<int>& nums) {
    int sum=0;
    int n=nums.size();
    for(int i=0;i<n;i++){
        sum+=nums[i];
    }
    //edge case
    if(sum%2==1) return false; //we can't divive odd number into two equal parts
    int target=sum/2;
    vector<vector<int>> dp(n,vector<int>(target+1,-1));
    return solve(n-1,nums,target,dp);
}

//no. of ways such that target sum k
//Remember this code works only if we have positive values in array and if negative values are also present then we will have to expand dp size and check if value is negative or positive at each step
//also here we are considering there are no zero in array else they will also account for answer but won't be calculated in solve function
//if zeros are also present in array then we will count n=no. of zeroes and give final answer ((2^n)*ways_Calculated_using_solve_function)
//memoization
int solve(int ind,vector<int> arr,int target,vector<vector<int>> &dp){
    if(target==0) return 1;
    if(ind==0){
        if(target==arr[0]) return 1;
        return 0;
    }
    if(dp[ind][target]!=-1) return dp[ind][target];
    int take=0;
    if(arr[ind]<=target) take=solve(ind-1,arr,target-arr[ind],dp);
    int nottake=solve(ind-1,arr,target,dp);
    return take+nottake;
}

int countways(vector<int> arr,int target){
    int n=arr.size();
    vector<vector<int>> dp(n,vector<int>(target+1,-1));
    return solve(n-1,arr,target,dp);
}

//count subsets with given difference d
//simply do (sum-curr_sum)-(curr_sum)=d
// 2*curr_sum=sum-d , we need to solve for this new equality to hold true target

int main(){
    vector<int> vec={1,2,2,3,1,2,3,4};
    int ans=countways(vec,3);
    cout<<ans;
}
