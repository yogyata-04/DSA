#include<bits/stdc++.h>
using namespace std;

//*********************************************2D DP***********************************************

//Ninja training
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
int solve_ninjatraining_tab(int n,vector<vector<int>> points){
    // vector<int> dp(4,vector<int>(n,-1));
    // int temp=dp(n-1,points,3,dp); //3->we can do anything next
    // return dp[n-1][3];
    int task0=points[0][0];
    int task1=points[0][1];
    int task2=points[0][2];
    int task3=0;
    vector<int> task={task0,task1,task2,task3};
    int ans=max(task[0],task[1],task[2],task[3]);
    for(int i=1;i<n;i++){
        for(int j=0;j<4;j++){
            int sum=0;
            for(int k=0;k<4;k++){
                if(k==j){
                    continue;
                }
                sum+=points[i][k];
            }
            task[j]=max(task[j],sum);
        }
    }
}

int main(){
    
}
