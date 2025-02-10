#include<bits/stdc++.h>
using namespace std;

//*********************************************2D DP***********************************************

//Ninja training
//TC->O(N*4*4) +SC->O(N*4)
int dp(int n,vector<vector<int>> points,int last,vector<vector<int>> dp){
    if(n<0){
        return 0;
    }
    if(dp[n][last]!=-1) return dp[n][last];
    //0, 1, 2, 3(can do anything next)
    int ans=0;
    for(int i=0;i<4;i++){
        if(i==3) ans=max(ans,dp(n-1,points,i)); //this will be useful when we have negative points included
        if(last==i) continue;
        else ans=max(ans,dp(n-1,points,i)+points[n][i]);
    }
    return dp[n][last]=ans;
}
int solve_ninjatraining(int n,vector<vector<int>> points){
    vector<int> dp(4,vector<int>(n,-1));
    int temp=dp(n-1,points,3,dp); //3->we can do anything next
    return dp[n-1][3];
}

//tabulation approach
//TC->O(N*4*3) SC->O(N*4)
int solve_ninjatraining_tab(int n,vector<vector<int>> points){
    vector<int> dp(4,vector<int>(n,-1));
    // int temp=dp(n-1,points,3,dp); //3->we can do anything next
    // return dp[n-1][3];
    // dp[0][0]=max(points[0][1],points[0][2]);
    // dp[0][1]=max(points[0][0],points[0][2]);
    // dp[0][2]=max(points[0][0],points[0][1]);
    // dp[0][3]=max(points[0][0],max(points[0][1],points[0][2]));
    // for(int day=1;day<n;day++){
    //     for(int last=0;last<4;last++){
    //         dp[day][last]=0;
    //         for(task=0;task<3;task++){
    //             if(task==last) continue;
    //             int point=points[day][task]+dp[day-1][task]; //for each task on the current day, we need to combine it with the best possible result from a valid task on the previous day.
    //             dp[day][last]=max(dp[day][last],point)
    //         }
    //     }
    // }
    // return dp[n-1][3];
    
    //TC->O(n*4*3) SC->O(1)
    vector<int> dp(4,0);
    dp[0]=max(points[0][1],points[0][2]);
    dp[1]=max(points[0][0],points[0][2]);
    dp[2]=max(points[0][0],points[0][1]);
    dp[3]=max(points[0][0],max(points[0][1],points[0][2]));
    for(int day=1;day<n;day++){
        vector<int> temp(4,0);
        for(int last=0;last<4;last++){
            for(task=0;task<3;task++){
                if(task==last) continue;
                int point=points[day][task]+dp[task];
                temp[last]=max(dp[day][last],point)
            }
        }
        dp=temp;
    }
    return dp[3];
}

//unique paths
//if no obstacles we can answer it like fact(n-1+m-1)/fact(n-1)*fact(m-1)
//using dp approach
//TC->O(N*M) SC->O(N*M)+O(n-1+m-1)(recursion stack)
int solve(int row,int col,vector<vector<int>> &dp){
    if(row<0 || col<0) return 0;
    if(row==0 && col==0) return dp[0][0]=1;
    if(dp[row][col]!=-1) return dp[row][col];
    //moving up
    int up=solve(row-1,col,dp);
    //moving left
    int left=solve(row,col-1,dp);
    return dp[row][col]=up+left;
}

int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m,vector<int>(n,-1));
    int temp=solve(m-1,n-1,dp);
    return dp[m-1][n-1];
}
//using tabulation approach
//TC->O(m*n) SC->O(m*n)
int uniquePaths_tabulation(int m,int n){
    vector<vector<int>> dp(m,vector<int>(n,-1));
    dp[0][0]=1;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(i==0 && j==0) dp[0][0]=1;
            else{
                int up=0,left=0;
                if(j-1>0) left=dp[i][j-1];
                if(i-1>0) up=dp[i-1][j];
                dp[i][j]=left+up;
            }
        }
    }
    return dp[m-1][n-1];
}
//space optimization
int uniquePaths_tabulation(int m,int n){
    vector<int> dp(n,-1);
    dp[0]=1;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(i==0 && j==0) dp[0][0]=1;
            else{
                int up=0,left=0;
                if(j-1>0) left=dp[i][j-1];
                if(i-1>0) up=dp[i-1][j];
                dp[i][j]=left+up;
            }
        }
    }
    return dp[m-1][n-1];
}

//Promise to myself:I am focusing currently on memoization only and not tabulation. Once I finish up things then I will try tabulation

//unique paths 2 (with obstacles) - now tell all possible paths possible
int solve(int row,int col,vector<vector<int>> &dp,vector<vector<int>> &grid){
    if(row<0 || col<0 || grid[row][col]==1) return 0;
    if(row==0 && col==0) return dp[0][0]=1;
    if(dp[row][col]!=0) return dp[row][col];
    //moving up
    int up=solve(row-1,col,dp,grid);
    //moving left
    int left=solve(row,col-1,dp,grid);
    return dp[row][col]=up+left;
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m=obstacleGrid.size();
    int n=obstacleGrid[0].size();
    vector<vector<int>> dp(m,vector<int>(n,0));
    int temp=solve(m-1,n-1,dp,obstacleGrid);
    return dp[m-1][n-1];
}

//minimum path sum in grid - to return minimum sum
int solve(int row,int col,vector<vector<int>> &dp,vector<vector<int>> &grid){
    if(row<0 || col<0) return INT_MAX;
    if(row==0 && col==0) return dp[0][0]=grid[0][0];
    if(dp[row][col]!=0) return dp[row][col];
    //moving up
    int up=solve(row-1,col,dp,grid);
    //moving left
    int left=solve(row,col-1,dp,grid);
    return dp[row][col]=min(up,left)+grid[row][col];
}

int minPathSum(vector<vector<int>>& obstacleGrid) {
    int m=obstacleGrid.size();
    int n=obstacleGrid[0].size();
    vector<vector<int>> dp(m,vector<int>(n,0));
    int temp=solve(m-1,n-1,dp,obstacleGrid);
    return dp[m-1][n-1];
}

int main(){
    
}
