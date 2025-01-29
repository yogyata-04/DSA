#include<bits/stdc++.h>
using namespace std;

//finding maximum element in an array 
// TC->O(n) SC->O(1) 
int maximumEl(vector<int> vec){
    int maxi=0;
    int n=vec.size();
    for(int i=0;i<n;i++){
        if(vec[i]>maxi){
            maxi=vec[i];
        }
    }
    return maxi;
}

//finding second minimum element in array
//TC->O(n) SC->O(1)
//remember to put condition vec[i]!=maxi in else if condition else if we have two maximums then second maxi = maxi which we don't want
int secondMaximumEl(vector<int> vec){
    int maxi=0;
    int second_maxi=0;
    int n=vec.size();
    for(int i=0;i<n;i++){
        if(vec[i]>maxi){
            second_maxi=maxi;
            maxi=vec[i];
        }
        else if(vec[i]>second_maxi && vec[i]!=maxi){
            second_maxi=vec[i];
        }
    }
    return second_maxi;
}

//Check if Array Is Sorted and Rotated (Here clockwise and anticlockwise is gonna make no difference)
//TC->O(n) SC->O(1)
//remember to increment start in second for loop
bool sortedNrotated(vector<int> vec){
    int n=vec.size();
    int start=-1;
    for(int i=1;i<n;i++){
        if(vec[i]<vec[i-1]){
            start=i;
            break;
        }
    }
    if(start==-1) return true;
    for(int i=0;i<n-1;i++){
        if(vec[start%n]>vec[(start+1)%n]) return false;
        start++;
    }
    return true;
}

//Remove duplicates from array sorted in non-decreasing order
//TC->O(n) SC->O(1)
int removeDuplicates(vector<int> &vec){
    int n=vec.size();
    int current_insertion_index=0;
    for(int i=0;i<n-1;i++){
        if(vec[i]!=vec[i+1]){
            swap(vec[current_insertion_index],vec[i]);
            current_insertion_index++;
        }
    }
    swap(vec[current_insertion_index],vec[n-1]);
    return current_insertion_index+1;
}

//left and right rotate an array by d places
//TC->O(n) SC->O(1)

void leftRotate(vector<int> &vec, int d){
    int n=vec.size();
    d=d%n;
    reverse(vec.begin(),vec.begin()+d);
    reverse(vec.begin()+d,vec.end());
    reverse(vec.begin(),vec.end());
}

void rightRotate(vector<int> &vec, int d){
    int n=vec.size();
    d=d%n;
    reverse(vec.begin(),vec.end()-d);
    reverse(vec.end()-d,vec.end());
    reverse(vec.begin(),vec.end());
}

//move zeroes to end
//TC->O(n) SC->O(1)
void zeroestoend(vector<int> &vec){
    int n=vec.size();
    int zero_pos=-1;
    for(int i=0;i<n;i++){
        if(vec[i]==0) {
            zero_pos=i;
            break;
        }
    }
    if(zero_pos==-1) return;
    for(int i=zero_pos;i<n;i++){
        if(vec[i]!=0){
            swap(vec[i],vec[zero_pos]);
            zero_pos++;
        }
    }
}

//Linear search - O(n) easy code only

//Find the union of two sorted arrays
//TC->O(n+m) SC->O(n+m)
vector<int> unionofarrays(vector<int> vec1,vector<int> vec2){
    int n=vec1.size();
    int m=vec2.size();
    vector<int> uni;
    int i=0,j=0;
    while(i<n && j<m){
        while(i+1<n && vec1[i]==vec1[i+1]){
            i++;
        }
        while(j+1<m && vec2[j]==vec2[j+1]){
            j++;
        }
        if(vec1[i]==vec2[j]){
            uni.push_back(vec1[i]);
            i++;
            j++;
        }
        else{
            if(vec1[i]<vec2[j]){
                uni.push_back(vec1[i]);
                i++;
            }
            else{
                uni.push_back(vec2[j]);
                j++;
            }
        }
    }
    while(i<n){
        while(i+1<n && vec1[i]==vec1[i+1]){
            i++;
        }
        uni.push_back(vec1[i]);
        i++;
    }
    while(j<m){
        while(j+1<m && vec2[j]==vec2[j+1]){
            j++;
        }
        uni.push_back(vec2[j]);
        j++;
    }
    return uni;
}

//another approach for finding union
//TC->O(n+m) SC->O(n+m)
//It's a cleaner approach
vector<int> unionofarrays2(vector<int> vec1,vector<int> vec2){
    int n=vec1.size();
    int m=vec2.size();
    vector<int> uni;
    int i=0,j=0;
    while(i<n && j<m){
        if(vec1[i]<=vec2[j]){
            if(uni.size()==0 || vec1[i]!=uni.back()) uni.push_back(vec1[i]);
            i++;
        }
        else{
            if(uni.size()==0 || vec2[j]!=uni.back()) uni.push_back(vec2[j]);
            j++;
        }
    }
    while(i<n){
        if(vec1[i]!=uni.back()) uni.push_back(vec1[i]);
        i++;
    }
    while(j<m){
        if(vec2[j]!=uni.back()) uni.push_back(vec2[j]);
        j++;
    }
    return uni;
}

//Find missing number in an array containing numbers from [0,n]
//TC->O(n) SC->O(1)
int missingnum(vector<int> vec){
    int n=vec.size();
    int req_sum=(n*(n+1))/2;
    int sum=0;
    for(int i=0;i<n;i++){
        sum+=vec[i];
    }
    return req_sum-sum;
}

//xor approach
int missingnumxor(vector<int> vec){
    int n=vec.size();
    int req_xor=0;
    int vec_xor=0;
    for(int i=0;i<n;i++){
        req_xor^=i;
        vec_xor^=vec[i];
    }
    req_xor^=n;
    return req_xor^vec_xor;
}

//maximum consecutive ones in an array
//TC->O(n) SC->O(1)
int maximum_consecutive_ones(vector<int> vec){
    int n=vec.size();
    int i=0;
    int ans=0;
    while(i<n){
        int temp=0;
        while(i<n && vec[i]==1){
            i++;
            temp++;
        }
        ans=max(ans,temp);
        i++;
    }
    return ans;
}

//Find the number that appears once, and other numbers twice
//TC->O(n) SC->O(1)
int single_number(vector<int> vec){
    int n=vec.size();
    int ans=0;
    for(int i=0;i<n;i++){
        ans^=vec[i];
    }
    return ans;
}

int main(){
    vector<int> vec1={4,1,2,1,2};
    vector<int> vec2={3,4,4,5,6};
    int ans;
    ans=single_number(vec1);
    cout<<ans;
}