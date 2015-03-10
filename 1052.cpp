#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

class Node {
public:
    int data;
    int next;
    Node() : data(0), next(-1){
        cout<<"should not happend"<<endl;
    }
    Node(int d, int n) : data(d), next(n) {}
};

int count(int head, unordered_map<int, Node>& mem) {
    int cur = head;
    int cnt = 0;
    while (cur != -1) {
        cnt++;
        cur = mem[cur].next;
    }
    return cnt;

}

int step(int head, int k, unordered_map<int, Node>& mem) {
    int cur = head;
    while (cur != -1) {
        if (k-- == 0) {
            break;

        }
        cur = mem[cur].next;
    }
    return cur;
}

int merge_list(int heada, int headb, unordered_map<int, Node>& mem) {
    int nhead = -1;
    int last = -1;
    int select = -1;
    int ca = heada, cb = headb;
    while (ca != -1 && cb != -1) {
        Node& na = mem[ca];
        Node& nb = mem[cb];

        if (na.data > nb.data) {
            select = cb;
            cb = nb.next;
        } else if (na.data <= nb.data) {
            select = ca;
            ca = na.next;
        }

        if (last == -1) {
            nhead = select;
        } else {
            mem[last].next = select;
        }
        last = select;
    }

    int last_part = -1;
    
    if (ca != -1) {
        last_part = ca;
    }
    
    if (cb != -1) {
        last_part = cb;
    }

    if (last == -1) {
        nhead = last_part;
    } else {
        mem[last].next = last_part;
    }

    return nhead;
}

int sort_list(int head, int n, unordered_map<int, Node>& mem) {

    if (n < 1) {
        return -1;
    }

    if (n == 1) {
        mem[head].next = -1;
        return head;
    }

    int a_cnt = n / 2;
    int b_cnt = n - a_cnt;

    int ca = head;
    int cb = step(head, a_cnt, mem);
    
    ca = sort_list(ca, a_cnt, mem);
    cb = sort_list(cb, b_cnt, mem);

    return merge_list(ca, cb, mem);

}

void print_list(int head, unordered_map<int, Node>& mem) {
    int cur = head;
    while (cur != -1) {
        Node& cn = mem[cur];
        if (cn.next == -1) {
            printf("%05d %d %d\n", cur, cn.data, cn.next);
        } else {
            printf("%05d %d %05d\n", cur, cn.data, cn.next);
        }
        cur = mem[cur].next;
    }
}

int main() {

    int N, head;

    scanf("%d%d", &N, &head);

    unordered_map<int, Node> mem;

    for (int i=0; i<N; i++) {
        int addr, data, next;
        scanf("%d%d%d", &addr, &data, &next);
        mem.insert(make_pair(addr, Node(data, next)));
    }

    int n = count(head, mem);

    head = sort_list(head, n, mem);
    if (n > 0) {
        printf("%d %05d\n", n, head);
    } else {
        printf("%d %d\n", n, head);
    }
    print_list(head, mem);

    return 0;

}
