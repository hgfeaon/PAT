#include <cstdio>
#include <cstdlib>

class Node {
public:
    Node* L;
    Node* R;
    int height;
    int data;
    Node(int val, Node* l = NULL, Node* r = NULL, int h = 0): data(val), L(l), R(r), height(h) {}
};

inline int height(Node* node) {
    if (node == NULL) return -1;
    return node->height;
}

inline int max(int a, int b) {return a>b?a:b;}
/* K2 is the first node violates the AVL property, K1 is its left node
   violation is caused by insert a node into the K1's right sub-tree
                (K2)                      (K1)
                /      LL-rotate          /  \
            (K1)     -------------->   (new) (K2)
            /
        (new)
 */
Node* rotateLL(Node* root) {
    Node* K1 = root->L;
    Node* K2 = root;
    
    Node* k1_rsub = K1->R;
    K1->R = K2;
    K2->L = k1_rsub;
    
    K1->height = max(height(K1->L), height(K1->R)) + 1;
    K2->height = max(height(K2->L), height(K2->R)) + 1;
    return K1;
}

/* K1 is the first node violates the AVL property, K2 is its right node
   violation is caused by insert a node into the K2's left sub-tree
   (K1)                                  (K2)
      \             RR-rotate            /  \
      (K2)       ---------------->     (K1) (new)
        \
        (new)
*/
Node* rotateRR(Node* root) {
    Node* K1 = root;
    Node* K2 = root->R;
    Node* k2_lsub = K2->L;
    K2->L = K1;
    K1->R = k2_lsub;
    
    K1->height = max(height(K1->L), height(K1->R)) + 1;
    K2->height = max(height(K2->L), height(K2->R)) + 1;
    
    return K2;
}

/*
    first do LL rotate on K3, then do RR rotate on K1
    (K1)          (K1)                   (K2)
      \              \                   /  \
      (K3) ------>   (K2)   -------->  (K1) (K3)
      /                \
    (K2)               (K3)
*/
Node* rotateRL(Node* root) {
    Node* K1 = root;
    Node* K2 = root->R->L;
    Node* K3 = root->R;
    
    K1->R = rotateLL(K3);
    return rotateRR(K1);
}


/*
    first do RR rotate on K1, then do LL rotate on K3
     (K3)              (K3)           (K2)
      /                /              /  \
    (K1)   ------>   (K2)  ------>  (K1) (K3)
      \              /
      (K2)         (K1)
*/
Node* rotateLR(Node* root) {
    Node* K1 = root->L;
    Node* K2 = root->L->R;
    Node* K3 = root;
    
    K3->L = rotateRR(K1);
    return rotateLL(K3);
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        return new Node(value);
    }
    if (value < root->data) {
        root->L = insert(root->L, value);
        // do AVL property check
        if (height(root->L) - height(root->R) == 2) {
            if (value < root->L->data) {
                // LL case, single rotation
                root = rotateLL(root);
            } else if (value > root->L->data) {
                // LR case, double rotation
                root = rotateLR(root);
            }
        }
    } else if (value > root->data ){
        root->R = insert(root->R, value);
        // do AVL property check
        if (height(root->R) - height(root->L) == 2) {
            if (value > root->R->data) {
                // RR case, single rotation
                root = rotateRR(root);
            } else if (value < root->R->data) {
                // RL case, double rotation
                root = rotateRL(root);
            }
        }
    } else {
        // equal, do nothing
    }

    root->height= max(height(root->L), height(root->R)) + 1;
    return root;
}

int main() {
    Node* r = NULL;

    int N;
    scanf("%d", &N);
    for (int i=0; i<N; i++) {
        int d;
        scanf("%d", &d);
        r = insert(r, d);
    }
    if (r != NULL) {
        printf("%d", r->data);
    }
	return 0;
}

