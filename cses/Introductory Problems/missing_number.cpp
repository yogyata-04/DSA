#include<bits/stdc++.h>
using namespace std;

// find missing number

int main(){
    int n;
    cin>>n;
    vector<int> vec(n-1);
    int sum=0;
    int req_sum=(n*(n+1))/2;
    for(int i=0;i<n-1;i++){
        cin>>vec[i];
        sum+=vec[i];
    }
    int val=req_sum-sum;
    cout<<val;
}
