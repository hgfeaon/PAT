#include <cstdio>
#include <cstdlib>
#include <stack>
#include <map>

using namespace std;
class StackItem {
public:
	int value;
	int median;
	StackItem(int v, int m): value(v), median(m){};
};

class MStask {
private:
	map<int, int> dc;
	stack<StackItem> sk;
	int size;
public:
	MStask() {
		size = 0;
	}
	void push(int value) {
		// if stack is empty, samplest case
		if (size == 0) {
			sk.push(StackItem(value, value));
			dc.insert(make_pair(value, 1));
			size++;
			return;
		}

		// stack not empty, normal case
		int last_median = sk.top().median;
		auto iter = dc.find(last_median);
		if (iter == dc.end()) {
			printf("invalid state[0]\n");
			return;
		}
		// easy case, median must the inserted value
		bool odd = size & 1;
		if (last_median == value) {
			sk.push(StackItem(value, value));
			++(iter->second);
		} else if (value < last_median) {
			dc.insert(make_pair(value, 1));
			if (odd) {
				if (iter->second == 1) {
					--iter;
				}
				sk.push(StackItem(value, iter->first));
			} else {
				sk.push(StackItem(value, last_median));
			}
		} else {
			if (odd) {
				sk.push(StackItem(value, last_median));
			} else {
				if (iter->second == 1) {
					++iter;
				}
				sk.push(StackItem(value, iter->first));
			}
		}
		size++;
	}
	
	int getSize() {
		return size;
	}
	
	int pop() {
		if (size == 0) {
			return -1;
		}
		StackItem item = sk.top();
		sk.pop();
		int value = item.value;
		auto iter = dc.find(value);
		if (iter == dc.end()) {
			printf("invalid state[1]\n");
			return -1;
		}
		if (iter->second > 1) {
			--(iter->second);
		} else {
			dc.erase(iter);
		}
		return value;
	}
	
	int peekMedian() {
		return sk.top().median;
	}
};

int main() {
	int N;
	scanf("%d", &N);
	char action[16];
	int value;
	
	MStask sk;
	for (int i=0; i<N; i++) {
		scanf("%s", action);
		if (action[0] == 'P' && action[1] == 'o') {
			// pop action
			if (sk.getSize() == 0) {
				printf("Invalid\n");
			} else {
				printf("%d\n", sk.pop());
			}
			continue;
		}
		
		if (action[0] == 'P' && action[1] == 'e'){
			// peekmedian action
			if (sk.getSize() == 0) {
				printf("Invalid\n");
			} else {
				printf("%d\n", sk.peekMedian());
			}
			continue;
		}
		
		// must be an push action here, so read value
		scanf("%d", &value);
		sk.push(value);
	}
	return 0;
}

