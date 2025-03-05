// #include<bits/stdc++.h>
// using namespace std;

// long long mod=1e9+7;

//got tle in 3 testcases using this method because of unnecesarry exploring of many paths with same cost
// void dijkstra(vector<vector<pair<int,long long>>> adj){
//     int n=adj.size()-1;
//     priority_queue<pair<long long,pair<int,int>>,vector<pair<long long,pair<int,int>>>,greater<pair<long long,pair<int,int>>>> pq;
//     //cost,node,count of flights
//     pq.push({0,{1,1}});
//     int max_cnt=INT_MIN;
//     int min_cnt=INT_MAX;
//     vector<long long> dis(n+1,LONG_MAX);
//     dis[1]=0;
//     long long ans=0;
//     long long min_cost=LONG_MAX;
//     while(!pq.empty()){
//         auto front=pq.top();
//         pq.pop();
//         long long cost=front.first;
//         int node=front.second.first;
//         int cnt=front.second.second;
//         if(cost>dis[node]){
//             continue;
//         }
//         if(node==n){
//             min_cnt=min(min_cnt,cnt);
//             max_cnt=max(max_cnt,cnt);
//             min_cost=cost;
//             ans=(ans+1)%mod;
//             while(!pq.empty()){
//                 auto front=pq.top();
//                 pq.pop();
//                 long long cost=front.first;
//                 int node=front.second.first;
//                 int cnt=front.second.second;
//                 if(cost>min_cost) break;
//                 else if(cost==min_cost && node==n){
//                     min_cnt=min(min_cnt,cnt);
//                     max_cnt=max(max_cnt,cnt);
//                     ans=(ans+1)%mod;
//                 }
//             }
//             break;
//         }
//         for(auto it:adj[node]){
//             if(dis[it.first]>=cost+it.second){
//                 dis[it.first]=cost+it.second;
//                 pq.push({dis[it.first],{it.first,cnt+1}});
//             }
//         }
//     }
//     cout<<min_cost<<" "<<ans<<" "<<min_cnt-1<<" "<<max_cnt-1<<endl;
// }

// int main(){
//     int n,m;
//     cin>>n>>m;
//     int a,b;
//     long long c;
//     vector<vector<pair<int,long long>>> adj(n+1);
//     for(int i=0;i<m;i++){
//         cin>>a>>b>>c;
//         adj[a].push_back({b,c});
//     }
//     //dijkstra
//     dijkstra(adj);
// }

const long long mod = 1e9 + 7;
const long long INF = 1e18;  // Large value to avoid overflow

void dijkstra(vector<vector<pair<int, long long>>> &adj, int n) {
    vector<long long> dis(n + 1, INF);  // Shortest distance to each node
    vector<long long> ways(n + 1, 0);   // Number of ways to reach a node with min cost
    vector<int> minFlights(n + 1, INT_MAX); // Minimum flights in shortest path
    vector<int> maxFlights(n + 1, INT_MIN); // Maximum flights in shortest path

    // Min-heap: {cost, node}
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    
    // Start from node 1
    pq.push({0, 1});
    dis[1] = 0;
    ways[1] = 1;
    minFlights[1] = maxFlights[1] = 0;

    while (!pq.empty()) {
        auto front = pq.top();
        long long cost=front.first;
        int node=front.second;
        pq.pop();

        // Ignore if we already found a better path
        if (cost > dis[node]) continue;

        // Process neighbors
        for (auto it: adj[node]) {
            long long edgeCost=it.second;
            int nextNode=it.first;
            long long newCost = cost + edgeCost;

            // Found a strictly shorter path
            if (newCost < dis[nextNode]) {
                dis[nextNode] = newCost;
                pq.push({newCost, nextNode});

                // Update values
                ways[nextNode] = ways[node];  // Reset path count
                minFlights[nextNode] = minFlights[node] + 1;
                maxFlights[nextNode] = maxFlights[node] + 1;
            }
            // Found another shortest path
            else if (newCost == dis[nextNode]) {
                ways[nextNode] = (ways[nextNode] + ways[node]) % mod;
                minFlights[nextNode] = min(minFlights[nextNode], minFlights[node] + 1);
                maxFlights[nextNode] = max(maxFlights[nextNode], maxFlights[node] + 1);
            }
        }
    }

    // Output results
    cout << dis[n] << " " << ways[n] << " " << minFlights[n] << " " << maxFlights[n] << endl;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    // Run Dijkstra Algorithm
    dijkstra(adj, n);

    return 0;
}
