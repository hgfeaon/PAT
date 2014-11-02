#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

class City {
public:
	vector<int> adj;
	bool  visited;
	City() : visited(false) {}
};

void dfs(int idx, vector<City>& cities) {
	if (cities[idx].visited) {
		return;
	}

	City& city = cities[idx];
	city.visited = true;
	
	for (int i=0; i<city.adj.size(); i++) {
		dfs(city.adj[i], cities);
	}
}

void reset_cities(vector<City>& cities) {
	int len = cities.size();
	for (int i=0; i<len; i++) {
		cities[i].visited = false;
	}
}

int main() {
	int N = 0, M = 0, K = 0;
	
	scanf("%d%d%d", &N, &M, &K);
	
	vector<City> cities(N + 1);
	
	for (int i=0; i<M; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		cities[a].adj.push_back(b);	
		cities[b].adj.push_back(a);
	}
	
	for (int i=0; i<K; i++) {
		int parts = 0;
		reset_cities(cities);
		int oc = -1;
		scanf("%d", &oc);
		cities[oc].visited = true;
		for (int i=1; i<=N; i++) {
			if (cities[i].visited) continue;
			parts++;
			dfs(i, cities);
		}
		printf("%d\n", parts - 1);
	}
	return 0;
}

