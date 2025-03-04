#include<bits/stdc++.h>
using namespace std;

//this solution gave tle in one test case
//bfs for shortest distance
pair<int,string> bfs(int &startx,int &starty,vector<vector<char>> &vec,int &endx,int &endy){
    int n=vec.size();
    int m=vec[0].size();
    vector<vector<int>> vis(n,vector<int>(m,0));
    queue<pair<pair<int,int>,string>> q;
    q.push({{startx,starty},""});
    vis[startx][starty]=1;
    vector<int> dx={1,-1,0,0};
    vector<int> dy={0,0,1,-1};
    vector<string> path={"D","U","R","L"};
    int level=0;
    while(!q.empty()){
        int l=q.size();
        while(l--){
            auto front=q.front();
            q.pop();
            int x=front.first.first;
            int y=front.first.second;
            string str=front.second;
            for(int i=0;i<4;i++){
                int new_x=x+dx[i];
                int new_y=y+dy[i];
                if(new_x>=0 && new_x<n && new_y>=0 && new_y<m && vis[new_x][new_y]==0 && vec[new_x][new_y]=='B'){
                    return {level+1,str+path[i]};
                }
                else if(new_x>=0 && new_x<n && new_y>=0 && new_y<m && vis[new_x][new_y]==0 && vec[new_x][new_y]=='.'){
                    vis[new_x][new_y]=1;
                    q.push({{new_x,new_y},str+path[i]});
                }
                
            }
        }
        level++;
    }
    return {-1,""};
}

int main(){
    int n,m;
    cin>>n;
    cin>>m;
    vector<vector<char>> vec(n,vector<char>(m));
    int startx=-1,starty=-1;
    int endx=-1,endy=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>vec[i][j];
            if(vec[i][j]=='A'){
                startx=i;
                starty=j;
            }
            if(vec[i][j]=='B'){
                endx=i;
                endy=j;
            }
        }
    }
    pair<int,string> p=bfs(startx,starty,vec,endx,endy);
    if(p.first==-1){
        cout<<"NO";
    }
    else{
        cout<<"YES"<<endl;
        cout<<p.first<<endl;
        cout<<p.second<<endl;
    }
}

//solution using parent for path retrieval instead of storing it in queue  
//bfs for shortest distance
int bfs(int &startx,int &starty,vector<vector<char>> &vec,int &endx,int &endy,vector<vector<pair<int,int>>> &parent){
    int n=vec.size();
    int m=vec[0].size();
    vector<vector<int>> vis(n,vector<int>(m,0));
    queue<pair<int,int>> q;
    
    q.push({startx,starty});
    vis[startx][starty]=1;
    vector<int> dx={1,-1,0,0};
    vector<int> dy={0,0,1,-1};
    vector<string> path={"D","U","R","L"};
    int level=0;
    while(!q.empty()){
        int l=q.size();
        while(l--){
            auto front=q.front();
            q.pop();
            int x=front.first;
            int y=front.second;
            
            for(int i=0;i<4;i++){
                int new_x=x+dx[i];
                int new_y=y+dy[i];
                if(new_x>=0 && new_x<n && new_y>=0 && new_y<m && vis[new_x][new_y]==0 && vec[new_x][new_y]=='B'){
                    //made mistake here didn't update parent array and returned level+1 which always led to empty array as answer
                    parent[new_x][new_y]={x,y};
                    return level+1;
                }
                else if(new_x>=0 && new_x<n && new_y>=0 && new_y<m && vis[new_x][new_y]==0 && vec[new_x][new_y]=='.'){
                    vis[new_x][new_y]=1;
                    q.push({new_x,new_y});
                    parent[new_x][new_y]={x,y};
                }
            }
        }
        level++;
    }
    return -1;
}

int main(){
    int n,m;
    cin>>n;
    cin>>m;
    vector<vector<char>> vec(n,vector<char>(m));
    vector<vector<pair<int,int>>> parent(n,vector<pair<int,int>>(m,{-1,-1}));
    int startx=-1,starty=-1;
    int endx=-1,endy=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>vec[i][j];
            if(vec[i][j]=='A'){
                startx=i;
                starty=j;
            }
            if(vec[i][j]=='B'){
                endx=i;
                endy=j;
            }
        }
    }
    
    int dist=bfs(startx,starty,vec,endx,endy,parent);
    if(dist==-1){
        cout<<"NO";
    }
    else{
        cout<<"YES"<<endl;
        cout<<dist<<endl;
        int x=endx,y=endy;
        string path="";
        
        while(x!=startx || y!=starty){
            
            int px=parent[x][y].first;
            int py=parent[x][y].second;
            if(px>x && py==y){
                path+="U";
            }
            else if(px<x && py==y){
                path+="D";
            }
            else if(px==x && py>y){
                path+="L";
            }
            else {
                path+="R";
            }
            x=px;
            y=py;
        }
        reverse(path.begin(),path.end());
        cout<<path<<endl;
    }
}

