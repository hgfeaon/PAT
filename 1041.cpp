#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

const int NUM_RANGE = 10001;
int tbl[NUM_RANGE];

int main() {
	int N;
	scanf("%d", &N);
	vector<int> nums(N);
	
	int i=0;
	for (i=0; i<NUM_RANGE; i++) {
		tbl[i] = false;
	}
	
	for (i=0; i<N; i++) {
		scanf("%d", &(nums[i]));
		tbl[nums[i]]++;
	}
	
	for (i=0; i<N; i++) {
		if (1 == tbl[nums[i]]) {
			printf("%d\n", nums[i]);
			break;
		}
	}
	if (i == N) {
		printf("None\n");
	}
	return 0;
}

