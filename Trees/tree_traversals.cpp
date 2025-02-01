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

//**********************TRAVERSALS***********************************//

//PREORDER TRAVERSAL (root left right) TC->O(n) SC->O(height of tree) recursion stack space
void preorder(Node* root){
    if(root==NULL) return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

//ITERATIVE PREORDER TRAVERSAL TC->O(n) SC-> figure it out
void iterativepreorder(Node* root){
    if(root==NULL) return;
    stack<Node*> st;
    st.push(root);
    while(!st.empty()){
        auto top=st.top();
        st.pop();
        cout<<top->data<<" ";
        if(top->right) st.push(top->right);
        if(top->left) st.push(top->left);
    }
}

//INORDER TRAVERSAL (left root right) TC->O(n) SC->O(height of tree) recursion stack space
void inorder(Node* root){
    if(root==NULL) return;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

//ITERATIVE INORDER TRAVERSAL TC->O(n) figure out space complexity
void iterativeinorder(Node* root){
    if(root==NULL) return;
    map<Node*,int> vis;
    
    stack<Node*> st;
    if(root->right) st.push(root->right);
    st.push(root);
    vis[root]=1;
    if(root->left) st.push(root->left);
    
    while(!st.empty()){
        auto top=st.top();
        st.pop();
        if(vis[top]==0){
            vis[top]=1;
            if(top->right) st.push(top->right);
            st.push(top);
            if(top->left) st.push(top->left);
        }
        else cout<<top->data<<" ";
    }
}
 
//POSTORDER TRAVERSAL (left right root) TC->O(n) SC->O(height of tree) recursion stack space
void postorder(Node* root){
    if(root==NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}

//LEVEL ORDER TRAVERSAL ()
vector<vector<int>> levelorder(Node* root){
    if(root==NULL) return {{}};
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

//POSTORDER TRAVERSAL USING 2 STACKS

//POSTORDERTRAVERSAL USING 1 STACK

//ALL TRAVERSAL IN ONE GO

//*******************************************************************//

//power function n^m (optimised function) 
int power(int n,int m){
    if(m==0) return 1;
    int temp=power(n,m/2);
    if(m%2==0) return temp*temp;
    return n*temp*temp;
}

//nodes at a level in binary tree //0-indexing
int node_at_level(int i){
    return power(2,i);
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
    iterativepreorder(root);
    cout<<endl;
    iterativeinorder(root);
    cout<<endl;
    postorder(root);
    cout<<endl;
    
    vector<vector<int>> vec;
    vec=levelorder(root);
    for(auto it:vec){
        for(auto i:it){
            cout<<i<<" ";
        }
        cout<<endl;
    }
}
