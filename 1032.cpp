#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>

using namespace std;

class Node {
public:
    Node() : data(0), next(0) {}
    char data;
    int next;
};

void print_list(unordered_map<int, Node*>& mem, int head) {
    int cur = head;
    while (cur != -1) {
        cout<<mem[cur]->data<<" ";
        cur = mem[cur]->next;
    }
    cout<<endl;
};

int step_list(unordered_map<int, Node*>& mem, int from, int n) {
    if (n < 0) return -1;
    int cur = from;
    while (cur != -1) {
        if (n == 0) {
            break;
        }
        cur = mem[cur]->next;
        n--;
    }
    return cur;
}

int count_list(unordered_map<int, Node*>& mem, int from) {
    if (from < 0) return 0;
    int cur =  from;
    int cnt = 0;
    while (cur != -1) {
        cur = mem[cur]->next;
        cnt++;
    }
    return cnt;
}

int main() {
    int head_a, head_b;
    int n;
    
    unordered_map<int, Node*> mem;
    
    cin>>head_a>>head_b>>n;
    
    for (int i=0; i<n; i++) {
        int addr;
        Node* np = new Node();
        scanf("%d %c %d", &addr, &(np->data), &(np->next));
        mem.insert(make_pair(addr, np));
    }

    int cnt_a = count_list(mem, head_a);
    int cnt_b = count_list(mem, head_b);
    
    int cnt_diff = cnt_a - cnt_b;
    int head_long  = head_a;
    int head_short = head_b;
    if (cnt_diff < 0) {
        cnt_diff = -cnt_diff;
        head_long = head_b;
        head_short= head_a;
    }
    
    head_long = step_list(mem, head_long, cnt_diff);
    
    while (head_long != head_short) {
        head_long = mem[head_long]->next;
        head_short= mem[head_short]->next;
    }
    if (head_long < 0) {
        printf("-1\n");
    } else {
        printf("%05d\n", head_long);
    }
	system("pause");
	return 0;
}

