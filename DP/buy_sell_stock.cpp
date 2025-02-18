//Best Time to Buy and Sell Stock - we can buy and sell only once
//simply buy stock at min. price till curr index and keep track of max. profit at each index one can have by taking difference of curr index stock and previous bought stock
//TC->O(n) SC->O(1)
int maxProfit(vector<int>& vec) {
    int n=vec.size();
    int profit=0;
    int last_buy=vec[0];
    for(int i=0;i<n;i++){
        profit=max(profit,vec[i]-last_buy);
        last_buy=min(last_buy,vec[i]);
    }
    return profit;
}

//Best Time to Buy and Sell Stock II - here we can buy and sell any no. of times. So, DP will be applied we will have to explore all possible ways (BSBS POSSIBLE BSSB NOT POSSIBLE)
//memoization
//TC->O(2*n) SC->O(2*N+N(recursion stack space));
int solve(int ind,int n,vector<int> &prices,int op,vector<vector<int>> &dp){
    if(ind==n) return 0;
    //we will buy/not buy
    if(dp[op][ind]!=-1) return dp[op][ind];
    int profit=0;
    if(op){
        profit=max(solve(ind+1,n,prices,!op,dp)-prices[ind],0+solve(ind+1,n,prices,op,dp));
    }
    else {
        profit=max(solve(ind+1,n,prices,!op,dp)+prices[ind],0+solve(ind+1,n,prices,op,dp));
    }
    return dp[op][ind]=profit;
}

int maxProfit(vector<int>& prices) {
    int n=prices.size();
    vector<vector<int>> dp(2,vector<int>(n,-1));
    return solve(0,n,prices,1,dp); //1->buy 0->sell
}
//tabulation approach 
//TC->O(2*n) SC->O(2*n)
int maxProfit(vector<int>& prices) {
    int n=prices.size();
    vector<vector<int>> dp(2,vector<int>(n+1,-1));
    //return solve(n-1,prices,0,dp); //1->buy 0->sell
    //base condition - any operation on out of bound index will be invalid so we will have 0 profit
    dp[0][n]=0;
    dp[1][n]=0;
    for(int ind=n-1;ind>=0;ind--){
        for(int buy=0;buy<=1;buy++){
            int profit=0;
            if(buy){
                profit=max(dp[!buy][ind+1]-prices[ind],0+dp[buy][ind+1]);
            }
            else{
                profit=max(dp[!buy][ind+1]+prices[ind],0+dp[buy][ind+1]);
            }
            dp[buy][ind]=profit;
        }
    }
    return dp[1][0];
}
//space optimization
//TC->O(2*n) SC->O(1)
int maxProfit(vector<int>& prices) {
  int n=prices.size();
  vector<int> dp(2);
  //base condition
  dp[0]=0;
  dp[1]=0;
  for(int ind=n-1;ind>=0;ind--){
      vector<int> temp(2,0);
      for(int buy=0;buy<=1;buy++){
          int profit=0;
          cout<<buy<<" "<<dp[buy]<<" "<<!buy<<" "<<dp[!buy]<<endl;
          if(buy){
              profit=max(dp[!buy]-prices[ind],0+dp[buy]);
          }
          else{
              profit=max(dp[!buy]+prices[ind],0+dp[buy]);
          }
          temp[buy]=profit;
      }
      dp=temp;
  }
  return dp[1];
}

//Best Time to Buy and Sell Stock III - we have upper limit for transactions, ie, 2 (so BSBS possible but not BSBSB..)
//This solution works only for 179/214 but if we have 3d dp and not changing anything, we are getting correct answer - need to figure out why?
//DON'T THINK THIS WAY
int solve(int ind,int n,vector<int> &prices,int op,vector<vector<int>> &dp,int cnt){
    if(cnt>=2) return 0;
    if(ind==n) return 0;
    //we will buy/not buy
    if(dp[op][ind]!=-1) return dp[op][ind];
    int profit=0;
    if(op==1){
        //buy or not buy
        profit=max(solve(ind+1,n,prices,!op,dp,cnt)-prices[ind],0+solve(ind+1,n,prices,op,dp,cnt));
    }
    else{
        //sell or not sell
        //incrementing count when two transactions completed
        profit=max(solve(ind+1,n,prices,!op,dp,cnt+1)+prices[ind],0+solve(ind+1,n,prices,op,dp,cnt));
    }
    return dp[op][ind]=profit;
}

int maxProfit(vector<int>& prices) {
    int n=prices.size();
    vector<vector<int>> dp(2,vector<int>(n,-1));
    return solve(0,n,prices,1,dp,0);
}
//using 3d dp memoization
//TC->O(3*2*n) SC->O(3*2*n)
int solve(int ind,int n,vector<int> &prices,int op,vector<vector<vector<int>>> &dp,int cnt){
    if(cnt>=2) return 0;
    if(ind==n) return 0;
    //we will buy/not buy
    if(dp[cnt][op][ind]!=-1) return dp[cnt][op][ind];
    int profit=0;
    if(op==1){
        //buy or not buy
        profit=max(solve(ind+1,n,prices,!op,dp,cnt)-prices[ind],0+solve(ind+1,n,prices,op,dp,cnt));
    }
    else {
        //sell or not sell
        //incrementing count when two transactions completed
        profit=max(solve(ind+1,n,prices,!op,dp,cnt+1)+prices[ind],0+solve(ind+1,n,prices,op,dp,cnt));
    }
    return dp[cnt][op][ind]=profit;
}

int maxProfit(vector<int>& prices) {
    int n=prices.size();
    vector<vector<vector<int>>> dp(3,vector<vector<int>>(2,vector<int>(n,-1)));
    return solve(0,n,prices,1,dp,0);
}
//we can solve using 2d dp of size 4*n 
//TC->O(2*n) SC->O(4*n)
int solve(int ind,int n,vector<int> &prices,vector<vector<int>> &dp,int cnt){
    if(cnt>=4) return 0;
    if(ind==n) return 0;
    //we will buy/not buy
    if(dp[cnt][ind]!=-1) return dp[cnt][ind];
    int profit=0;
    if(cnt%2==0){
        //buy or not buy
        profit=max(solve(ind+1,n,prices,dp,cnt+1)-prices[ind],0+solve(ind+1,n,prices,dp,cnt));
    }
    else {
        //sell or not sell
        //incrementing count when two transactions completed
        profit=max(solve(ind+1,n,prices,dp,cnt+1)+prices[ind],0+solve(ind+1,n,prices,dp,cnt));
    }
    return dp[cnt][ind]=profit;
}

int maxProfit(vector<int>& prices) {
    int n=prices.size();
    vector<vector<int>> dp(4,vector<int>(n,-1)); //cnt,ind //if cnt even buy else sell
    return solve(0,n,prices,dp,0);
}
//tabulation
int maxProfit(vector<int>& prices) {
    int n=prices.size();
    vector<vector<int>> dp(5,vector<int>(n+1,0)); //cnt,ind //if cnt even buy else sell
    for(int ind=n-1;ind>=0;ind--){
        for(int cnt=3;cnt>=0;cnt--){
            int profit=0;
            if(cnt%2==0){
                //buy or not buy
                profit=max(dp[cnt+1][ind+1]-prices[ind],0+dp[cnt][ind+1]);
            }
            else {
                //sell or not sell
                //incrementing count when two transactions completed
                profit=max(dp[cnt+1][ind+1]+prices[ind],0+dp[cnt][ind+1]);
            }
            dp[cnt][ind]=profit;
        }
    }
    return dp[0][0];
}
//space optimization
int maxProfit(vector<int>& prices) {
    int n=prices.size();
    vector<int> dp(5,0); //cnt,ind //if cnt even buy else sell
    for(int ind=n-1;ind>=0;ind--){
        vector<int> temp(5,0);
        for(int cnt=3;cnt>=0;cnt--){
            int profit=0;
            if(cnt%2==0){
                //buy or not buy
                profit=max(dp[cnt+1]-prices[ind],0+dp[cnt]);
            }
            else {
                //sell or not sell
                //incrementing count when two transactions completed
                profit=max(dp[cnt+1]+prices[ind],0+dp[cnt]);
            }
            temp[cnt]=profit;
        }
        dp=temp;
    }
    return dp[0];
}

//Best Time to Buy and Sell Stock IV - here we can do atmost k transactions
//memoization
int solve(int ind,int n,vector<int> &prices,int op,vector<vector<vector<int>>> &dp,int cnt){
    if(cnt<=0) return 0;
    if(ind==n) return 0;
    //we will buy/not buy
    if(dp[cnt][op][ind]!=-1) return dp[cnt][op][ind];
    int profit=0;
    if(op==1){
        //buy or not buy
        profit=max(solve(ind+1,n,prices,!op,dp,cnt)-prices[ind],0+solve(ind+1,n,prices,op,dp,cnt));
    }
    else {
        //sell or not sell
        //incrementing count when two transactions completed
        profit=max(solve(ind+1,n,prices,!op,dp,cnt-1)+prices[ind],0+solve(ind+1,n,prices,op,dp,cnt));
    }
    return dp[cnt][op][ind]=profit;
}

int maxProfit(int k,vector<int>& prices) {
    int n=prices.size();
    vector<vector<vector<int>>> dp(k+1,vector<vector<int>>(2,vector<int>(n,-1)));
    return solve(0,n,prices,1,dp,k);
}
//tabulation
