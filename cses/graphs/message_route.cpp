#include<bits/stdc++.h>
using namespace std;

//simple bfs for shortest path
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
    queue<int> q;
    q.push(1);
    vis[1]=1;
    int flag=0;
    vector<int> parent(n+1);
    while(!q.empty()){
        
        int k=q.size();
        while(k--){
            int front=q.front();
            q.pop();
            for(auto it:adj[front]){
                if(it==n){
                    parent[it]=front;
                    flag=1;
                    break;
                }
                if(!vis[it]){
                    parent[it]=front;
                    q.push(it);
                    vis[it]=1;
                }
            }
            if(flag==1) break;
        }
        if(flag==1) break;
    }
    
    if(flag==0) cout<<"IMPOSSIBLE";
    else{
        
        vector<int> ans;
        ans.push_back(n);
        int node=n;
        while(node!=1){
            ans.push_back(parent[node]);
            node=parent[node];
        }
        reverse(ans.begin(),ans.end());
        cout<<ans.size()<<endl;
        for(auto it:ans){
            cout<<it<<" ";
        }
    }
    
}
