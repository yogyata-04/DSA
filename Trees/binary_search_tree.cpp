//duplicate nodes not allowed in BST

//search in bst
//TC->O(height) in balanced tree case height=log2n
TreeNode* searchBST(TreeNode* root, int val) {
    while(root!=NULL){
        if(root->val==val){
            return root;
        }
        if(root->val>val){
            root=root->left;
        }
        else{
            root=root->right;
        }
    }
    return root; //no such node
}

//min in BST - leftmost node 
//TC->O(height)
int minValue(Node* root) {
      if(root==NULL) return -1; 
      while(root->left!=NULL){
          root=root->left;
      }
      return root->data;
  }
//max in BST - rightmost node

//ceil in BST - Ceil(X) is a number that is either equal to X or is immediately greater than X
//TC->O(height) SC->O(1) 
int findCeil(Node* root, int input) {
    if (root == NULL) return -1;
    int ans=-1;
    while(root){
        if(root->data==input){
            return input;
        }
        else if(root->data<input){
            //move to right;
            root=root->right;
        }
        else{
            //move to left
            ans=root->data;
            root=root->left;
        }
    }
    return ans;
}

//floor in BST - Floor of a value refers to the value of the largest node in the Binary Search Tree that is smaller than or equal to the given key
int floorInBST(TreeNode* root, int key){
    int floor = -1;
    while(root){
        if(root->val == key){
            floor = root->val;
            return floor;
        }
        if(root->val<key){
            floor = root->val;
            root = root->right;
        }
        else{
            root = root->left;
        }
    }
    return floor;
}

//insert node in BST
TreeNode* insertIntoBST(TreeNode* temp, int val) {
      TreeNode* root=temp;
      if(root==NULL) {
          return new TreeNode(val);
      }
      
      TreeNode* node=new TreeNode(val);
      while(root){
          if(root->val>val){
              if(!root->left){
                  root->left=node;
                  break;
              }
              root=root->left;
          }
          else{
              if(!root->right){
                  root->right=node;
                  break;
              }
              root=root->right;
          }
      }
      return temp;
  }

//delete node in BST
