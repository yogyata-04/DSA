//27 Feb 2025
//1749. Maximum Absolute Sum of Any Subarray
//You are given an integer array nums. The absolute sum of a subarray [numsl, numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).
//Return the maximum absolute sum of any (possibly empty) subarray of nums.
//Note:Here initialise min and max sum with 0 and not INT_MAX and INT_MIN
int maxAbsoluteSum(vector<int>& nums) {
    int n=nums.size();
    int mini_sum=0;
    int maxi_sum=0;
    int sum=0;
    for(int i=0;i<n;i++){
        sum+=nums[i];
        mini_sum=min(mini_sum,sum);
        maxi_sum=max(maxi_sum,sum);
    }
    return maxi_sum-mini_sum;
}
//53. Maximum Subarray
//Given an integer array nums, find the subarray with the largest sum, and return its sum.
int maxSubArray(vector<int>& nums) {
    int n=nums.size();
    int ans=nums[0];
    int sum=0;
    for(int i=0;i<n;i++){
        sum+=nums[i];
        ans=max(ans,sum);
        if(sum<0){ 
            sum=0;
        }
    }
    return ans;
}

 
