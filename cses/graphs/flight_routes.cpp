#include<bits/stdc++.h>
using namespace std;

//applying dijkstra for k minimum using distance array with priority queue element
//getting TLE in one testcase
int main() {
	int n,m,k;
	cin>>n>>m>>k;
	vector<vector<pair<int,long long>>> adj(n+1);
	int a,b;
	long long c;
	for(int i=0; i<m; i++) {
		cin>>a>>b>>c;
		adj[a].push_back({b,c});
	}
	//can use priority queue so that instead of exploring all paths we can just explore first k shortest paths till that node
	priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;
	pq.push({0,1});
	int l=0;
	vector<priority_queue<long long>> dis(n+1, priority_queue<long long>()); //maintain priority queue so that we can remove maximum element from top when size==k

	while(!pq.empty()) {
		auto front=pq.top();
		pq.pop();
		int node=front.second;
		long long cost=front.first;
		for(auto it:adj[node]) {
			//pushing every node is not a good option we will store k smallest ones
			if(dis[it.first].size()==k) {
				long long top=dis[it.first].top();
				if(top>it.second+cost) {
					dis[it.first].pop();
					dis[it.first].push(it.second+cost);
					pq.push({it.second+cost,it.first});
				}
			}
			else {
				dis[it.first].push(it.second+cost);
				pq.push({it.second+cost,it.first});
			}

		}
	}
	vector<long long> ans;
	while(!dis[n].empty()) {
		ans.push_back(dis[n].top());
		dis[n].pop();
	}
	reverse(ans.begin(),ans.end());
	for(auto it:ans) {
		cout<<it<<" ";
	}
}
