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

//boundary traversal of binary tree
//TC->O(h+n+h) SC->O(3n);
vector<int> boundaryleft(Node* root){
    if(root==NULL) return {};
    vector<int> left;
    while(root->left || root->right){
        left.push_back(root->data);
        if(root->left) root=root->left;
        else if(root->right) root=root->right;
    }
    return left;
}

void boundarybottom(Node* root,vector<int> &bottom){
    if(root==NULL) return;
    if(!root->left && !root->right) bottom.push_back(root->data);
    if(root->left) boundarybottom(root->left,bottom);
    if(root->right) boundarybottom(root->right,bottom);
}

vector<int> boundaryright(Node* root){
    if(root==NULL) return {};
    vector<int> right;
    while(root->left || root->right){
        right.push_back(root->data);
        if(root->right) root=root->right;
        else if(root->left) root=root->left;
    }
    reverse(right.begin(),right.end());
    return right;
}

//remember here right traversal should have root->right and not root else what if tree is scewed, then left and right traversal will be same which is wrong
void boundarytraversal(Node* root){
    if(root==NULL) return ;
    vector<int> left=boundaryleft(root);
    vector<int> right;
    if(root->right) right=boundaryright(root->right);
    vector<int> bottom;
    boundarybottom(root,bottom);
    for(auto it:left){
        cout<<it<<" ";
    }
    for(auto it:bottom){
        cout<<it<<" ";
    }
    int n=right.size();
    for(int i=0;i<n;i++){
        cout<<right[i]<<" ";
    }
}

//vertical order traversal
vector<vector<int>> verticaltraversal(Node* root){
    vector<vector<int>> ans;
    map<int,vector<int>> mp;
    queue<pair<Node*, pair<int,int>>> q;
    q.push({root,{0,0}});
    while(!q.empty()){
        int n=q.size();
        while(n--){
            auto front=q.front();
            q.pop();
            int x=front.second.first;
            int y=front.second.second;
            Node* curr=front.first;
            mp[x].push_back(curr->data);
            if(curr->left){
                q.push({curr->left,{x-1,y+1}});
            }
            if(curr->right){
                q.push({curr->right,{x+1,y+1}});
            }
        }
    }
    for(auto it:mp){
        ans.push_back(it.second);
    }
    return ans;
}

//vertical order traversal if we need nodes at same x,y in sorted order
//TC->O(n*logn*logn*logn) SC->O(n(map)+n/2(max space occupied by queue))
//Multiset Operations to insert overlapping nodes at a specific vertical and horizontal level also takes O(log2N) complexity.
//Map operations involve insertion and retrieval of nodes with their vertical and level as their keys. Since there are two nested maps, the total time complexity becomes O(log2N)*O(log2N).
//remember here we need to use multiset if we want to have sorted orded of nodes at same x,y value, else we can simply use map<int,vector<int,int>>
vector<vector<int>> verticaltraversal(Node* root){
    vector<vector<int>> ans;
    map<int,map<int,multiset<int>>> mp;
    queue<pair<Node*, pair<int,int>>> q;
    q.push({root,{0,0}});
    while(!q.empty()){
        int n=q.size();
        while(n--){
            auto front=q.front();
            q.pop();
            int x=front.second.first;
            int y=front.second.second;
            Node* curr=front.first;
            mp[x][y].insert(curr->data);
            if(curr->left){
                q.push({curr->left,{x-1,y+1}});
            }
            if(curr->right){
                q.push({curr->right,{x+1,y+1}});
            }
        }
    }
    //IMPORTANT syntax
    for(auto it:mp){
        vector<int> col;
        for(auto level:it.second){
            col.insert(col.end(),level.second.begin(),level.second.end());
        }
        ans.push_back(col);
    }
    return ans;
}

//top view of binary tree
//TC->O(n*logn) SC->O(n/2+n/2)
vector<int> topview(Node* root){
    if(root==NULL) return {};
    queue<pair<Node*,pair<int,int>>>q;
    q.push({root,{0,0}});
    vector<int> ans;
    map<int,int> mp;
    while(!q.empty()){
        int n=q.size();
        while(n--){
            auto front=q.front();
            q.pop();
            int x=front.second.first;
            int y=front.second.second;
            Node* curr=front.first;
            if(!mp[x]) mp[x]=curr->data;
            if(curr->left){
                q.push({curr->left,{x-1,y+1}});
            }
            if(curr->right){
                q.push({curr->right,{x+1,y+1}});
            }
        }
    }
    for(auto it:mp){
        ans.push_back(it);
    }
    return ans;
}

//bottom view of binary tree
//TC->O(n) SC->O(n/2+n/2)
vector <int> bottomView(Node *root) {
    // Your Code Here
    if(root==NULL) return {};
    queue<pair<Node*,pair<int,int>>>q;
    q.push({root,{0,0}});
    vector<int> ans;
    map<int,int> mp;
    while(!q.empty()){
        int n=q.size();
        while(n--){
            auto front=q.front();
            q.pop();
            int x=front.second.first;
            int y=front.second.second;
            Node* curr=front.first;
            mp[x]=curr->data;
            if(curr->left){
                q.push({curr->left,{x-1,y+1}});
            }
            if(curr->right){
                q.push({curr->right,{x+1,y+1}});
            }
        }
    }
    for(auto it:mp){
        ans.push_back(it.second);
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
