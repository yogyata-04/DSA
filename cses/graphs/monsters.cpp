#include<bits/stdc++.h>
using namespace std;


//mistake I didn't consider monster movement and treated them as wall only
// bool dfs(int x,int y,vector<vector<char>> &grid,vector<vector<int>> &vis,vector<vector<pair<int,int>>> &parent,int n,int m,int &endx,int &endy){
//     vis[x][y]=1;
//     //at edge if i=0 || j=0 || i==n-1 || j==m-1;
//     vector<int> dx={0 ,0 ,1,-1};
//     vector<int> dy={1 ,-1,0,0};
//     for(int i=0;i<4;i++){
//         int new_x=x+dx[i];
//         int new_y=y+dy[i];
//         if(new_x>=0 && new_y>=0 && new_x<n && new_y<m && !vis[new_x][new_y] && grid[new_x][new_y]=='.'){
//             parent[new_x][new_y]={x,y};
//             if(new_x==0 || new_x==n-1 || new_y==0 || new_y==m-1){
//                 endx=new_x;
//                 endy=new_y;
//                 return true;
//             }
//             else if(dfs(new_x,new_y,grid,vis,parent,n,m,endx,endy)) return true;
//         }
//     }
//     return false;
// }

// int main(){
//     int n,m;
//     cin>>n>>m;
//     vector<vector<char>> vec(n,vector<char>(m));
//     int startx=-1,starty=-1;
//     for(int i=0;i<n;i++){
//         for(int j=0;j<m;j++){
//             cin>>vec[i][j];
//             if(vec[i][j]=='A'){
//                 startx=i,starty=j;
//             }
//         }
//     }
//     vector<vector<int>> vis(n,vector<int>(m,0));
//     vector<vector<pair<int,int>>> parent(n,vector<pair<int,int>>(m));
//     int endx=-1,endy=-1;
//     if(dfs(startx,starty,vec,vis,parent,n,m,endx,endy)){
//         int x=endx,y=endy;
//         string ans="";
//         while(x!=startx || y!=starty){
//             int px=parent[x][y].first;
//             int py=parent[x][y].second;
//             if(px<x && py==y){
//                 ans+="D";
//             }
//             else if(px>x && py==y){
//                 ans+="U";
//             }
//             else if(px==x && py>y){
//                 ans+="L";
//             }
//             else {
//                 ans+="R";
//             }
//             x=px;
//             y=py;
//         }
//         reverse(ans.begin(),ans.end());
//         cout<<"YES"<<endl;
//         cout<<ans.size()<<endl;
//         cout<<ans<<endl;
//     }
//     else cout<<"NO";
// }


//not handled cases where in last line we have spaces and no input - no idea how to handle them

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<char>> vec(n,vector<char>(m,'#'));
    queue<pair<int,int>> q;
    vector<vector<int>> time(n,vector<int> (m,INT_MAX)); //time in which monster can raech a cell
    int startx=-1,starty=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>vec[i][j];
            if(vec[i][j]=='M'){
                q.push({i,j});
                time[i][j]=0;
            }
            if(vec[i][j]=='A'){
                startx=i;
                starty=j;
            }
        }
    }
    //EDGE CASE if A is at edge already
    if(startx==0|| starty==0|| startx==n-1 || starty==m-1){
        cout<<"YES"<<endl;
        cout<<"0"<<endl;
        return 0;
    }
    //first step -  compute least time in which monster can reach a cell
    vector<int> dx={1,-1,0,0};
    vector<int> dy={0,0,1,-1};
    int t=0;
    while(!q.empty()){
        int k=q.size();
        t++;
        while(k--){
            auto front=q.front();
            q.pop();
            int x=front.first;
            int y=front.second;
            for(int i=0;i<4;i++){
                int new_x=x+dx[i];
                int new_y=y+dy[i];
                if(new_x>=0 && new_x<n && new_y>=0 && new_y<m && vec[new_x][new_y]!='#' && time[new_x][new_y]==INT_MAX){
                    time[new_x][new_y]=t;
                    q.push({new_x,new_y});
                }
            }
        }
    }
    
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         cout<<time[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    
    //bfs on our start node based on condition that minimum reachable time on any tile should be less than that of monster
    q.push({startx,starty});
    t=0;
    int endx=-1,endy=-1;
    int flag=0;
    vector<vector<pair<int,int>>> parent(n,vector<pair<int,int>>(m));
    while(!q.empty()){
        t++;
        int k=q.size();
        while(k--){
            auto front=q.front();
            q.pop();
            int x=front.first;
            int y=front.second;
            for(int i=0;i<4;i++){
                int new_x=x+dx[i];
                int new_y=y+dy[i];
                
                if(new_x>=0 && new_x<n && new_y>=0 && new_y<m && vec[new_x][new_y]=='.'){
                    //did mistake here by adding this condition outside current if which included "#" path also
                    if(new_x==0|| new_y==0|| new_x==n-1 || new_y==m-1){
                        flag=1;
                        endx=new_x;
                        endy=new_y;
                        parent[new_x][new_y]={x,y};
                        break;
                    }
                    if(t<time[new_x][new_y]){
                        parent[new_x][new_y]={x,y};
                        q.push({new_x,new_y});
                    }
                }
            }
            if(flag==1) break;
        }
        if(flag==1) break;
    }
    if(endx==-1 && endy==-1) cout<<"NO";
    else{
        string ans="";
        int x=endx,y=endy;
        while(x!=startx || y!=starty){
            int px=parent[x][y].first;
            int py=parent[x][y].second;
            if(px<x && py==y){
                ans+="D";
            }
            else if(px>x && py==y){
                ans+="U";
            }
            else if(px==x && py>y){
                ans+="L";
            }
            else {
                ans+="R";
            }
            x=px;
            y=py;
        }
        reverse(ans.begin(),ans.end());
        cout<<"YES"<<endl;
        cout<<ans.size()<<endl;
        cout<<ans<<endl;
    }
}
