#inlcude<bits/stdc++.h>
using namespace std;

//Graph representation - adjacency matrix (O(N^2)) and adjacency list O(2*E)

//bfs traversal
//when we consider starting node=0
//TC->O(N+2E) SC->O(2*E(adj. list)+N(queue)+N(visited vector))
vector<int> bfsOfGraph(vector<vector<int>> &adj) {
    vector<int> ans;
    int n=adj.size();
    vector<int> vis(n,0);
    queue<int> q;
    q.push(0);
    vis[0]=1;
    while(!q.empty()){
        int front=q.front();
        q.pop();
        ans.push_back(front);
        for(auto it:adj[front]){
            if(!vis[it]) q.push(it);
            vis[it]=1;
        }
    }
    return ans;
}

//dfs traversal
//when we are considering starting point as 0;
//TC->O(N+2E) SC->O(N(stack space worst case when skewed graph)+N(vis array)+2E(adj. list))
void dfs(int node,vector<vector<int>>& adj, vector<int> &vis,vector<int> &ans){
    ans.push_back(node);
    vis[node]=1;
    for(auto it:adj[node]){
        if(!vis[it]){
            dfs(it,adj,vis,ans);
        }
    }
}

vector<int> dfsOfGraph(vector<vector<int>>& adj) {
    int n=adj.size();
    vector<int> ans;
    vector<int> vis(n,0);
    dfs(0,adj,vis,ans);
    return ans;
}

//no. of provinces
//always remember to take reference of vis vector
//TC->O(N^2(converting adjacency matrix to adj. list)+N(loop i)+2E(traversal)) SC->O(N(recursion stack space)+N(vis array)+2E(adj. list))
void traversal(int node, vector<vector<int>> adj, vector<int> &vis){
    vis[node]=1;
    for(auto it:adj[node]){
        if(!vis[it]) traversal(it,adj,vis);
    }
}

int findCircleNum(vector<vector<int>>& vec) {
    //1-indexed
    //convert adj matrix to adj list
    int n=vec.size();
    vector<vector<int>> adj(n);
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            if(vec[i][j]==1){
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    vector<int> vis(n,0);
    int cnt=0;
    for(int i=0;i<n;i++){
        if(!vis[i]){
            traversal(i,adj,vis);
            cnt++;
        }
    }
    return cnt;
}

//rotten oranges
//BFS traversal
//TC->O(4*m*n(bfs)+n*m(counting fresh and pushing rot)) +SC(n*n+n*n)
int orangesRotting(vector<vector<int>>& grid) {
    int n=grid.size();
    int m=grid[0].size();
    //we can move in four directions
    int dx[]={0,0,1,-1};
    int dy[]={1,-1,0,0};
    queue<pair<int,int>> q; //index(x,y)
    //need to keep track of count because there might be a possibility that all fresh oranges are not reached
    int cnt_fresh=0;
    vector<vector<int>> vis(n,vector<int>(m,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j]==2) {q.push({i,j});vis[i][j]=1;}
            else if(grid[i][j]==1) cnt_fresh++;
            else vis[i][j]=1;
        }
    }
    //EDGE CASE
    if(cnt_fresh==0) return 0;
    int t=0;
    while(!q.empty()){
        //did mistake and took n instead of size and it collided with previous variable which led to wrong answer
        int size=q.size();
        while(size--){
            int x=q.front().first;
            int y=q.front().second;
            q.pop();
            
            for(int i=0;i<4;i++){
                int xn=x+dx[i];
                int yn=y+dy[i];
                if(xn>=0 && xn<n && yn>=0 && yn<m && vis[xn][yn]!=1){
                    if(grid[xn][yn]==1){
                        q.push({xn,yn});
                        vis[xn][yn]=1;
                        cnt_fresh--;
                    }
                }
            }
        }
        t++;
        //Remember this step
        if(cnt_fresh==0){
            return t;
        }
    }
    
    if(cnt_fresh!=0) return -1;
    return t;
}

//Flood fill
//TC->O(4*n*m) SC->O(n*m)
//NOTE-whenever minimum time is there in question do bfs and not dfs
//we can solve it using dfs as well - we will need visited vector for this approach so extra space required
vector<vector<int>> floodFill(vector<vector<int>>& grid, int sr, int sc, int color) {
    //Remember this edge case else will fall in infinite loop without visited array
    if(grid[sr][sc]==color) return grid;
    int n=grid.size();
    int m=grid[0].size();
    //we can move in four directions
    int dx[]={0,0,1,-1};
    int dy[]={1,-1,0,0};
    queue<pair<int,int>> q; //index(x,y)
    //need to keep track of count because there might be a possibility that all fresh oranges are not reached
    int cnt_fresh=0;
    vector<vector<int>> ans(n,vector<int>(m,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            ans[i][j]=grid[i][j];
        }
    }
    int colororg=grid[sr][sc];
    q.push({sr,sc});
    while(!q.empty()){
        //did mistake and took n instead of size and it collided with previous variable which led to wrong answer
        int size=q.size();
        while(size--){
            int x=q.front().first;
            int y=q.front().second;
            q.pop();
            ans[x][y]=color;
            for(int i=0;i<4;i++){
                int xn=x+dx[i];
                int yn=y+dy[i];
                if(xn>=0 && xn<n && yn>=0 && yn<m && ans[xn][yn]==colororg){
                    ans[xn][yn]=color;
                    q.push({xn,yn});
                }
            }
        }
        
    }
    
    return ans;
}

//dfs traversal
//TC->O(4*n*m) SC->O(n*m stack space)
void dfs(int x,int y,vector<vector<int>> &image,int color,int scol){
    int n=image.size(),m=image[0].size();
    int r[]={-1,1,0,0};
    int c[]={0,0,-1,1};
    for(int i=0;i<4;i++){
        int row=x+r[i];
        int col=y+c[i];
        if(row>=0 && col>=0 && row<n && col<m && image[row][col]==scol){
            image[row][col]=color;
            dfs(row,col,image,color,scol);
        }
    }
}

vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
    //EDGE CASE
    if(image[sr][sc]==color) return image;
    queue<pair<int,int>> q;
    int scol=image[sr][sc];
    image[sr][sc]=color;
    int n=image.size(),m=image[0].size();
    dfs(sr,sc,image,color,scol);
    
    return image;
}

//CYCLE DETECTION

//BFS Approach
//TC->O(2*E+N(connected components case)) SC->O(n+n)
//always remember the case of components in graph in such cases
bool isCycle(vector<vector<int>>& adj) {
    int n=adj.size();
    vector<int> vis(n,0);
    for(int i=0;i<n;i++){
        queue<pair<int,int>> q;//node,parent
        if(!vis[i])
        {
            q.push({i,-1});
            vis[i]=1;
            while(!q.empty()){
                auto front=q.front();
                q.pop();
                int node=front.first;
                int parent=front.second;
                for(auto it:adj[node]){
                    
                    //Cleaner way to write this condition
                    // if(!vis[it]) {
                    //     q.push({it,node});
                    //     //remember to update vis array before adding it in queue
                    //     vis[it]=1;
                    // }
                    // else if(it!=parent) return true;
                    
                    //Don't write vis[it] && it!=parent condition here, else we will add visited node again and again which will lead to tle 
                    if(vis[it] == 1)
                    {
                        if(it!=parent) return true;   
                    }
                    else {
                        q.push({it, node});
                        vis[it] = 1;  // remember to update vis array before adding it to queue
                    }
                }
            }
        }
    }
    return false;
}

//dfs Approach
//we don't need pathvis for undirected graph case while finding if cycle is present
//TC->O(n+2*e) SC->O(n+n(recursion stack space))
bool dfs(int node,int parent, vector<vector<int>> &adj,vector<int> &vis){
    vis[node]=1;
    for(auto it:adj[node]){
        if(!vis[it]){
            //remember this step and don't simply return dfs(it,node,adj,vis) because maybe further we can detect cycle in same component
            if(dfs(it,node,adj,vis)) return true;
        }
        else if(it!=parent) return true;
    }
    return false;
}

bool isCycle(vector<vector<int>>& adj) {
    int n=adj.size();
    vector<int> vis(n,0);
    for(int i=0;i<n;i++){
        if(!vis[i]){
            if(dfs(i,-1,adj,vis)) return true;
        }
    }
    return false;
}

//01 Matrix- return the distance of the nearest 0 for each cell. So we will insert all zeroes in our queue and do bfs to get minimum distance of 1 and keep track of visited node.
//Here I have just updated matrix 1->0. But, maybe this is not a good way for industry level code
vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int n=mat.size();
    int m=mat[0].size();
    queue<pair<pair<int,int>,int>> q;// {x,y},dist
    vector<vector<int>> ans=mat;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mat[i][j]==0){
                //distance for cell having 0 will be 0
                q.push({{i,j},0});
            }
        }
    }
    vector<int> dx={1,-1,0,0};
    vector<int> dy={0,0,1,-1};
    while(!q.empty()){
        auto front=q.front();
        q.pop();
        int x=front.first.first;
        int y=front.first.second;
        int dist=front.second;
        for(int i=0;i<4;i++){
            int x_new=x+dx[i];
            int y_new=y+dy[i];
            if(x_new>=0 && x_new<n && y_new>=0 && y_new<m && mat[x_new][y_new]==1){
                mat[x_new][y_new]=0;
                q.push({{x_new,y_new},dist+1});
                ans[x_new][y_new]=dist+1;
            }
        }
    }
    return ans;
}   

//Surrounded regions
//bfs approach
//TC->O(n+m+4*n*m+n*m) SC->O(n*m(vis array)+n*m(queue))
void solve(vector<vector<char>>& board) {
    int n=board.size();
    int m=board[0].size();
    int lr[]={1,-1,0,0};
    int lc[]={0,0,-1,1};
    vector<vector<int>> vis(n,vector<int>(m,0));
    queue<pair<int,int>> q;
    for(int i=0;i<n;i++){
        if(board[i][0]=='O'){
            q.push({i,0});
            vis[i][0]=1;
            board[i][0]='a';
        }
        if(board[i][m-1]=='O'){
            q.push({i,m-1});
            vis[i][m-1]=1;
            board[i][m-1]='a';
        }
    }
    for(int j=1;j<m-1;j++){
        if(board[0][j]=='O'){
            q.push({0,j});
            vis[0][j]=1;
            board[0][j]='a';
        }
        if(board[n-1][j]=='O'){
            q.push({n-1,j});
            vis[n-1][j]=1;
            board[n-1][j]='a';
        }
    }

    while(!q.empty()){
        auto front=q.front();
        q.pop();
        int row=front.first;
        int col=front.second;
        for(int i=0;i<4;i++){
            int r=row+lr[i];
            int c=col+lc[i];
            if(r>=0 && c>=0 && r<n && c<m && vis[r][c]!=1 && board[r][c]=='O'){
                q.push({r,c});
                vis[r][c]=1;
                board[r][c]='a';
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(board[i][j]=='O') board[i][j]='X';
            else if(board[i][j]=='a') board[i][j]='O';
        }
    }
}
//dfs approach
//TC->O(n+m+4*n*m+n*m) SC->O(n*m(vis array)+n*m(recursion stack space))
void dfs(int x,int y,vector<vector<char>> &board, vector<vector<int>> &vis){
    int n=board.size();
    int m=board[0].size();
    vis[x][y]=1;
    board[x][y]='a';
    vector<int> dx={0,0,1,-1};
    vector<int> dy={1,-1,0,0};
    for(int i=0;i<4;i++){
        int new_x=x+dx[i];
        int new_y=y+dy[i];
        if(new_x>=0 && new_x<n && new_y>=0 && new_y<m && vis[new_x][new_y]==0 && board[new_x][new_y]=='O'){
            dfs(new_x,new_y,board,vis);
        }
    }
}

void solve(vector<vector<char>>& board) {
    int n=board.size();
    int m=board[0].size();
    int lr[]={1,-1,0,0};
    int lc[]={0,0,-1,1};
    vector<vector<int>> vis(n,vector<int>(m,0));
    for(int i=0;i<n;i++){
        if(board[i][0]=='O'){
            dfs(i,0,board,vis);
        }
        if(board[i][m-1]=='O'){
            dfs(i,m-1,board,vis);
        }
    }
    for(int j=1;j<m-1;j++){
        if(board[0][j]=='O'){
            dfs(0,j,board,vis);
        }
        if(board[n-1][j]=='O'){
            dfs(n-1,j,board,vis);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(board[i][j]=='O') board[i][j]='X';
            else if(board[i][j]=='a') board[i][j]='O';
        }
    }
}

//Bipartite graph (here we are also considering case of connected components)
//It's coloring approach and checking if already visited node follows criteria of bipartite, if no, return false
//bfs or dfs both will work
//TC->O(n+2e+n(connected components loop)) SC->O(n(vis)+n(queue)) y=using bfs
bool solve(int i,vector<vector<int>> &graph,vector<int> &vis){
    int n=graph.size();
    queue<int> q; //store color of node
    q.push(i);
    vis[i]=0;
    int color=0;
    while(!q.empty()){
        int k=q.size();
        color=!color;
        while(k--){
            int front=q.front();
            q.pop();
            for(auto it:graph[front]){
                if(vis[it]==-1){
                    vis[it]=color;
                    q.push(it);
                }
                else if(vis[it]!=color){
                    return false;
                }
            }
        }
    }
    return true;
}
bool isBipartite(vector<vector<int>>& graph) {
    int n=graph.size();
    vector<int> vis(n,-1); //in visited we will store color, -1 if not visited
    for(int i=0;i<n;i++){
        if(vis[i]==-1){
            if(!solve(i,graph,vis)) return false;
        }
    }
    return true;
}
//using dfs
//TC->O(n+2e+n(connected components)) SC->O(n(vis)+n(recursion stack))
bool dfs(int i,vector<vector<int>> &graph,vector<int> &vis,int col){
    vis[i]=col;
    for(auto it:graph[i]){
        if(vis[it]==-1){
            if(!dfs(it,graph,vis,!col)) return false;
        }
        else if(vis[it]==col){
            return false;
        }
    }
    return true;
}

bool isBipartite(vector<vector<int>>& graph) {
    int n=graph.size();
    vector<int> vis(n,-1); //in visited we will store color, -1 if not visited
    for(int i=0;i<n;i++){
        if(vis[i]==-1){
            if(!dfs(i,graph,vis,0)) return false;
        }
    }
    return true;
}

//REMEMBER -  DFS is more prone to higher memory usage due to recursion depth, while BFS is more memory-efficient in optimal cases.


//cycle detection in directed graph (use pathvis)
//scheduling 
//used dfs, can use bfs also
//Remember we should push element into answer vector while backtracking in such cases
//e.g. to understand this
// 0 → 1 → 2  
//   ↘     ↓  
//      3 → 4  
//here if we push while traversing (0,1,2,4,3) which is incorrect it should be (0,1,2,3,4)
//and keep track of pathvis to detect cycle on the way because if cycle is present we can't do scheduling ans={}
//getting TLE by dfs -Resolved it by using reference for all parameters

//IMPORTANT: When parameters (like vectors) are passed by value, C++ creates a copy of the entire vector for every
//recursive function call. This copying operation has a time complexity of O(n) for each call where n is the size of the vector.
//When you pass parameters by reference (&), C++ does not create a copy. Instead, it provides access to the original memory location, 
//making the function calls efficient.

//remember the condition if vis[it] && it!=parent is incorrect in case of directed graph because otherwise unnecessary cycles will be detected which is not required

//need to optimise it using bfs
bool dfs(int i,vector<int> &vis,vector<int> &ans,vector<vector<int>> adj,vector<int> pathvis){
    vis[i]=1;
    pathvis[i]=1;
    //don't insert element here as it will be preorder
    // ans.push_back(i);
    for(auto it:adj[i]){
        if(!vis[it]){
            //detecting cycle as well on the way
            if(dfs(it,vis,ans,adj,pathvis)){
                return true;
            }
        }
        else if(pathvis[it]) return true;
    }
    //insert here as in this case we need postorder and last element will have no dependencies so we can push it
    ans.push_back(i);
    return false;
}

vector<int> findOrder(int n, vector<vector<int>>& p) {
    vector<int> ans;
    vector<vector<int>> adj(n);
    int m=p.size();
    for(int i=0;i<m;i++){
        adj[p[i][1]].push_back(p[i][0]);
    }
    vector<int> pathvis(n,0);
    vector<int> vis(n,0);
    for(int i=0;i<n;i++){
        if(!vis[i]){
            if(dfs(i,vis,ans,adj,pathvis)) return {};
        }
    }
    //important 
    reverse(ans.begin(),ans.end());
    return ans;
}

//bfs approach
vector<int> findOrder(int n, vector<vector<int>>& p) {
    vector<int> ans;
    vector<vector<int>> adj(n);
    vector<int> indegree(n,0);
    int m=p.size();
    for(int i=0;i<m;i++){
        adj[p[i][1]].push_back(p[i][0]);
        indegree[p[i][0]]++;
    }
    queue<int> q;
    for(int i=0;i<n;i++){
        if(indegree[i]==0) q.push(i);
    }
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
    //important condition , EDGE CASE, what if indegree of all elements does not become zero because of cycle present
    if(ans.size()!=n) return {};
    return ans;
}

//WordLadder 1
//TC->O(klogk+k*n*26*logk*logk) SC->O(k(set)+k(queue)+k(map))
//we can reduce this space complexity by not using map and erasing words used from set itself using st.erase(word) before pushing it to queue to reduce redundancy
int ladderLength(string beginWord, string endWord, vector<string>& wordlist) {
    int n=beginWord.size();
    int m=endWord.size();
    if(n!=m) return 0;
    int ans=0;
    int k=wordlist.size();
    set<string> st;
    for(int i=0;i<k;i++){
        st.insert(wordlist[i]);
    }
    if(st.find(endWord)==st.end()) return 0;
    queue<pair<string,int>> q; // word,level
    map<string,int> mp;
    q.push({beginWord,1});
    mp[beginWord]=1;
    while(!q.empty()){
        string word=q.front().first;
        int level=q.front().second;
        q.pop();
        if(word==endWord){
            return level;
        }
        cout<<level<<" ";;
        for(int i=0;i<n;i++){
            char track=word[i];
            for(char j='a';j<='z';j++){
                word[i]=j;
                if(st.find(word)!=st.end() && !mp[word]){
                    q.push({word,level+1});
                    mp[word]=1;
                }
            }
            word[i]=track;
        }
    }
    return ans;
}

//Word ladder 2
//Remember here not to remove word from set inside k-- loop as other paths can use that same word at that level
//Also keep track of words to be erased from set at each level
vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordlist) {
    set<string> st;
    vector<vector<string>> ans;
    int n=wordlist.size();
    int l=beginWord.size();
    for(int i=0;i<n;i++){
        if(wordlist[i]==beginWord) continue;
        st.insert(wordlist[i]);
    }
    queue<vector<string>> q;
    q.push({beginWord});
    while(!q.empty()){
        if(ans.size()>=1) return ans;
        int k=q.size();
        vector<string> to_delete_from_set;
        while(k--){
            auto front=q.front();
            q.pop();
            for(int i=0;i<l;i++){
                string temp=*front.rbegin();
                for(char j='a';j<='z';j++){
                    vector<string> tvec=front;
                    temp[i]=j;
                    if(st.find(temp)!=st.end()){
                        tvec.push_back(temp);
                        q.push(tvec);
                        if(temp==endWord) ans.push_back(tvec);
                        to_delete_from_set.push_back(temp);
                    }
                }   
            }
        }
        int j=to_delete_from_set.size();
        for(int i=0;i<j;i++){
            st.erase(to_delete_from_set[i]);
        }
    }
    return ans;
}
