#include<bits/stdc++.h>
using namespace std;

int mod=1e9+7;

//getting tle using this method
int solve(int i,int money,vector<int> &price,vector<int> &pages,vector<vector<int>> &dp) {
	if(money==0 || i>=price.size()){
	    return 0;
	}
	if(dp[i][money]!=-1) return dp[i][money];
	int take=0;
	if(price[i]<=money)take=solve(i+1,money-price[i],price,pages,dp)+pages[i];
	int nottake=solve(i+1,money,price,pages,dp);
	return dp[i][money]=max(take,nottake);
}

int main() {
	int n,x;
	cin>>n>>x;
    vector<int> price(n);
    vector<int> pages(n);
    for(int i=0;i<n;i++){
        cin>>price[i];
    }
    for(int i=0;i<n;i++){
        cin>>pages[i];
    }
    vector<vector<int>> dp(n,vector<int>(x+1,-1));
    cout<<solve(0,x,price,pages,dp);
}
