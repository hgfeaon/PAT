#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>* > paths;

class Node {
public:
	vector<int> child;
	int weight;
	Node(int w = 0) : weight(w){}
};

int str2num(const char* str) {
	if (str == NULL) return 0;
	int v = 0;
	int i = 0;
	char ch;
	while ((ch = str[i++]) != '\0') {
		v = v * 10 + (ch - '0');
	}
	return v;
}

void print_nodes(vector<Node> &nodes) {
	for (int i=0; i<nodes.size(); i++) {
		printf("id:%d nchild:%d\n", i, nodes[i].child.size());
		for (int j=0; j<nodes[i].child.size(); j++) {
			printf(" %d", nodes[i].child[j]);
		}
		printf("\n");
	}
}

void dfs(vector<Node> &nodes, vector<int> &path, int idx, int sum, int target) {
	if (idx >= nodes.size()) return; // invalid case;
	int path_weight = sum + nodes[idx].weight;
	if (path_weight == target) {
		// not a leaf node, ignore it
		if (!nodes[idx].child.empty()) {
			return;
		}
		// leaf node, so we got a Root->Leaf path weight equal to the target weight
		path.push_back(nodes[idx].weight);
		// record it
		paths.push_back(new vector<int>(path));
		path.pop_back();
		return;
	} else if (path_weight > target) {
		// impossible continue to find a valid path
		return;
	}

	int clen = nodes[idx].child.size();
	for (int i=0; i<clen; i++) {
		path.push_back(nodes[idx].weight);
		dfs(nodes, path, nodes[idx].child[i], path_weight, target);
		path.pop_back();
	}

}
class cmpcls {
private:
    vector<Node>* nodes;
public:
    cmpcls(vector<Node>* ns) : nodes(ns) {}
    bool operator()(int a, int b) {
        if ((*nodes)[a].weight > (*nodes)[b].weight) {
            return true;
        } else {
            return false;
        }
    }
};

bool mycmp(const vector<int>* a, const vector<int>* b) {
	int len = 0;
	if (a->size() > b->size()) {
		len = b->size();
	} else {
		len = a->size();
	}
	for (int i=0; i<len; i++) {
		if ((*a)[i] > (*b)[i]) return true;
	}
	return false;
}

void print_path() {
	int len = paths.size();
	for (int i=0; i<len; i++) {
		int plen = paths[i]->size();
		printf("%d", (*paths[i])[0]);
		for (int j=1; j<plen; j++) {
			printf(" %d", (*paths[i])[j]);
		}
		printf("\n");
	}
}
int main() {
	int N, M, S;

	scanf("%d%d%d", &N, &M, &S);
	vector<Node> nodes(N);

	char buf[4];

	for (int i=0; i<N; i++) {
		int w = 0;
		scanf("%d", &w);
		nodes[i].weight = w;
	}
    cmpcls cmpobj(&nodes);
    
	for (int i=0; i<M; i++) {
		int nchild = 0;
		scanf("%s%d", buf, &nchild);
		Node& node = nodes[str2num(buf)];
		for (int j=0; j<nchild; j++) {
			scanf("%s", buf);
			node.child.push_back(str2num(buf));
		}
        sort(node.child.begin(), node.child.end(), cmpobj);
	}
	vector<int> path;
	dfs(nodes, path, 0, 0, S);
	print_path();
	return 0;
}
