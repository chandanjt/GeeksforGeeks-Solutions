#include <iostream>
#include <bits/stdc++.h>
using namespace std;

static bool fun(pair<int,int> p1,pair<int,int> p2){
    if(p1.second>p2.second) return true;
    if(p1.second==p2.second&&p1.first<p2.first) return true;
    return false;
}
vector<int> sortByFrequency(int arr[],int n){
    vector<int> ans;
    map<int,int> mpp;
    for(int i=0;i<n;i++){
        mpp[arr[i]]++;
    }
    vector<pair<int,int>> v;
    for(auto it:mpp){
        v.push_back({it.first,it.second});
    }
    sort(v.begin(),v.end(),fun);
    for(auto it:v){
        for(int i=0;i<it.second;i++){
            ans.push_back(it.first);
        }
    }
    return ans;
}
int main() {
    int t;
    cin>>t;
    while(t>0){
        int N;
        cin>>N;
        int arr[N];
        for(int i=0;i<N;i++){
            cin>>arr[i];
        }
        vector<int> v=sortByFrequency(arr,N);
        for(auto it:v){
            cout<<it<<" ";
        }
        cout<<endl;
        t--;
    }
    return 0;
}