#include <cstdio>
#include <cstdlib>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;


int main() {
	int N, M;
	scanf("%d%d", &N, &M);
	vector<int> nums(N);
	
	vector<pair<int, int> > cuts;
	
	for (int i=0; i<N; i++) {
		scanf("%d", &nums[i]);
	}
	int p = 0;
	int q = 0;
	
	int csum = nums[0];
	int lsum = INT_MAX;

	while (p<=q && q < N) {
		if (csum < M) {
			if (q+1 >= N) {
				break;
			}
			csum += nums[++q];
		} else if (csum == M) {
			if (lsum > csum) {
				cuts.clear();
			}
			lsum = csum;
			cuts.push_back(make_pair(p, q));
			if (q+1 >= N) {
				break;
			}
			csum -= nums[p++];
			csum += nums[++q];
		} else {
			if (csum < lsum) {
				cuts.clear();
				lsum = csum;
				cuts.push_back(make_pair(p, q));
			} else if (csum == lsum) {
				cuts.push_back(make_pair(p, q));
			}
			if (p == q && (q + 1 < N)) {
				csum += nums[++q];
			}
			csum -= nums[p++];
		}
	}
	sort(cuts.begin(), cuts.end());
	int len = cuts.size();
	
	for (int i=0; i<len; i++) {
		printf("%d-%d\n", cuts[i].first + 1, cuts[i].second + 1);
	}
	return 0;
}

