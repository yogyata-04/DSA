#include<bits/stdc++.h>
using namespace std;

int mod=1e9+7;

int solve(int x,int y,vector<vector<char>> &grid,vector<vector<int>> &dp) {
	if(x>=grid.size() || x<0 || y>=grid.size() || y<0 || grid[x][y]=='*'){
	    return 0;
	}
	int n=grid.size();
	if(x==n-1 && y==n-1) return 1;
	if(dp[x][y]!=-1) return dp[x][y];
	int right=solve(x,y+1,grid,dp);
	int down=solve(x+1,y,grid,dp);
	return dp[x][y]=(right+down)%mod;
}

int main() {
	int n;
	cin>>n;
	vector<vector<char>> grid(n,vector<char>(n));
	for(int i=0;i<n;i++){
	    for(int j=0;j<n;j++){
	        cin>>grid[i][j];
	    }
	}
	vector<vector<int>> dp(n,vector<int>(n,-1));
	cout<<solve(0,0,grid,dp);
}
