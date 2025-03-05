#include<bits/stdc++.h>
using namespace std;

//getting 3 wrong answers
int main(){
  
    int n,m;
    cin>>n>>m;
    int a,b;
    long long c;
    vector<pair<pair<int,int>,long long>> vec(m);
    for(int i=0;i<m;i++){
        cin>>a>>b>>c;
        vec[i]={{a,b},c};
    }
    vector<int> parent(n+1,-1);
    vector<long long> dis(n+1,LONG_MAX);
    dis[1]=0;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<m;j++){
            int x=vec[j].first.first;
            int y=vec[j].first.second;
            long long dist=vec[j].second;
            //don't update if x itself is not visited yet 
            if(dis[x]==LONG_MAX) continue;
            if(dist+dis[x]<dis[y]){
                //parent to recover cycle path
                parent[y]=x;
                dis[y]=dist+dis[x];
            }
        }
    }
    
    //checking if cycle exists
    int flag=0;
    
    for(int j=0;j<m;j++){
        int x=vec[j].first.first;
        int y=vec[j].first.second;
        long long dist=vec[j].second;
        //don't update if x itself is not visited yet 
        if(dis[x]==LONG_MAX) continue;
        if(dist+dis[x]<dis[y]){
            parent[y]=x;
            flag=y;
            //add break condition
            break;
        }
    }
    
    
    if(flag==0) cout<<"NO";
    else {
        //take care of this thing
        //flag might not be inside the cycle; it could just be a node affected by it.
        for (int i = 0; i < n; i++) {flag = parent[flag];}
        //negative cycle exists
        //print cycle using parent
        vector<int> path;
        int temp=flag;
        path.push_back(flag);
        while(parent[flag]!=temp && parent[flag]!=-1){
            path.push_back(parent[flag]);
            flag=parent[flag];
        }
        path.push_back(temp);
        cout<<"YES"<<endl;
        reverse(path.begin(),path.end());
        for(auto it:path){
            cout<<it<<" ";
        }
    }
}

