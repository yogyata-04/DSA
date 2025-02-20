#include<bits/stdc++.h>
using namespace std;

//shortest path in undirected graph with unit weights
//TC->O(n+2*E(bfs)+n(backtracking shortest distance)) SC->O(n(queue)+n(parent vector)+n(distance vector)+n(ans vector))
#include<bits/stdc++.h>
using namespace std;
vector<int> shortestpath_undirectedgraph(vector<vector<int>> adj,int src,int des){
    int n=adj.size();
    queue<pair<int,int>> q;//node,dist
    vector<int> ans;
    //storing parents to trace back path for any destination - we could have also created vector<vector<int>> for every destination node from given source
    vector<int> par(n,-1);
    vector<int> dis(n,INT_MAX);
    q.push({src,0});
    while(!q.empty()){
        auto front=q.front();
        int node=front.first;
        int dist=front.second;
        q.pop();
        for(auto it:adj[node]){
            if(dis[it]==INT_MAX){
                dis[it]=dist+1;
                par[it]=node;
                q.push({it,dis[it]});
            }
        }
    }
    for(auto it:par){
        cout<<it<<" ";
    }
    cout<<endl;
    //tracing back shortest path
    int node=des;
    while(par[node]!=-1){
        ans.push_back(node);
        node=par[node];
    }
    
    if(node!=src) return {};
    ans.push_back(node);
    reverse(ans.begin(),ans.end());
    return ans;
}

int main(){
    vector<vector<int>> adj={{1,3},{2},{6},{4},{5},{6},{7,8},{6,8},{6,7}};
    vector<int> ans=shortestpath_undirectedgraph(adj,0,5);
    for(auto it:ans){
        cout<<it<<" ";
    }
}

//printing shortest path
//TC->O(V+2*E)(BFS) SC->O(V*2(queue)+V(dist array)+V*2(path array))
vector<int> spath_undirected(vector<vector<int>> adj){
    int n=adj.size();
    queue<pair<int,vector<int>>> q; //node, path 
    q.push({0,{0}});
    vector<int> dist(n,INT_MAX);
    vector<vector<int>> vec(n);
    dist[0]=0;
    int dis=1;
    while(!q.empty()){
        int m=q.size();
        while(m--){
            auto front=q.front();
            q.pop();
            int node=front.first;
            vector<int> temp=front.second;
            for(auto it:adj[node]){
                if(dist[it]==INT_MAX){
                    dist[it]=dis;
                    temp.push_back(it);
                    q.push({it,temp});
                    vec[it]=temp;
                    temp.pop_back();
                }
            }
        }
        dis++;
    }
    for(auto it:vec){
        for(auto i:it){
            cout<<i<<" ";
        }
        cout<<endl;
    }
    return dist;
}

#include<bits/stdc++.h>
using namespace std;

//shortest path in DAG
//we will first find toposort and then we will release each node and keep on updating distance
//TC->O(E+V+V+V)
//NOTE- Need to figure out how to solve problems like from src,dis in directed graph
vector<int> shortestpath_DAG(vector<vector<pair<int,int>>> adj){
    int n=adj.size();
    queue<int> q;
    vector<int> dis(n,INT_MAX);
    vector<int> indegree(n,0);
    for(int i=0;i<n;i++){
        for(auto it:adj[i]){
            indegree[it.first]++;
        }
    }
    for(int i=0;i<n;i++){
        if(indegree[i]==0) {q.push(i);dis[i]=0;}
    }
    vector<int> toposort;
    while(!q.empty()){
        int front=q.front();
        q.pop();
        for(auto it:adj[front]){
            indegree[it.first]--;
            if(indegree[it.first]==0){
                q.push(it.first);
            }
            if(it.second+dis[front]<dis[it.first]){
                dis[it.first]=it.second+dis[front];
            }
        }
    }
    return dis;
    
}

int main(){
    vector<vector<pair<int,int>>> adj={{{1,2},{4,1}},{{2,3}},{{3,6}},{},{{5,4},{2,2}},{{3,1}}};
    vector<int> dis=shortestpath_DAG(adj);
    for(auto it:dis){
        cout<<it<<" ";
    }
}

#include<bits/stdc++.h>
using namespace std;
//shortest path in directed acyclic graph (weighted)
//to decide the order of nodes and starting node we need topo sorted order
//I am using dfs here we can also use bfs
//Here we are deciding source node, but there might be cases where we are given source node (in such case there might be possibility of not reaching certain nodes)
//TC->O(V(finding indegree)+V(adding source nodes in queue)+(V+E)(toposort order)+(V+E)(updating distance array))
//SC->O(V(indegree)+V(queue)+V(order)+V(dist))
vector<int> spath_directedacyclic(vector<vector<pair<int,int>>> adj){
    int n=adj.size();
    vector<int> indegree(n,0);
    for(int i=0;i<n;i++){
        for(auto it:adj[i]){
            indegree[it.first]++;
        }
    }
    queue<int> q;
    for(int i=0;i<n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    vector<int> order;
    while(!q.empty()){
        int front=q.front();
        q.pop();
        order.push_back(front);
        for(auto it:adj[front]){
            indegree[it.first]--;
            if(indegree[it.first]==0) q.push(it.first);
        }
    }
    
    vector<int> dist(n,INT_MAX);
    dist[order[0]]=0;
    for(auto it:order){
        for(auto i:adj[it]){
            if((long long)dist[i.first]>(long long)dist[it]+(long long)i.second) dist[i.first]=dist[it]+i.second;
        }
    }
    return dist;
}

//if non weighted direccted acyclic graph
vector<int> spath_directedacyclic1(vector<vector<int>> adj){
    int n=adj.size();
    vector<int> indegree(n,0);
    for(int i=0;i<n;i++){
        for(auto it:adj[i]){
            indegree[it]++;
        }
    }
    queue<int> q;
    for(int i=0;i<n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    vector<int> order;
    while(!q.empty()){
        int front=q.front();
        q.pop();
        order.push_back(front);
        for(auto it:adj[front]){
            indegree[it]--;
            if(indegree[it]==0) q.push(it);
        }
    }
    
    vector<int> dist(n,INT_MAX);
    dist[order[0]]=0;
    for(auto it:order){
        for(auto i:adj[it]){
            if(dist[i]==INT_MAX) dist[i]=dist[it]+1;
        }
    }
    return dist;
}

//Remember whenever it's given that we don't have negative weight edges and we have to find shortest path,
//it is mp question of Dijkstra's algorithm
//not applicable for negative weights
//applicable for cyclic graphs
//Shortest path for graph (can work for cyclic graph as well, but does not work for negative weights)

//DIJKSTRA IMPLEMENTATION USING PRIORITY QUEUE
//WE WILL NOT USE QUEUE OTHERWISE UNNECESSARY EXPLORING OF ALL PATHS
//TC->O(ElogV) SC->O(V+E)
vector<int> dijkstra(vector<vector<pair<int,int>>> adj,int src){
    int n=adj.size();
    vector<int> dis(n,INT_MAX);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,src});
    dis[src]=0;
    while(!pq.empty()){
        auto front=pq.top();
        int dist=front.first;
        int node=front.second;
        pq.pop();
        for(auto it:adj[node]){
            if(dis[it.first]>dist+it.second){
                dis[it.first]=dist+it.second;
                pq.push({dis[it.first],it.first});
            }
        }
    }
    return dis;
}
//DIJKSTRA IMPLEMENTATION USING SET
vector<int> dijkstra(vector<vector<pair<int,int>>> adj,int src){
    int n=adj.size();
    vector<int> dis(n,INT_MAX);
    set<pair<int,int>> st;
    st.insert({0,src});
    dis[src]=0;
    while(!st.empty()){
        auto front=*(st.begin());
        int dist=front.first;
        int node=front.second;
        st.erase(front);
        for(auto it:adj[node]){
            if(dis[it.first]>dist+it.second){
                if(dis[it.first]!=INT_MAX){
                    st.erase({dis[it.first],it.first});
                }
                dis[it.first]=dist+it.second;
                st.insert({dis[it.first],it.first});
            }
        }
    }
    return dis;
}

//Shortest path in a binary maze
//we will simply use queue here and not priority queue as undirected graph kind of arrangement
//TC->O(8*N*M) SC->O(2*N*M)
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    //EDGE CASE - WHAT IF SOURCE ITSELF IS 1
    if(grid[0][0]==1) return -1;

    int n=grid.size();
    int m=grid[0].size();
    vector<vector<int>> dis(n,vector<int>(m,INT_MAX));
    dis[0][0]=1;
    
    queue<pair<int,pair<int,int>>> q;
    q.push({1,{0,0}});
    vector<int> dx={0,0,-1,1,1,-1,1,-1};
    vector<int> dy={1,-1,0,0,1,1,-1,-1};
    while(!q.empty()){
        auto top=q.front();
        int dist=top.first;
        int x=top.second.first;
        int y=top.second.second;
        q.pop();
        
        for(int i=0;i<8;i++){
            int new_x=x+dx[i];
            int new_y=y+dy[i];
            if(new_x>=0 && new_y>=0 && new_x<n && new_y<m && grid[new_x][new_y]==0 && (long long)(dis[new_x][new_y])>(long long)(dist+1)){
                dis[new_x][new_y]=dist+1;
                q.push({dis[new_x][new_y],{new_x,new_y}});
            }
        }
    }
    if(dis[n-1][m-1]==INT_MAX) return -1;
    return dis[n-1][m-1];
}

//Path with minimum effort
//Dijkstra solution for optimized exploration
//TC->O(ElogV) E=4*N*M V=N*M
int minimumEffortPath(vector<vector<int>>& heights) {
    int n=heights.size();
    int m=heights[0].size();
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> q;
    q.push({0,{0,0}});
    vector<int> dx={0,0,-1,1};
    vector<int> dy={1,-1,0,0};
    vector<vector<int>> dis(n,vector<int>(m,INT_MAX));
    dis[0][0]=0;
    while(!q.empty()){
        auto top=q.top();
        int max_effort=top.first;
        int x=top.second.first;
        int y=top.second.second;
        q.pop();
        if(x==n-1 && y==m-1){
            return max_effort;
        }
        
        for(int i=0;i<4;i++){
            int new_x=x+dx[i];
            int new_y=y+dy[i];
            if(new_x>=0 && new_y>=0 && new_x<n && new_y<m){
                //here I made mistake of updating max_effort but we will have other iterations as well for same node hence we can't update max_effort instead need new variable to store it
                int new_effort=max(max_effort,abs(heights[new_x][new_y]-heights[x][y]));
                if(new_effort<dis[new_x][new_y]){
                    dis[new_x][new_y]=new_effort;
                    q.push({dis[new_x][new_y],{new_x,new_y}});
                }
            }
        }
    }
    return 0;
}
//we can solve this question using queue also but unnecessary exploration of all paths even if we get a shorter cost path later for particular node that was inserted before
int minimumEffortPath(vector<vector<int>>& heights) {
    int n=heights.size();
    int m=heights[0].size();
    queue<pair<int,pair<int,int>>> q;
    q.push({0,{0,0}});
    vector<int> dx={0,0,-1,1};
    vector<int> dy={1,-1,0,0};
    vector<vector<int>> dis(n,vector<int>(m,INT_MAX));
    dis[0][0]=0;
    int min_effort=INT_MAX;
    while(!q.empty()){
        auto top=q.front();
        int max_effort=top.first;
        int x=top.second.first;
        int y=top.second.second;
        q.pop();
        if(x==n-1 && y==m-1){
            min_effort=min(max_effort,min_effort);
        }
        for(int i=0;i<4;i++){
            int new_x=x+dx[i];
            int new_y=y+dy[i];
            if(new_x>=0 && new_y>=0 && new_x<n && new_y<m){
                int new_effort=max(max_effort,abs(heights[new_x][new_y]-heights[x][y]));
                if(new_effort<dis[new_x][new_y]){
                    dis[new_x][new_y]=new_effort;
                    q.push({dis[new_x][new_y],{new_x,new_y}});
                }
            }
        }
    }
    if(min_effort==INT_MAX) return 0;
    return min_effort;
}

//cheapest flight within k stops -remember here we are not considering src and dst as stop
//This is dijkstra using queue 
//This time we cannot optimise it by not exploring all the paths and using priority queue for the same
//because there might be a possibility that we reach a destination at lower cost but exceeding k limit also here k is of atmost priority so, we will first consider it and as k will be increasing +1 every time 
//so we don't need priority queue as queue will also ensure that lowk is in front and highk on top
//also remember we will not stop once we reach destination in <=k stops because further path may have lower cost and <=k condition satisfied
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    //creating adj list //node->{child,cost}
    vector<vector<pair<int,int>>> adj(n);
    int m=flights.size();
    int min_cost=INT_MAX;
    for(int i=0;i<m;i++){
        int parent=flights[i][0];
        int child=flights[i][1];
        int cost=flights[i][2];
        adj[parent].push_back({child,cost});
    }
    vector<int> cost(n,INT_MAX);
    cost[src]=0;
    //create queue with k count, cost count, coordinates with most priority of cost count
    queue<pair<int,pair<int,int>>> q; //{cost,{kcount,node}}
    q.push({0,{0,src}});
    while(!q.empty()){
        auto front=q.front();
        int curr_cost=front.first;
        int curr_k=front.second.first;
        int node=front.second.second;
        q.pop();
        //previously coded curr_k<=k which gave incorrect result as I was counting dst also in stop which si not needed
        if(node==dst && curr_k<=k+1){
            min_cost=min(min_cost,curr_cost);
            continue;
        }
        for(auto it:adj[node]){
            if(curr_cost+it.second<=cost[it.first]){
                cost[it.first]=curr_cost+it.second;
                q.push({cost[it.first],{curr_k+1,it.first}});
            }
        }
    }
    if(min_cost==INT_MAX) return -1;
    return min_cost;
}

//network delay time
//here we have nodes from 1->n so 1 indexed
//TC->O(ElogV) SC->O(E+V+V)
//always remember to update time, cost or whatever array for src node
int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    //create adj list
    //n=no. of nodes, src=k
    vector<vector<pair<int,int>>> adj(n+1);
    int m=times.size();
    for(int i=0;i<m;i++){
        int parent=times[i][0];
        int child=times[i][1];
        int time=times[i][2];
        adj[parent].push_back({child,time});
    }
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;//time,node
    q.push({0,k});
    vector<int> t(n+1,INT_MAX); //t array to store min time for all nodes
    t[k]=0;
    while(!q.empty()){
        auto front=q.top();
        int time=front.first;
        int node=front.second;
        q.pop();
        for(auto it:adj[node]){
            if(time+it.second<t[it.first]){
                t[it.first]=time+it.second;
                q.push({t[it.first],it.first});
            }
        }
    }
    int max_time=0;
    for(int i=1;i<=n;i++){
        //cout<<t[i]<<" ";
        max_time=max(max_time,t[i]);
    }
    if(max_time==INT_MAX) return -1;
    return max_time;
}

//No. of ways to arrive at destination
//remember here we need to store previous ways also
//also take care of range of input and adjust type of int 
//Still testcase 54 not passed out of 55 testcases
int mod=1e9+7;
int countPaths(int n, vector<vector<int>>& roads) {
    vector<vector<pair<int,int>>> adj(n);
    int m=roads.size();
    for(int i=0;i<m;i++){
        int parent=roads[i][0];
        int child=roads[i][1];
        int time=roads[i][2];
        adj[parent].push_back({child,time});
        adj[child].push_back({parent,time});
    }
    vector<long long> time(n,LLONG_MAX);
    vector<long long> ways(n,0);
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> q;//time,node
    q.push({0,0}); //time,src
    time[0]=0;
    ways[0]=1;
    
    while(!q.empty()){
        auto front=q.top();
        int t=front.first;
        int nodef=front.second;
        q.pop();
        //so that we don't explore all paths unnecessarily
        if(t>time[nodef]) continue;
        for(auto it:adj[nodef]){
            int node=it.first;
            int td=it.second;
            if(1LL*td+t<time[node]){
                time[node]=1LL*t+td;
                //remember here don't have ways[node]=1;
                ways[node]=ways[nodef];
                q.push({time[node],node});
            }
            else if(1LL*td+t==time[node]){
                //same here don't have ways[node]++ instead add all previous node's ways also which might not be just 1
                ways[node]=(ways[nodef]+ways[node])%mod;
            }
        }
    }
    
    return ways[n-1];
}

//given src, dest and an arr
//we have to simply find min multiplication operations to reach destination from source 
//simply take a vector of size 10^5-1 as we have to do mod 10^5 if it exceeds this number.
//And in each index we will store min. steps. initialise with INT_MAX and then apply dijkstra.

//Bellman ford algorithm - to find negative cycle (if more than n-1 edges to get min. distance path, because if we are reducing path even at nth iteration that means we are taking n edges which means we have fallen inside some negative cycle)
//at most we just need n-1 edges to update all nodes min. distance
//why n-1 iterations, just consider a simple linkedlist and start from head as source and tail as destination and reverse order of list formed, we will understand that at each iteration n-i-1 element is updated
//works only for directed graph, so if undirected graph make it two way directed
//TC->O((V-1)*E) V-1 iterations and in each iteration E comparisons
vector<int> bellmanford(vector<vector<int>> edges,int src,int n){
    //n->no. of vertices
    vector<int> dis(n,INT_MAX);
    int m=edges.size(); //parent,child,weight
    for(int i=0;i<n-1;i++){
        for(int j=0;j<m;j++){
            int par=edges[j][0];
            int child=edges[j][1];
            int weight=edges[j][2];
            if(dis[par]!=INT_MAX && weight+dis[par]<dis[child]){
                dis[child]=dis[par]+weight;
            }
        }
    }
    //Nth relaxation to check if negative cycle exists
    for(int i=0;i<m;i++){
        int par=edges[j][0];
        int child=edges[j][1];
        int weight=edges[j][2];
        if(dis[par]!=INT_MAX && weight+dis[par]<dis[child]){
            return {-1}; //cycle exists
        }
    }
    return dis;
}
