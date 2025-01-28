#include<bits/stdc++.h>
using namespace std;

//put larger element to right by swapping iteratively
void bubblesort(vector<int> &vec){
    int n=vec.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(vec[j]>vec[j+1]){
                swap(vec[j],vec[j+1]);
            }
        }
    }
}

//put smaller element to current index
void selectionsort(vector<int> &vec){
    int n=vec.size();
    for(int i=0;i<n;i++){
        int mini_ind=i;
        for(int j=i;j<n;j++){
            if(vec[j]<vec[mini_ind]){
                mini_ind=j;
            }
        }
        swap(vec[i],vec[mini_ind]);
    }
}

//put element at it's correct position for selected sorted array from left and the current element
void insertionsort(vector<int> &vec){
    int n=vec.size();
    for(int i=1;i<n;i++){
        int j=i;
        while(j>0 && vec[j]<vec[j-1]){
            swap(vec[j],vec[j-1]);
            j--;
        }
    }
}

//here we use extra temp vector,i.e., O(N) auxiliary space
//what is auxiliary space? - extra space used by an algorithm other than to store input data (additional memory required)
void merge(vector<int> &vec,int left,int mid,int right){
    int it1=left;
    int it2=mid+1;
    vector<int> temp;
    while(it1<=mid && it2<=right){
        if(vec[it1]<vec[it2]){
            temp.push_back(vec[it1]);
            it1++;
        }
        else{
            temp.push_back(vec[it2]);
            it2++;
        }
    }
    while(it1<=mid){
        temp.push_back(vec[it1]);
        it1++;
    }
    while(it2<=right){
        temp.push_back(vec[it2]);
        it2++;
    }
    for(int i=left;i<=right;i++){
        vec[i]=temp[i-left];
    }
}

void mergesort(vector<int> &vec,int left,int right){
    if(left>=right) return;
    int mid=left+(right-left)/2;
    mergesort(vec,left,mid);
    mergesort(vec,mid+1,right);
    merge(vec,left,mid,right);
}

//remember here i=left and not left+1 and return j not i-1
//here we do not need extra space of O(n) unlike mergesort so better than mergesort
int partition(vector<int> &vec,int left,int right){
    int pivot=vec[left];
    int i=left;
    int j=right;
    while(i<j){
        while(vec[i]<=pivot && i<j){
            i++;
        }
        while(vec[j]>pivot && j>=i){
            j--;    
        }
        if(i<j){
            swap(vec[i],vec[j]);
        }
    }
    swap(vec[left],vec[j]);
    return j;
}

void quicksort(vector<int> &vec,int left,int right){
    if(left>=right) return;
    int partition_ind=partition(vec,left,right);
    quicksort(vec,left,partition_ind-1);
    quicksort(vec,partition_ind+1,right);
}

int main(){
    vector<int> vec={6,7,8,1,2,4,3};
    int n=vec.size();
    quicksort(vec,0,n-1);
    for(int i=0;i<n;i++){
        cout<<vec[i]<<" ";    
    }
}