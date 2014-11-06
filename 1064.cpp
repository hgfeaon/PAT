#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
public:
    Node(): val(0), left(NULL), right(NULL) {}
    Node(int _val, Node* _left = NULL, Node* _right = NULL): val(_val), left(_left), right(_right) {}
};

vector<Node*> build_next_level(vector<Node*> last_level, int &num) {
    vector<Node*> res;
    if (num < 1) return res;
    
    for (auto iter = last_level.begin(); iter != last_level.end(); iter++) {
        Node* parent = *iter;
        
        Node* lchild = new Node();
        res.push_back(lchild);
        parent->left = lchild;
        if (--num < 1) break;
        
        Node* rchild = new Node();
        res.push_back(rchild);
        parent->right= rchild;
        if (--num < 1) break;
    }
    
    return res;
}

void inorder_traverse(Node* root, int& order) {
    if (root == NULL) return;
    inorder_traverse(root->left, order);
    root->val = order++;
    inorder_traverse(root->right, order);
}

int main() {
    int cnt;

    scanf("%d", &cnt);
    
    vector<int> nums(cnt, 0);
    
    if (cnt < 1) return 0;
    
    for (int i = 0; i<cnt; i++) {
        int num = 0;
        scanf("%d", &num);
        nums[i] = num;
    }
    sort(nums.begin(), nums.end());
    
    vector<vector<Node*> > levels;

    vector<Node*> last_level;
    last_level.push_back(new Node());

    levels.push_back(last_level);
    
    int node_cnt = cnt - 1; // we already pushed the root node
    while (node_cnt > 0) {
        vector<Node*> cur_level = build_next_level(last_level, node_cnt);
        levels.push_back(cur_level);
        swap(last_level, cur_level);
    }

    int order = 0;
    inorder_traverse(levels[0][0], order);
    
    node_cnt = cnt;
    
    for (auto iter_levels = levels.begin(); iter_levels != levels.end(); iter_levels++) {
        vector<Node*>& cur_level = *iter_levels;
        for (auto iter = cur_level.begin(); iter != cur_level.end(); iter++) {
            Node* node = *iter;
            int val = nums[node->val];
            if (--node_cnt > 0) {
                printf("%d ", val);
            } else {
                printf("%d\n", val); // last element
            }
        }
    }
	return 0;
}

