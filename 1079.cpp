#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>

using namespace std;

void print(vector<vector<int> > &man) {
	for (int i=0; i<man.size(); i++) {
		for (int j=0; j<man[i].size(); j++) {
			cout<<man[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

double total = 0.0;

void dfs(vector<vector<int> > &G, int i, double p, double r) {
	if (i >= G.size()) {
		cout<<"out of index bound"<<endl;
		return;
	}
	
	if (G[i][0] < 0) {
		total += p * (-G[i][0]);
		return;
	}
	
	p = p * (1 + r);
	
	for (int j=0; j<G[i].size(); j++) {
		dfs(G, G[i][j], p, r);
	}
}

int main() {
	
	int n;
	double p, r;
	
	cin>>n>>p>>r;
	
	vector<vector<int> > G(n, vector<int>());
	
	for (int i=0; i<n; i++) {
		int m, v;
		cin>>m;
		if (m == 0) {
			cin>>v;
			G[i].push_back(-v);
			continue;
		}
		for (int j=0; j<m; j++) {
			int v;
			cin>>v;
			G[i].push_back(v);
		}
	}
	
	//print(G);
	
	dfs(G, 0, p, r / 100.0);
	
	printf("%.1lf\n", total);
	
	system("pause");	
	return 0;
}
