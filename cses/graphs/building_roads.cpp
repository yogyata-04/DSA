#include<bits/stdc++.h>
using namespace std;

//solved using concept of connected components
void dfs(int i,vector<vector<int>> &adj,vector<int> &vis){
    vis[i]=1;
    for(auto it:adj[i]){
        if(!vis[it]){
            dfs(it,adj,vis);
        }
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> vec(m,vector<int>(2));
    vector<vector<int>> adj(n+1);
    for(int i=0;i<m;i++){
        cin>>vec[i][0];
        cin>>vec[i][1];
        adj[vec[i][0]].push_back(vec[i][1]);
        adj[vec[i][1]].push_back(vec[i][0]);
    }
    vector<int> vis(n+1,0);
    vector<int> ans;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            ans.push_back(i);
            dfs(i,adj,vis);
        }
    }
    int k=ans.size();
    cout<<k-1<<endl;
    //edge case size of answer should be greater than 1
    if(k>1){
        for(int i=0;i<k-1;i++){
            cout<<ans[i]<<" "<<ans[i+1]<<endl;
        }
    }
    //min_connections=ans.size()-1;
}
