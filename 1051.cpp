#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

bool push_validate(int &pre_push, int max_push, int cur, vector<int>& stack, int mcap) {
	if (pre_push >= max_push || pre_push >= cur) {
		// there not exist valid push for this pop
		return false;
	}
	if (cur > max_push) {
		// this pop value is out of range
		return false;
	}
	if (stack.size() + cur - pre_push > mcap) {
		// stack capacity not enough
		return false;
	}
	for (int j = pre_push+1; j<=cur; j++) {
		// push the value (if less value not pushed also push them in)
		stack.push_back(j);
	}
	pre_push = cur;
	return true;
}

bool validate(vector<int> &seq, int capacity) {
	int len = seq.size();
	int pre_push = 0;
	int max_push = len;
	
	vector<int> stack;
	int i = 0;
	while (i<len) {
		int cur = seq[i];
		//printf("cur seq: %d\n", cur);
		if (stack.empty() || cur != stack.back()) { // there must be a push before this pop or it's invalid
			if (push_validate(pre_push, max_push, cur, stack, capacity)) {
				continue;
			} else {
				return false;
			}
		}
		// easy case, just pop element from stack & check next in the pop seq
		i++;
		//printf("pop %d\n", stack.back());
		stack.pop_back();
	}
	return true;
}

int main() {
	int M, N, K;
	scanf("%d%d%d", &M, &N, &K);
	vector<int> seq(N);
	for (int i=0; i<K; i++) {
		for (int j=0; j<N; j++) {
			scanf("%d", &seq[j]);
		}
		
		if (validate(seq, M)) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}

