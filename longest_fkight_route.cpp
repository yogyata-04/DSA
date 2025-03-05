#include<bits/stdc++.h>
using namespace std;
 
//getting TLE and runtime error for few testcases using dfs due to stack overflow and all 
void dfs(int i,vector<vector<int>> &adj, vector<int> path,vector<int> &ans){
    path.push_back(i);
    if(i==adj.size()-1){
        if(ans.size()<path.size()){
            ans=path;
        }
    }
    for(auto it:adj[i]){
        //here if I use visited condition then some cases will be missed
        //visited works when we want to detect cycle and we are guaranteed that no cycle exists
        dfs(it,adj,path,ans);
    }
    path.pop_back();
}

//using dijkstra
//we will have weight as -1 instead of 1 and we will minimise path length, but actually maximizing it which is required
void dijkstra(vector<vector<int>> &adj){
    int n=adj.size()-1;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;//cost,node
    pq.push({0,1});
    vector<int> parent(n+1,-1);
    vector<int> dis(n+1,INT_MAX);
    while(!pq.empty()){
        auto front=pq.top();
        pq.pop();
        int node=front.second;
        int cost=front.first;
        if(cost>dis[node]){
            continue;
        }
        for(auto it:adj[node]){
            if(cost-1<dis[it]){
                parent[it]=node;
                dis[it]=cost-1;
                pq.push({dis[it],it});
            }
        }
    }
    vector<int> ans;
    int temp=n;
    while(parent[temp]!=-1){
        ans.push_back(temp);
        temp=parent[temp];
    }
    ans.push_back(temp);
    if(temp!=1) cout<<"IMPOSSIBLE";
    else{
        cout<<ans.size()<<endl;
        reverse(ans.begin(),ans.end());
        for(auto it:ans){
            cout<<it<<" ";
        }
    }
}
 
int main(){
    int n,m;
    cin>>n>>m;
    int a,b;
    vector<vector<int>> adj(n+1);
    for(int i=0;i<m;i++){
        cin>>a>>b;
        adj[a].push_back(b);
    }
    
    dijkstra(adj);
}
