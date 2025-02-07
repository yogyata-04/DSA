#include<bits/stdc++.h>
using namespace std;

//print root to node path in a binary tree
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
    return 1+count(root->left)+count(right->right);
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

//Construct the Binary Tree from Postorder and Inorder Traversal

//Serialize and deserialize Binary Tree

int main(){
    
}
