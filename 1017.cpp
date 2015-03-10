#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class Man {
public:
    int arrive;
    int need;
    int start;
    Man(int a, int n) : arrive(a), need(n), start(0) {}
};

class ArriveCmp {
public:
    vector<Man>& customers;
    ArriveCmp(vector<Man>& mans) : customers(mans) {}
    bool operator() (int i, int j) {
        return customers[i].arrive < customers[j].arrive;
    }
};

int max(int a, int b) {
    return a>b? a : b;
}

int fetch_customer(list<int>& wait, vector<Man>& customers, int elapsed_time) {
    if (wait.size() <= 0) {
        return -1;
    }
    int c = wait.front();
    customers[c].start = max(elapsed_time, customers[c].arrive);
    wait.pop_front();
    return c;
}

void print_time(int time) {
    int s = time % 60;
    int m = time/60 % 60;
    int h = time / 3600;
    printf("%02d:%02d:%02d\n", h, m, s);
}

int main() {

    int N, W;
    
    scanf("%d%d", &N, &W);
    
    vector<Man> customers;
    vector<int> windows(W, -1);
    list<int> wait;
    ArriveCmp cmp(customers);
    
    int idx = 0;
    for (int i=0; i<N; i++) {
        int h, m, s, need;
        scanf("%d:%d:%d%d", &h, &m, &s, &need);
        if (h >= 17 && (m || s)) {
            // customers arrived too late
            continue;
        }
        need = need * 60; // convert minute to second
        if (need > 3600) {
            // no customer can occupy one window for more than 1hour.
            need = 3600;
        }
        
        customers.push_back(Man(h * 3600 + m * 60 + s, need));
        wait.push_back(idx++);
    }

    wait.sort(cmp);
    
    int elapsed_time = 8 * 3600;
    
    // <finish_time, customer_index>
    priority_queue<pair<int, int> , vector<pair<int, int> >, greater<pair<int, int> > > work;
    
    int next = -1;
    
    while (!wait.empty()) {
        if (!work.empty()) {
            int fast = work.top().second;
            Man& c = customers[fast];
            elapsed_time = c.start + c.need;
            work.pop();
        }
        while (work.size() < W) {
            next = fetch_customer(wait, customers, elapsed_time);
            if (next == -1) {
                break;
            }
            Man& c = customers[next];
            work.push(make_pair(c.start + c.need, next));
        }
    }
    
    int n = customers.size();
    int alltime = 0;
    for (int i=0; i<n; i++) {
        alltime += customers[i].start - customers[i].arrive;
    }
    
    printf("%.1f", alltime * 1.0 / 60 / n );
    
	system("pause");
	return 0;
}

