#include<bits/stdc++.h>
using namespace std;

//solution using floyd warshall - multisource distance
int main(){
    int n,m,q;
    cin>>n>>m>>q;
    int a,b;
    long long c;
    vector<vector<long long>> dis(n+1,vector<long long>(n+1,LONG_MAX));
    for(int i=1;i<=n;i++){
        dis[i][i]=0;
    }
    for(int i=0;i<m;i++){
        cin>>a>>b>>c;
        //did mistake here, it is never said that only one c for a,b pair we have many c and we have to choose minimum
        dis[a][b]=min(c,dis[a][b]);
        dis[b][a]=dis[a][b];
    }
    
    vector<pair<int,int>> queries(q);
    for(int i=0;i<q;i++){
        cin>>a>>b;
        queries[i]={a,b};
    }
    
    for(int via=1;via<=n;via++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                //edge case if via is not reachable by any node i or j
                if(dis[i][via]==LONG_MAX || dis[via][j]==LONG_MAX) continue;
                dis[i][j]=min(dis[i][j],dis[i][via]+dis[via][j]);
                dis[j][i]=dis[i][j];
            }
        }
    }
    
    for(int i=0;i<q;i++){
        int x=queries[i].first;
        int y=queries[i].second;
        if(dis[x][y]==LONG_MAX) {cout<<"-1"<<endl; continue;}
        cout<<dis[x][y]<<endl;
    }
    
}
