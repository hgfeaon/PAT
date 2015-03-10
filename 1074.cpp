#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unordered_map>

using namespace std;

class Node {
public:
    int data;
    int next;
    Node() : data(0), next(0) {}
    Node(int d, int n):data(d), next(n){}
};

int reverse_help(int head, int k, unordered_map<int, Node>& mem) {
    if (head == -1) {
        return -1;
    }

    int cur = head;
    int prev= -1;
    while (cur != -1) {
        if (k == 0) {
             break;
        }
        int tmp = mem[cur].next;
        mem[cur].next = prev;
        prev = cur;
        cur = tmp;

        k--;
    }
    mem[head].next = cur;
    return prev;
}

int reverse(int head, int k, unordered_map<int, Node>& mem, int n) {
    if (head == -1) {
        return -1;
    }

    int nhead = -1;
    int cur = head;
    int pre = -1;

    while (cur != -1) {
        int t = reverse_help(cur, k, mem);
        if (nhead == -1) {
            nhead = t;
        }
        if (pre != -1) {
            mem[pre].next = t;
        }
        pre = cur;
        cur = mem[cur].next;
        n -= k;
        if (n < k) {
            break;
        }
    }

    return nhead;
}

void print(int head, unordered_map<int, Node>& mem) {
    int cur = head;
    while(cur != -1) {
        Node& cnode = mem[cur];
        if (cnode.next != -1) {
            printf("%05d %d %05d\n", cur, cnode.data, cnode.next);
        } else {
            printf("%05d %d %d\n", cur, cnode.data, cnode.next);
        }
        cur = mem[cur].next;
    }
}

int count(int head, unordered_map<int, Node>& mem) {
    int cnt = 0;
    int cur = head;
    while(cur != -1) {
        cnt++;
        cur = mem[cur].next;
    }
    return cnt;
}

int main() {

    int head, n, k;
    scanf("%d%d%d", &head, &n, &k);

    unordered_map<int, Node> mem;

    for (int i=0; i<n; i++) {
        int addr, data, next;
        scanf("%d%d%d", &addr, &data, &next);
        mem.insert(make_pair(addr, Node(data, next)));
    }

    cout<<"===="<<endl;
    print(head, mem);
    cout<<"===="<<endl;
    head = reverse(head, k, mem, count(head, mem));
    print(head, mem);

    return 0;
}
