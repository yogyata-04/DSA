#include<bits/stdc++.h>
using namespace std;

//print root to node path in a binary tree
//consideration - no two nodes have same value and path exists
//TC->O(n) + SC->O(n+logn(for temp vector))
void traversal(Node* root,vector<vector<int>> &vec,vector<int> temp){
    if(root==NULL) return;
    temp.push_back(root->data);
    if(!root->left && !root->right){
        vec.push_back(temp);
        return;
    }
    if(root->left) traversal(root->left,vec,temp);
    if(root->right) traversal(root->right,vec,temp);
    temp.pop_back();
}

vector<vector<int>> Paths(Node* root) {
    // code here
    vector<vector<int>> ans;
    vector<int> temp;
    traversal(root,ans,temp);
    return ans;
}

//Find lowest common ancestor for given two nodes
//Cases one is parent of other/ one lie on left and other on right
//TC->O(n) SC->O(logn) recursive stack space
bool solve(TreeNode* root, TreeNode* p, TreeNode* q,TreeNode* &ans){
    if(root==NULL) return false;
    auto left=solve(root->left,p,q,ans);
    auto right=solve(root->right,p,q,ans);
    //one lie on left and other on right
    if(left && right) ans=root;
    //one is parent of other
    if((root==p || root==q) && (left||right)) ans=root;
    return root==p || root==q || left || right;
}
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* ans=root;
    solve(root,p,q,ans);
    return ans;
}

#include<bits/stdc++.h>
using namespace std;

//Maximum width of binary Tree
//TC->O(n) SC->O(n)
//Remember to use start index and subtract it from curr index otherwise integer overflow error can come
int widthOfBinaryTree(TreeNode* root) {
    if(root==NULL) return 0;
    queue<pair<TreeNode*,long long>> q;
    int ans=1;
    q.push({root,1});
    while(!q.empty()){
        int n=q.size();
        int start=q.front().second;
        long long min_index=INT_MAX;
        long long max_index=INT_MIN;
        while(n--){
            auto front=q.front();
            q.pop();
            long long index=front.second-start;
            min_index=min(min_index,index);
            max_index=max(max_index,index);
            auto node=front.first;
            if(node->left){
                q.push({node->left,2*(index)+1});
            }
            if(node->right){
                q.push({node->right,2*(index-1)+2});
            }
        }
        ans=max(ans,(int)(max_index-min_index)+1);
    }
    return ans;
}

//check for children sum property
//TC->O(n) SC->O(height)
bool childrensum(TreeNode* root){
    //handling edge case when node is null or is leaf node
    if(root==NULL || (root->left==NULL && root->right==NULL)) return true;
    bool left=true,right=true;
    if(root->left) left=childrensum(root->left);
    if(root->right) right=childrensum(root->right);
    if(!left || !right) return false;
    int sum=0;
    //remember this step as it might be possible only one child is present of given node and not two
    if(root->left) sum+=root->left->val;
    if(root->right) sum+=root->right->val;
    return sum==root->val;
}


//Print all the Nodes at a distance of K in a Binary Tree
//consider parent, left, right for each node and do bfs
//Edge case- when k=0 return vector containing target, when root is NULL return {};
//also don't miss condition of !vis while adding nodes at certain level
//level order traversal is used 2 times, one to add ancestors/parents, another to check level k
//TC->O(n(adding parents)+n(bfs)) SC->O(n(parent map)+n(queue)+n(vis map)+m(answer nodes))
vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    vector<int> ans;
    
    //Edge case
    if(!root) return ans;
    //store parents of each node
    map<TreeNode*,TreeNode*> mp;
    queue<TreeNode*> q;
    q.push(root);
    mp[root]=NULL;
    while(!q.empty()){
        auto front=q.front();
        q.pop();
        if(front->left){
            q.push(front->left);
            mp[front->left]=front;
        }
        if(front->right){
            q.push(front->right);
            mp[front->right]=front;
        }
    }
    int level=0;
    q.push(target);
    //keep track of visited nodes so that we don't visit them multiple times
    map<TreeNode*,bool> vis;
    vis[target]=true;

    //Edge case
    if(level==k){
        ans.push_back(target->val);
        return ans;
    }
    //we could have also kept it inside while loop before incrementing level

    while(true){
        level++;
        int n=q.size();
        while(n--){
            auto front=q.front();
            q.pop();
            //add parents
            if(mp[front] && !vis[mp[front]]){
                q.push(mp[front]);
                vis[mp[front]]=true;
            }
            //add left child
            if(front->left && !vis[front->left]){
                q.push(front->left);
                vis[front->left]=true;
            }
            //add right child 
            if(front->right && !vis[front->right]){
                q.push(front->right);
                vis[front->right]=true;
            }
        }
        if(level==k){
            while(!q.empty()){
                ans.push_back((q.front())->val);
                q.pop();
            }
            return ans;
        }
    }
    return ans;
}

//Minimum time taken to BURN the Binary Tree from a Node
//we can solve it using above concept only just we don't have to stop at k level this time

//Count total Nodes in a COMPLETE Binary Tree
//A Complete Binary Tree is a binary tree in which all levels are completely filled, 
//except possibly for the last level, and all nodes are as left as possible
//TC->O(logn*logn) SC->O(height) recursive stack space
//We are sure that no. of iterations in countNodes function will be logn times only because in each 
//iteration we are sure that either left tree will be complete binary tree or right tree will be complete
//binary tree, so we will go to either left or right in each iteration making it equal to height of tree
int countNodes(TreeNode* root){
    if(root==NULL) return 0;
    //Don't do mistake here by putting leftheight(root->left) and rightheight(root->right)
    int left=leftheight(root);
    int right=rightheight(root);
    if(left==right) return pow(2,left)-1; 
    return 1+countNodes(root->left)+countNodes(right->right);
}

int leftheight(TreeNode* root){
    int h=0;
    while(root){
        root=root->left;
        h++;
    }
    return h;
}

int rightheight(TreeNode* root){
    int h=0;
    while(root){
        root=root->right;
        h++;
    }
    return h;
}

//requirements needed to build a unique binary tree- preorder/postorder and inorder

//construct binary tree from preorder and inorder traversal
void indexing(vector<int> &inorder, map<int,int> &mp){
    int n = inorder.size();
    for(int i = 0; i < n; i++){
        mp[inorder[i]] = i; // Store the index of each element from inorder[] in the map
    }
}

TreeNode* helper(vector<int> &preorder, vector<int> &inorder, int instart, int inend, int prestart, int preend, map<int,int> &mp){
    if(instart > inend || prestart > preend) return NULL; // Base condition: if the range is invalid, return NULL
    
    // Create a new node with the value from preorder[prestart]
    TreeNode* Root = new TreeNode(preorder[prestart]);
    
    // Find the index of the root in inorder traversal
    int inRoot = mp[Root->val];
    
    // Calculate the number of elements in the left subtree
    int size = inRoot - instart;
    
    // Build the left subtree
    Root->left = helper(preorder, inorder, instart, inRoot - 1, prestart + 1, prestart + size, mp);
    
    // Build the right subtree
    Root->right = helper(preorder, inorder, inRoot + 1, inend, prestart + size + 1, preend, mp);
    
    return Root; // Return the root node of the constructed subtree
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    map<int, int> mp; // Map to store the index of each value in the inorder traversal
    indexing(inorder, mp); // Fill the map with inorder indices
    int n = preorder.size(); // Number of elements in the tree
    
    // Call the helper function to build the tree
    return helper(preorder, inorder, 0, n - 1, 0, n - 1, mp);
}

//Construct the Binary Tree from Postorder and Inorder Traversal
void indexing(vector<int> &inorder, map<int,int> &mp){
    int n=inorder.size();
    for(int i=0;i<n;i++){
        mp[inorder[i]]=i;
    }
}

TreeNode* helper(vector<int> &postorder, vector<int> &inorder,int instart,int inend, int poststart, int postend, map<int,int> &mp){
    if(instart>inend || poststart>postend) return NULL;
    TreeNode* Root=new TreeNode(postorder[postend]);
    int inRoot=mp[Root->val];
    int size=inRoot-instart;
    Root->left=helper(postorder,inorder,instart,inRoot-1,poststart,poststart+size-1, mp);
    Root->right=helper(postorder,inorder,inRoot+1,inend,poststart+size,postend-1,mp);
    return Root;
}


TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    map<int,int> mp; //to store indexes of roots in inorder vector
    indexing(inorder,mp);
    int n=postorder.size();
    return helper(postorder,inorder,0,n-1,0,n-1,mp);
}

//Serialize and deserialize Binary Tree
string serialize(TreeNode* root) {
    //we will perform level order traversal and for null we will store "#"
    string str="";
    if(root==NULL) return str;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        auto front=q.front();
        q.pop();
        if(front==NULL) {str+="#,";continue;}
        int node=front->val;
        string st=to_string(node);
        str+=st;
        str+=",";
        q.push(front->left);
        q.push(front->right);
    }
    return str;
}

// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
    //case when root is NULL
    if(data.size()==0) return NULL;
    stringstream s(data);
    string str;
    getline(s,str,',');
    TreeNode *root=new TreeNode(stoi(str));
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode* node=q.front();
        q.pop();
        getline(s,str,',');
        if(str=="#") {
            node->left=NULL;
        }
        else{
            node->left=new TreeNode(stoi(str));
            q.push(node->left);
        }
        getline(s,str,',');
        if(str=="#") {
            node->right=NULL;
        }
        else{
            node->right=new TreeNode(stoi(str));
            q.push(node->right);
        }
    } 
    return root;
}

//Morris Preorder traversal of binary tree
//TC->O(n) SC->O(1)
vector<int> inorderTraversal(TreeNode* root) {
    //threaded BT
    vector<int> ans;
    TreeNode* curr=root;
    while(curr){
        if(curr->left==NULL){
            ans.push_back(curr->val);
            curr=curr->right;
        }
        else{
            TreeNode* prev=curr->left;
            while(prev->right && prev->right!=curr){
                prev=prev->right;
            }
            if(prev->right==NULL){
                //create thread
                prev->right=curr;
                curr=curr->left;
            }
            else{
                //remove thread as it is already present
                ans.push_back(curr->val); //curr=prev->right
                prev->right=NULL;
                curr=curr->right;
            }
        }
    }
    return ans;
}

//Morris Inorder traversal of binary tree
vector<int> inorderTraversal(TreeNode* root) {
    //threaded BT
    vector<int> ans;
    TreeNode* curr=root;
    while(curr){
        if(curr->left==NULL){
            ans.push_back(curr->val);
            curr=curr->right;
        }
        else{
            TreeNode* prev=curr->left;
            while(prev->right && prev->right!=curr){
                prev=prev->right;
            }
            if(prev->right==NULL){
                //create thread
                prev->right=curr;
                ans.push_back(curr->val);
                curr=curr->left;
            }
            else{
                //remove thread as it is already present
                prev->right=NULL;
                curr=curr->right;
            }
        }
    }
    return ans;
}

//flatten binary tree
//TC->O(n) SC->O(1) 
//flatten using right pointer
void flatten(TreeNode* root) {
    TreeNode* curr = root;
    while (curr) {
        if (curr->left) {
            // Find the rightmost node in the left subtree (predecessor)
            TreeNode* pred = curr->left;
            while (pred->right != NULL) {
                pred = pred->right;
            }

            // Attach the right subtree to the rightmost node in left subtree
            pred->right = curr->right;

            // Move the left subtree to the right and set left to NULL
            //basically detaching it from right child and connecting with left subtree
            curr->right = curr->left;
            curr->left = NULL;
        }

        // Move to the next node in the list (right child)
        curr = curr->right;
    }
}
//flatten using left pointer
void flattenToLeft(TreeNode* root) {
    TreeNode* curr = root;
    while (curr != NULL) {
        if (curr->right != NULL) { // We work with the right subtree now
            // Find the leftmost node in the right subtree (predecessor on left side)
            TreeNode* pred = curr->right;
            while (pred->left != NULL) {
                pred = pred->left;
            }

            // Attach the left subtree to the leftmost node in the right subtree
            pred->left = curr->left;

            // Move the right subtree to the left, and set right to NULL
            curr->left = curr->right;
            curr->right = NULL;
        }

        // Move to the next node using the left pointer
        curr = curr->left;
    }
}

int main(){
    
}
