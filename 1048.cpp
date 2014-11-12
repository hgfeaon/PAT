#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N, M;
	scanf("%d%d", &N, &M);
	
	vector<int> coins(N);
	for (int i=0; i<N; i++) {
		scanf("%d", &coins[i]);
	}
	
	sort(coins.begin(), coins.end());
	
	int p = 0, q = N - 1;
	while (p<q) {
		int sum = coins[p] + coins[q];
		if (sum > M) {
			// bigger, so decrease it, move q to the smaller coins
			q--;
		} else if (sum < M) {
			// smaller, so increase it, move p to the bigger coins
			p++;
		} else {
			// we found the coins
			printf("%d %d\n", coins[p], coins[q]);
			break;
		}
	}
	if (p >= q) {
		printf("No Solution\n");
	}
	return 0;
}

