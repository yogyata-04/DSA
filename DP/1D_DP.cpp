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
