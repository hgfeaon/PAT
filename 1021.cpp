#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>

using namespace std;

class Node {
public:
    vector<int> adj;
    bool visited;
    Node() : visited(false) {}
};

void reset_nodes(vector<Node>& nodes) {
    int len = nodes.size();
    for (int i=0; i<len; i++) {
        nodes[i].visited = false;
    }
}

void dfs(int idx, vector<Node>& nodes, int level, int& deepest, set<int>& leaf) {
    if (nodes[idx].visited) return;
    Node& node = nodes[idx];
    node.visited = true;
    if (level > deepest) {
        deepest = level;
        leaf.clear();
        leaf.insert(idx);
    } else if (level == deepest) {
        leaf.insert(idx);
    }
    
    int len = node.adj.size();
    for (int i=0; i<len; i++) {
        dfs(node.adj[i], nodes, level + 1, deepest, leaf);
    }
}

int find_deepest_from(int idx, vector<Node>& nodes, set<int>& leaf) {
    int deepest = 0;
    // reset visited flag of all the nodes
    reset_nodes(nodes);
    
    // find the max level from this node(as root)
    dfs(idx, nodes, 0, deepest, leaf);

    int parts = 1;
    // check if other parts exist
    set<int> dummy_leaf;
    int dummy_deepest = 0;
    for (int i = nodes.size() - 1; i>=1; i--) {
        if (!nodes[i].visited) {
            dummy_leaf.clear();
            dummy_deepest = 100000;
            dfs(i, nodes, 0, dummy_deepest, dummy_leaf);
            parts++;
        }
    }
    if (parts > 1) return -parts;
    
    reset_nodes(nodes);
    vector<int> root(leaf.begin(), leaf.end());
    int len = root.size();
    
    for (int i=0; i<len; i++) {
        dfs(root[i], nodes, 0, deepest, leaf);
        leaf.insert(root[i]);
    }
    
    return parts > 1 ? -parts : deepest;
}

int main() {
    int N = 0;
    scanf("%d", &N);

    vector<Node> nodes(N + 1);
    
    for (int i=1; i<N; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        nodes[a].adj.push_back(b);
        nodes[b].adj.push_back(a);
    }
    
    int res = 0;
    set<int> deepnodes;
    int deepest = 0;
    res = find_deepest_from(1, nodes, deepnodes);
    // not connected graph
    if (res < 0) {
        printf("Error: %d components\n", -res);
    } else {
        auto iter = deepnodes.begin();
        while (iter != deepnodes.end()) {
            printf("%d\n", *iter++);
        }
    }
	return 0;
}

