#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;
const int ROWS = 10002;
const int COLS = 102;

char dp[ROWS][COLS];

bool dfs(vector<int> &coins, vector<int> &path, int idx, int target) {
	if (dp[idx][target] != -1) {
		return dp[idx][target];
	}
	if (idx >= coins.size()) return false;// should not happen
	if (coins[idx] == target) {
		// we found one
		path.push_back(idx);
		return true;
	}
	if (idx == coins.size() - 1) {
		// no more coins to try
		return false;
	}
	path.push_back(idx);
	// try use current idx coin
	if (coins[idx] < target) {
		if (dfs(coins, path, idx + 1, target - coins[idx])) {
			return true;
		}
	}
	path.pop_back();
	// try not use current idx coin
	if (dfs(coins, path, idx + 1, target)) {
		return true;
	}
	dp[idx][target] = false;
	return dp[idx][target];
}

int main() {
	int N, M;
	scanf("%d%d", &N, &M);
	
	vector<int> coins(N);
	
	for (int i=0; i<N; i++) {
		scanf("%d", &coins[i]);
	}
	sort(coins.begin(), coins.end());
	
	for (int i=0; i<ROWS; i++) {
		for (int j=0; j<COLS; j++) {
			dp[i][j] = -1;
		}
	}
	
	// use current st. j-coins>=0
	//dp[i][j] = dp[i-1][j-coins[i]]
	// not use current
	//dp[i][j] = dp[i-1][j];
	vector<int> path;
	bool res = dfs(coins, path, 0, M);
	int len = path.size();
	if (res) {
		if (len > 0) {
			printf("%d", coins[path[0]]);
		}
		for (int i=1; i<len; i++) {
			printf(" %d", coins[path[i]]);
		}
	} else {
		printf("No Solution");
	}
	return 0;
}

