#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
        int data;
    Node* left=NULL;
    Node* right=NULL;
    Node(int val){
        data=val;
    }
};

//height of a binary tree
//TC->O(nodes) SC->(height)
//figure out why space compexity is not O(nodes)
int heighttree(Node* root){
    if(root==NULL) return 0;
    int left=heighttree(root->left);
    int right=heighttree(root->right);
    return max(left,right)+1;
}

//is given tree a balanced binary tree - |height(leftsubtree)-height(rightsubtree)|<=1 for all nodes
//remember the cases root->data==-1 || left==-1 || right==-1
//TC->O(n) SC->O(height) recursion stack space
int isbalancedBT(Node* root){
    if(root==NULL) return 0;
    if(root->data==-1) return -1;
    int left=isbalancedBT(root->left);
    if(left==-1) return -1;
    int right=isbalancedBT(root->right);
    if(right==-1|| abs(right-left)>1) return -1;
    return max(left,right)+1;
}

//diameter of binary tree (remember here we can't keep track of maximum diameter using recusive output so we need maxi variable)
//TC->O(n) SC->O(height) recursion stack space
int diameterBT(Node* root,int &maxi){
    if(root==NULL) return 0;
    int left=diameterBT(root->left,maxi);
    int right=diameterBT(root->right,maxi);
    maxi=max(left+right,maxi);
    return max(left,right)+1;
}

//maximum path sum
//remember here not to consider negative sum cases and convert such cases into 0; and then we can have max(left+right+root,maxi) as maxpathsum
//TC->O(n) SC->O(h) recursion stack space
int maxpathsum(Node* root,int &maxi){
    if(root==NULL) return 0;
    //we will not take negative sums further
    int left=max(0,maxpathsum(root->left,maxi));
    int right=max(0,maxpathsum(root->right,maxi));
    maxi=max(left+right+root->data,maxi);
    return max(left,right)+root->data;
}

//check if two trees are identical or not, i.e., left subtree is identical to right subtree for all nodes
//TC->O(min(n,m)) SC->O(min(h1,h2))
bool areidentical(Node* root1,Node* root2){
    if(root1==NULL || root2==NULL) return root1==root2;
    return areidentical(root1->left,root2->left) && areidentical(root1->right, root2->right) && root1->data==root2->data;
}

//zigzag traversal
//TC->O(n) SC->O(n/2) apx.;
vector<vector<int>> zigzaglevelorder(Node* root){
    if(root==NULL) return {};
    vector<vector<int>> ans;
    queue<Node*> q;
    q.push(root);
    int flag=1;
    while(!q.empty()){
        int n=q.size();
        flag=!flag;
        vector<int> temp;
        while(n--){
            auto front=q.front();
            q.pop();
            temp.push_back(front->data);
            if(front->left){
                q.push(front->left);
            }
            if(front->right){
                q.push(front->right);
            }
        }
        //for spiral manner
        if(flag) reverse(temp.begin(),temp.end());
        
        ans.push_back(temp);
    }
    return ans;
}

int main(){
    Node* root=new Node(1);
    root->left=new Node(2);
    root->right=new Node(3);
    root->left->left=new Node(4);
    root->left->right=new Node(5);
    root->left->right->left=new Node(6);
    root->left->right->right=new Node(7);
    root->right->right=new Node(8);
    root->right->right->left=new Node(9);
    vector<vector<int>> ans=zigzaglevelorder(root);
    
}
