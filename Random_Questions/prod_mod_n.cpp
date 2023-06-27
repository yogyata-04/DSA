//We are given a number n such that we consider array with elements 1,2,---,n-1 and now we have to remove minimum no. from array such that product of elements % n = 1
//Concept- (a*b)%n=(a%n)*(b%n)
//this solution is to be changed 
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
