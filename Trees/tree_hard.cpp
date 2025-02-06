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
