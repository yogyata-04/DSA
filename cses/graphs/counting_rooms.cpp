#include<bits/stdc++.h>
using namespace std;

//got runtime error with dfs 
void dfs(int i,int j,vector<vector<char>> vec,vector<vector<int>> &vis,int n,int m){
    vis[i][j]=1;
    vector<int> dx={1,-1,0,0};
    vector<int> dy={0,0,1,-1};
    for(int k=0;k<4;k++){
        int new_x=i+dx[k];
        int new_y=j+dy[k];
        if(new_x>=0 && new_x<n && new_y>=0 && new_y<m && vis[new_x][new_y]==0 && vec[new_x][new_y]=='.'){
            dfs(new_x,new_y,vec,vis,n,m);
        }
    }
}

//runtime error removed but still TLE for 2 testcases
//runtime error removed if I had vec with reference
void bfs(int i,int j,vector<vector<char>> &vec,vector<vector<int>> &vis){
    int n=vec.size();
    int m=vec[0].size();
    queue<pair<int,int>> q;
    q.push({i,j});
    vector<int> dx={1,-1,0,0};
    vector<int> dy={0,0,1,-1};
    while(!q.empty()){
        auto front=q.front();
        q.pop();
        int x=front.first;
        int y=front.second;
        for(int i=0;i<4;i++){
            int new_x=x+dx[i];
            int new_y=y+dy[i];
            if(new_x>=0 && new_x<n && new_y>=0 && new_y<m && vis[new_x][new_y]==0 && vec[new_x][new_y]=='.'){
                vis[new_x][new_y]=1;
                q.push({new_x,new_y});
            }
        }
    }
}

int solution(vector<vector<char>> vec){
    int n=vec.size();
    int m=vec[0].size();
    vector<vector<int>> vis(n,vector<int> (m,0));
    int cnt=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(vis[i][j]==0 && vec[i][j]=='.'){
                bfs(i,j,vec,vis);
                cnt++;
            }
        }
    }
    return cnt;
}

int main(){
    int n,m;
    cin>>n;
    cin>>m;
    vector<vector<char>> vec(n,vector<char>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>vec[i][j];
        }
    }
    cout<<solution(vec);
}
