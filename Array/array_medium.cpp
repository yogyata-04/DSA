#include<bits/stdc++.h>
using namespace std;

//2 sum problem (a+b=k)

//sort array of 0s, 1s and 2s 
void sort012(vector<int> &vec){
    //easy solution would be to count frequency of each number and then store them in array using loop -> TC: O(n+n) SC: O(1)
    int n=vec.size();
    //using dutch national flag TC-> O(n) SC->O(1)
    int left=0,mid=0,right=n-1; //0->left-1 : 0 , left->mid-1 : 1 , mid->right : unsorted , right+1->n-1 : 2
    while(mid<=right){
        if(vec[mid]==0){
            swap(vec[mid],vec[left]);
            left++;
            mid++;
            
        }
        else if(vec[mid]==1){
            mid++;
        }
        else{
            swap(vec[mid],vec[right]);
            right--;
        }
    }
}

//majority element >n/2 times TC->O(n) SC->O(1)
int majorityeln2(vector<int> vec){
    int el=vec[0];
    int cnt=1;
    int n=vec.size();
    for(int i=1;i<n;i++){
        if(vec[i]==el) cnt++;
        else{
            cnt--;
            if(cnt==0) {el=vec[i];cnt=1;}
        }
    }
    //count occurence of el now to confirm it occurs >n/2 times as there can be cases like 1,2,1,2,4,4 where el=4 in end but is not correct ans 
    cnt=0;
    for(int i=0;i<n;i++){
        if(vec[i]==el){
            cnt++;
        }
    }
    if(cnt>n/2) return el;
    return -1;
}

//maximum subarray sum TC->O(n) SC->O(1)
//Remember to have ans=vec[0] and not 0 as all values in array can be negative
//Also remember that first negative value can be less than next negative values which could lead to wrong answer if we just do sum=0 in else condition inside while loop
//So, have ans=max(ans,vec[i]) inside else as that negative can be more than previous negative number in ans in case of all negative numbers
int maxsubsum(vector<int> vec){
    int n=vec.size();
    int ans=vec[0];
    int sum=0;
    for(int i=0;i<n;i++){
        if(sum+vec[i]>0) {sum+=vec[i];ans=max(ans,sum);}
        else{
            ans=max(ans,vec[i]);
            sum=0;
        }
    }
    return ans;
}

//stock buy and sell TC->O(n) SC->O(1)
int stockprofit(vector<int> vec){
    int n=vec.size();
    int profit=0;
    int last_buy=vec[0];
    for(int i=0;i<n;i++){
        if(vec[i]>last_buy){
            profit=max(profit,vec[i]-last_buy);
        }
        last_buy=min(last_buy,vec[i]);
    }
    return profit;
}

//Rearrange the array in alternating positive and negative items. Consideration - no. of positives = no. of negatives
vector<int> alternatesignrearrange(vector<int> &vec){
    int n=vec.size();
    
    //by manipulating original vector
    // vector<int> pos,neg;
    // for(int i=0;i<n;i++){
    //     if(vec[i]<0) neg.push_back(vec[i]);
    //     else pos.push_back(vec[i]);
    // }
    // int i=0;
    // for(auto it:pos){
    //     vec[i]=it;
    //     i+=2;
    // }
    // i=1;
    // for(auto it:neg){
    //     vec[i]=it;
    //     i+=2;
    // }
    
    //we can also create new vector and not manipulate original vector
    vector<int> ans(n,0); 
    int i=0,j=1,k=0; // i is for position of pos and j for position of neg, k to keep traverse vector
    while(k<n){
        if(vec[k]<0){
            ans[j]=vec[k];
            k++;
            j+=2;
        }
        else{
            ans[i]=vec[k];
            k++;
            i+=2;
        }
    }
    return ans;
}

//next permutation for given vector TC->O(n+n+n) SC->O(1)
//remember here we do not need sorting just visulaise dip portion and you will understand
void nextpermutation(vector<int> &vec){
    int n=vec.size();
    int dip=-1;
    //finding dip
    for(int i=n-1;i>=1;i--){
        if(vec[i]>vec[i-1]){
            dip=i-1;
            break;
        }
    }
    if(dip==-1){reverse(vec.begin(),vec.end());return;}
    //now find element just greater than vec[dip]
    for(int i=n-1;i>dip;i--){
        if(vec[i]>vec[dip]){
            swap(vec[i],vec[dip]);
            break;
        }
    }
    reverse(vec.begin()+dip+1,vec.end());
    //sorting is not required here
    //sort(vec.begin()+dip+1,vec.end());
}

//leaders in an array - leader is element which is greater than all the elements to the right of it
//TC->O(n) SC->O(n)
vector<int> leaders(vector<int> vec){
    vector<int> ans;
    int n=vec.size();
    int maxi=INT_MIN;
    for(int i=n-1;i>=0;i--){
        if(vec[i]>maxi){
            ans.push_back(i);
            maxi=vec[i];
        }
    }
    return ans;
}

//longest consecutive sequence in an array

//set matrix zeroes
//remember to take col0 when doing space optimization
void setmatrixzeroes(vector<vector<int>> &vec){
    int n=vec.size();
    int m=vec[0].size();
    // vector<int> rows;
    // vector<int> cols;
    // int n=vec.size();
    // int m=vec[0].size();
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         if(vec[i][j]==0){
    //             rows.push_back(i);
    //             cols.push_back(j);
    //         }
    //     }
    // }
    // for(auto it:rows){
    //     for(int j=0;j<m;j++){
    //         vec[it][j]=0;
    //     }
    // }
    // for(auto it:cols){
    //     for(int i=0;i<n;i++){
    //         vec[i][it]=0;
    //     }
    // }
    
    //optimising space complexity
    int col0=vec[0][0];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(vec[i][j]==0){
                vec[i][0]=0;
                if(j==0){
                    col0=0;
                }
                else vec[0][j]=0;
            }
        }
    }
    
    for(int i=0;i<n;i++){
        if(vec[i][0]==0){
            for(int j=0;j<m;j++){
                vec[i][j]=0;
            }
        }
    }
    for(int j=0;j<m;j++){
        if(vec[0][j]==0){
            for(int i=0;i<n;i++){
                vec[i][j]=0;
            }
        }
    }
    vec[0][0]=col0;
}

//rotate image by 90 degrees (clockwise) nxn matrix TC->O(n*(n(traversing)+n(reversing))) SC->O(1) 
//if matrix size is nxm then we use conventional way to store it in vector size mxn and have new_vector[j][n-1-i]=vec[i][j]  TC->O(n*m) SC->O(m*n) 
void rotate90clock(vector<vector<int>> &vec){
    int n=vec.size();
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            swap(vec[i][j],vec[j][i]);
        }
        reverse(vec[i].begin(),vec[i].end());
    }
}

//Longest Consecutive Sequence in an Array

//print matrix in spiral order

//count subarrays with sum k


int main(){
    vector<vector<int>> vec={{1,2,3,4},
                            {5,0,7,8},
                            {0,10,11,12},
                            {13,14,15,0}};
    rotate90clock(vec);
    for(auto it:vec){
        for(auto i:it){
            cout<<i<<" ";
        }
        cout<<endl;
    }
}
