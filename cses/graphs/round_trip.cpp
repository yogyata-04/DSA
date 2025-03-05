#include<bits/stdc++.h>
using namespace std;

bool dfs(int i,vector<vector<int>> &adj,vector<int> &vis,vector<int> &path,vector<int> &ans,int parent){
    vis[i]=1;
    path.push_back(i);
    for(auto it:adj[i]){
        if(!vis[it]){
            if(dfs(it,adj,vis,path,ans,i)){return true;}
        }
        else if(it!=parent){
            path.push_back(it); ans=path;
            return true;
        }
    }
    path.pop_back();
    return false;
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
            if(dfs(i,adj,vis,ans,ans,-1)) {
                int k=ans.size();
                //I made mistake of taking entire answer which included cycle +extra initial part also. So, take care of that thing
                int start=-1;
                for(int j=0;j<k;j++){
                    if(ans[j]==ans[k-1]) {start=j;break;}
                }
                cout<<k-start<<endl;
                for(int j=start;j<k;j++){
                    cout<<ans[j]<<" ";
                }
                return 0;
            }
        }
    }
    cout<<"IMPOSSIBLE";
}
