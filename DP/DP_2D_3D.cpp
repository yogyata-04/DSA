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


//minimum path sum in a triangular grid
//dp solution - TC->O((n*(n-1)/2)*2) SC->O(n^2)
int solve(int row,int col,vector<vector<int>> triangle,vector<vector<int>> &dp,int n){
    if(col>row || row>n) return INT_MAX;
    if(row==n) {
        return 0;
    }
    if(dp[row][col]!=-1) return dp[row][col];
    //starting from top
    //move downright
    int downright=INT_MAX;
    if(col<=row) downright=solve(row+1,col+1,triangle,dp,n);
    //move dowm
    //take care here we will not have right instead we will have down as specified in question
    int down=solve(row+1,col,triangle,dp,n);

    return dp[row][col]=min(downright,down)+triangle[row][col];
}
int minimumTotal(vector<vector<int>>& triangle) {
    int n=triangle.size();
    vector<vector<int>> dp(n,vector<int> (n,-1));
    //we just want to reach last row
    int temp=solve(0,0,triangle,dp,n);
    //here remember we are returning temp;
    return temp;
}

//can also do it like
int solve(int row,int col,vector<vector<int>> triangle,vector<vector<int>> &dp,int n){
    if(col>row || row>n) return INT_MAX;
    if(row==n-1) {
        return triangle[row][col];
    }
    if(dp[row][col]!=-1) return dp[row][col];
    //starting from top
    //move downright
    int downright=INT_MAX;
    if(col<=row) downright=solve(row+1,col+1,triangle,dp,n);
    //move dowm
    //take care here we will not have right instead we will have down as specified in question
    int down=solve(row+1,col,triangle,dp,n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    return dp[row][col]=min(downright,down)+triangle[row][col];
}



int minimumTotal(vector<vector<int>>& triangle) {
    int n=triangle.size();
    vector<vector<int>> dp(n,vector<int> (n,-1));
    //we just want to reach last row
    int temp=solve(0,0,triangle,dp,n);
    return temp;
}

//Minimum falling path sum
//DP approach TC->O(N^2*3) SC->O(N^2+O(N)(recursion stack space))
int solve(int row,int col,vector<vector<int>> &matrix,int n,vector<vector<int>> &dp){
    if(row>=n || col<0 || col>=n) return INT_MAX;
    if(row==n-1){
        return matrix[row][col];
    }
    if(dp[row][col]!=-1) return dp[row][col];
    //move down
    int down=solve(row+1,col,matrix,n,dp);
    //move downleft
    int downleft=solve(row+1,col-1,matrix,n,dp);
    //move downright
    int downright=solve(row+1,col+1,matrix,n,dp);
    return dp[row][col]=min(down,min(downleft,downright)) + matrix[row][col];
}
int minFallingPathSum(vector<vector<int>>& matrix) {
    int n=matrix.size();
    vector<vector<int>> dp(n,vector<int>(n,-1));
    int ans=INT_MAX;
    for(int i=0;i<n;i++){
        ans=min(ans,solve(0,i,matrix,n,dp));
    }
    return ans;
}

//3D dp
//Alice and bob problem for maximum sum Alice(0,0) Bob(0,m-1)
//we can work with even one row instead of rowa and rowb
//without memoisation TC->O(3^n*3^n) SC->O(n)(recursion stack space)
//After memoization TC->O(N*M*M*9) SC->O(N*M*M)
int solve(int rowa,int cola,int rowb,int colb,vector<vector<int>> grid,int n,int m,vector<vector<vector<int>>> &dp){
    if(rowa>=n || rowb>=n || cola<0 || cola>=m || colb<0 || colb>=m) return INT_MIN;
    if(rowa==n-1 && rowb==n-1){
        if(cola==colb){
            return grid[rowa][cola];
        }
        return grid[rowa][cola]+grid[rowb][colb];
    }
    if(dp[rowa][cola][colb]!=-1) return dp[rowa][cola][colb];
    //storing movements column wise , now need of row as it will always increment by 1
    vector<int> dy={-1,0,1};
    int maxi=INT_MIN;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(cola==colb){
                maxi=max(maxi,grid[rowa][cola]+solve(rowa+1,cola+dy[i],rowb+1,colb+dy[j],grid,n,m,dp));
            }
            else{
                maxi=max(maxi,grid[rowa][cola]+grid[rowb][colb]+solve(rowa+1,cola+dy[i],rowb+1,colb+dy[j],grid,n,m,dp));
            }
        }
    }
    return dp[rowa][cola][colb]=maxi;
}

int alicebobmax(vector<vector<int>> grid){
    int n=grid.size();
    int m=grid[0].size();
    //row*alicecol*bobcol n*m*m
    vector<vector<vector<int>>> dp(n,vector<vector<int>>(m,vector<int>(m,-1)));
    int temp=solve(0,0,0,m-1,grid,n,m,dp);
    return temp;
}

int main(){
    vector<vector<int>> vec={{2,3,1,2},{3,4,2,2},{5,6,3,5}};
    cout<<alicebobmax(vec);
}

int main(){
    
}
