//Salesforce coding round-Here we are given an array with n elements and we have to divide it into m parts so that maximum sum of a section is minimum
//learning-whenever confused to find a desired number from some range apply binary search for optimized solution
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,m;
    cin>>n>>m;
    vector<int> vec;
    int x;
    int mini=INT_MAX,maxi=0;
    int sum=0;
    for(int i=0;i<n;i++){
        cin>>x;
        vec.push_back(x);
        mini=min(mini,vec[i]);
        maxi=max(maxi,vec[i]);
        sum+=vec[i];
    }
    if(m>=n)
    {
        cout<<maxi<<endl;
        return 0;
    }
    int low=mini;
    int high=sum;
    int mid,count,ans=INT_MAX,temp_ans;
    while(low<high){
        int temp_sum;
        temp_ans=0;
        mid=low+(high-low)/2;
        count=0;
        for(int i=0;i<n;i++){
            temp_sum=0;
            while(temp_sum+vec[i]<=mid && i<n){
                temp_sum+=vec[i];
                i++;
            }
            i=i-1;
            count++;
            if(count>m)
                break;
            temp_ans=max(temp_ans,temp_sum);
        }
        if(count>m)
        {
            low=mid+1;
        }
        else if(count<=m){
            high=mid-1;
            ans=min(ans,temp_ans);
        }
    }
    cout<<ans<<endl;
    
}
