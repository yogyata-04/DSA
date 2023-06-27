#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    int x;
    long long prod=1;
    int prev_index=1;
    for(int i=2;i<n;i++){
        prod*=i;
        if(prod%n==1){
            prod=1;
            prev_index=i;
        }
    }
    
    for(int i=1;i<=prev_index;i++){
        cout<<i<<" ";
    }

}
