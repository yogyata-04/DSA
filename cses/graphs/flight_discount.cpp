#include<bits/stdc++.h>
using namespace std;

//This is modified dijkstra with usedDiscount factor
int main(){
    int n,m;
    cin>>n>>m;
    int a,b;
    long long c;
    vector<vector<pair<int,long long>>> adj(n+1);
    for(int i=0;i<m;i++){
        cin>>a>>b>>c;
        adj[a].push_back({b,c});
    }
    
    vector<vector<long long>> dis(n+1,vector<long long>(2,LONG_MAX)); //0->without discount 1->with discount
    dis[1][0]=0;
    priority_queue<pair<long long,pair<int,bool>>,vector<pair<long long,pair<int,bool>>>,greater<pair<long long,pair<int,bool>>>> pq;
    //price with/without discount, node, used discount
    pq.push({0,{1,false}});
    while(!pq.empty()){
        auto front=pq.top();
        pq.pop();
        long long cost=front.first;
        int node=front.second.first;
        bool usedDiscount=front.second.second;
        if(dis[node][usedDiscount]<cost){
            continue;
        }
        for(auto it:adj[node]){
            //without using discount
            //remember here we will use usedDiscount and not 0 because if we have used discount then that will always be better than no discount used 
            if((cost+it.second)<dis[it.first][usedDiscount]){
                dis[it.first][usedDiscount]=cost+it.second;
                pq.push({dis[it.first][usedDiscount],{it.first,usedDiscount}});
            }
            //with discount
            if(usedDiscount==false){
                if((cost+((it.second)/2))<dis[it.first][1]){
                    dis[it.first][1]=cost+((it.second)/2);
                    pq.push({dis[it.first][1],{it.first,true}});
                }
            }
        }
    }
    cout<<dis[n][1]<<endl;
}

