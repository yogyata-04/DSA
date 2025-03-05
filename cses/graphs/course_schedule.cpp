#include<bits//stdc++.h>
using namespace std;

//using Kahn's algorithm
int main(){
    int n,m;
    cin>>n>>m;
    int a,b;
    vector<vector<int>> adj(n+1);
    vector<int> indegree(n+1,0);
    for(int i=0;i<m;i++){
        cin>>a>>b;
        adj[a].push_back(b);
        indegree[b]++;
    }
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    //no starting node then not possible as cycle definitely exist
    if(q.size()==0){
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }
    vector<int> ans;
    while(!q.empty()){
        int front=q.front();
        q.pop();
        ans.push_back(front);
        for(auto it:adj[front]){
            indegree[it]--;
            if(indegree[it]==0){
                q.push(it);
            }
        }
    }
    //Don't forget to include this check
    if(ans.size()!=n) cout<<"IMPOSSIBLE"<<endl;
    else{
        for(auto it:ans){
            cout<<it<<" ";
        }
    }
}
