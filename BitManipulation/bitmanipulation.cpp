#include<bits/stdc++.h>
using namespace std;

//******************************************BIT MANIPULATION****************************************

//check if ith bit is set or not
bool issetbit(int i,int num){
    return num>>i & 1;
}

//check is even or not - simply return !(num&1);

//check if number is power of 2
//remember the edge case when num<0 and num==0
bool isPowerOfTwo(int n) {
    if(n==0 || n<0) return false;
    return !(n&(n-1));
}

//Count no. of set bits [1-n]
//You are given a number n. Find the total count of set bits for all numbers from 1 to n (both inclusive).
//need to understand

//unset rightmost set bit
int unsetbit(int n){
    return n&(n-1);
}

//set rightmost unset bit
int setbit(int n){
    return n|n+1;
}

//swap two numbers
pair<int, int> swap(int a, int b){
    a=a^b;
    b=a^b;
    a=a^b;
    return {a,b};
}

//Divide two integers without using multiplication, division and mod operator
//need to understand

int main(){
    int num=12;
    cout<<unsetbit(num);
}
