#include<bits/stdc++.h>
using namespace std;

//based on concept of bipartite
bool bfs(int i,vector<vector<int>> &adj,vector<int> &vis){
    queue<pair<int,int>> q;//node,parent
    q.push({i,-1});
    int curr=1;
    vis[i]=curr;
    while(!q.empty()){
        curr=!curr;
        int k=q.size();
        while(k--){
            auto front=q.front();
            q.pop();
            int node=front.first;
            int parent=front.second;
            for(auto it:adj[node]){
                if(vis[it]==-1){
                    q.push({it,node});
                    vis[it]=curr;
                }
                else if(vis[it]==vis[node]){
                    return false;
                }
            }
            
        }
    }
    return true;
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
    vector<int> vis(n+1,-1);
    for(int i=1;i<=n;i++){
        if(vis[i]==-1){
            //in vis only we can store team 
            bool flag=bfs(i,adj,vis);
            if(flag==false) {cout<<"IMPOSSIBLE";return 0;}
        }
    }
    for(int i=1;i<=n;i++){
        cout<<vis[i]+1<<" ";
    }
}
