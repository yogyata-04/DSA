#include<bits/stdc++.h>
using namespace std;
 
int main(){
    int n,m;
    cin>>n>>m;
    //did mistake of not taking long long for distance as it can be out of int range
    vector<vector<pair<int,long long>>> adj(n+1);
    int a,b;
    long long c;
    for(int i=0;i<m;i++){
        cin>>a>>b>>c;
        adj[a].push_back({b,c});
    }
    vector<long long> dis(n+1,LONG_MAX);
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> q; //node,dis
    q.push({0,1});
    dis[1]=0;
    while(!q.empty()){
        auto front=q.top();
        q.pop();
        int node=front.second;
        long long dist=front.first;
        if(dist>dis[node]) continue;
        for(auto it:adj[node]){
            if(dis[it.first]>dist+it.second){
                dis[it.first]=dist+it.second;
                q.push({dis[it.first],it.first});
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<dis[i]<<" ";
    }
}
