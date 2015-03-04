#include <cstdio>
#include <climits>
#include <cstdlib>
#include <vector>

const double LO_BOUND = -1.0 + INT_MIN;
const double HI_BOUND = +1.0 + INT_MAX;

using namespace std;

class Node {
public:
	Node* L;
	Node* R;
	int data;
	Node(int d=0, Node* l = NULL, Node* r = NULL) : L(l), R(r), data(d){}
};


Node* build_bst(vector<Node> &nums, int start, int end, bool mirror = false) {
	if (start >= end) return NULL;
	if (start + 1 == end) {
		nums[start].R = nums[start].L = NULL;
		return &nums[start];
	}
	Node& root = nums[start];
	int i = start + 1;
	while (i<end) {
		if (!mirror) {
			if (nums[i].data >= root.data) break;
		} else {
			if (nums[i].data < root.data) break;
		}
		i++;
	}
//	printf("Root: %d\n", start);
//	printf("L: %d-%d\n", start + 1, i);
//	printf("R: %d-%d\n", i, end);
	
	root.L = build_bst(nums, start + 1, i, mirror);
	root.R = build_bst(nums, i, end, mirror);
	
	return &root;
}

bool is_bst(Node* root, bool mirror = false, double lo = LO_BOUND, double hi = HI_BOUND) {
	if (root == NULL) return true;
//	printf("check %d lo=%f hi=%f mirror=%d\n", root->data, lo, hi, mirror);
	if (root->data < lo || root->data >= hi) {
//		printf("fail\n");
		return false;
	}
	Node *vL = root->L, *vR = root->R, *tmp = NULL;
	if (mirror) {
		tmp = vL;
		vL = vR;
		vR = tmp;
	}
	return is_bst(vL, mirror, lo, root->data) && is_bst(vR, mirror, root->data, hi);
}

void postorder(Node* root, vector<int> &v) {
	if (root == NULL) return;
	postorder(root->L, v);
	postorder(root->R, v);
	v.push_back(root->data);
	return;
}

void print(vector<int> &v) {
	int len = v.size();
	
	if (len < 1) return;
	printf("%d", v[0]);
	for (int i=1; i<len; i++) {
		printf(" %d", v[i]);
	}
	printf("\n");
}
int main() {
	int N;
	scanf("%d", &N);
	vector<Node> nums(N);
	
	for (int i=0; i<N; i++) {
		scanf("%d", &(nums[i].data));
	}
	vector<int> post;
	
	Node* root = build_bst(nums, 0, nums.size());
	if (is_bst(root)) {
		printf("YES\n");
		postorder(root, post);
		print(post);
		return 0;
	}

	root = build_bst(nums, 0, nums.size(), true);
	if (is_bst(root, true)) {
		printf("YES\n");
		postorder(root, post);
		print(post);
		return 0;
	} else {
		printf("NO\n");
	}
	return 0;
}

