#include<bits/stdc++.h>
using namespace std;
 
long long mod=1e9+7;
 
//getting TLE for few testcases using dfs due to stack overflow and all 
void dfs(int i,vector<vector<int>> &adj,long long &cnt){
    if(i==adj.size()-1) {cnt=(cnt+1)%mod;return;}
    for(auto it:adj[i]){
        //here if I use visited condition then some cases will be missed
        //visited works when we want to detect cycle and we are guaranteed that no cycle exists
        dfs(it,adj,cnt);
    }
}

//need to practice dp on graphs
//here we can do toposort 

int main(){
    int n,m;
    cin>>n>>m;
    int a,b;
    vector<vector<int>> adj(n+1);
    for(int i=0;i<m;i++){
        cin>>a>>b;
        adj[a].push_back(b);
    }
    
    long long ans=0;
    dfs(1,adj,ans);
    cout<<ans;
}
