#include<bits/stdc++.h>
using namespace std;

int mod=1e9+7;

int solve(int n,vector<int> &dp) {
	if(n==0) return 0;
	if(dp[n]!=-1) return dp[n];
	int temp=n;
	int ans=INT_MAX;
	while(temp) {
		int dig=temp%10;
		//remember this base condition that we will not subtract 0 as it will lead to infinte loop
    	if (dig!=0)	ans=min(ans,solve(n-dig,dp)+1);
		temp/=10;
	}
	return dp[n]=ans;
}

int main() {
	int n;
	cin>>n;
	vector<int> dp(n+1,-1);
	cout<<solve(n,dp);
}
