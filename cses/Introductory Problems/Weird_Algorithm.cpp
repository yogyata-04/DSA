#include<bits/stdc++.h>
using namespace std;

// This is Collatz conjecture (3n+1 problem)
//The Collatz sequence is known for how unpredictable it is — even very large numbers will quickly fall down to 1, but there's no formal proof that all numbers do

int main(){
    int n;
    cin>>n;
    while(n!=1){
        cout<<n<<" ";
        if(n%2==0) n/=2;
        else{
            n=(n*3)+1;
        }
    }
    cout<<n<<endl;
}
