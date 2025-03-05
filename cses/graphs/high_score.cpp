#include<bits/stdc++.h>
using namespace std;

//I am getting wrong answer on few test cases still..unable to figure out why
int main(){
    int n,m;
    cin>>n>>m;

    vector<pair<pair<int,int>,long long>> vec(m);
    int a,b;
    long long c;
    for(int i=0;i<m;i++){
        cin>>a>>b>>c;
        vec[i]={{a,b},c};
    }
    vector<long long> dis(n+1,LONG_MIN);
    dis[1]=0;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<m;j++){
            int x=vec[j].first.first;
            int y=vec[j].first.second;
            long long dist=vec[j].second;
            //don't update if x itself is not visited yet 
            if(dis[x]==LONG_MIN) continue;
            if(dist+dis[x]>dis[y]){
                dis[y]=dist+dis[x];
            }
        }
    }
    long long dist=dis[n];
    //checking if cycle exists
    int flag=0;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<m;j++){
            int x=vec[j].first.first;
            int y=vec[j].first.second;
            long long dist=vec[j].second;
            //don't update if x itself is not visited yet 
            if(dis[x]==LONG_MIN) continue;
            if(dist+dis[x]>dis[y]){
                dis[y]=dist+dis[x];
            }
        }
    }
    if(dis[n]>dist) flag=1;
    
    if(flag==1) cout<<"-1";
    else cout<<dis[n];
}

