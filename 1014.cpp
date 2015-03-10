#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class Man {
public:
    int need;
    int time;
    int finish;
    Man(int t = 0) : time(t), finish(0), need(t) {}

};

int move_customers(list<int>& wait, vector<list<int> >& win, int win_max) {
    if (wait.size() == 0 || win_max <= 0 || win.size() <=0) {
        return 0;
    }
    int win_num = win.size();
    int moved = 0;
    int min_index = 0;
    for (int i=0; i<win_num; i++) {
        if (win[i].size() < win[min_index].size()) {
            min_index = i;
        }
    }
    if (win[min_index].size() == win_max) {
        // all windows are full
        return 0;
    }
    int customer = wait.front();
    wait.pop_front();
    win[min_index].push_back(customer);
    moved++;
    return moved;
}

int time_step(vector<Man>& customers, vector<list<int> >& win, int time_elasped) {
    int win_num = win.size();
    int min_time_step = INT_MAX;
    bool has_wait = false;
    // get the mininum time step
    for (int i=0; i<win_num; i++) {
        if (win[i].size() == 0) {
            continue;
        }
        has_wait = true;
        int cur = customers[win[i].front()].time;
        if (cur < min_time_step) {
            min_time_step = cur;
        }
    }
    
    time_elasped += has_wait ? min_time_step : 0;
    // time walk
    for (int i=0; i<win_num; i++) {
        list<int>& cur = win[i];
        if (cur.size() == 0) {
            // win empty
            continue;
        }
        Man& man = customers[cur.front()];
        man.time  -= min_time_step;
        if (man.time == 0) {
            // this customer has been done
            man.finish = time_elasped;
            cur.pop_front();
        }
    }
    
    return time_elasped;
}


void print(int finish, int need) {
    int start = finish - need;
    int maxtime = (17 - 8) * 60;
    if (start >= maxtime) {
        printf("Sorry\n");
        return;
    }
    int hour = 8 + finish / 60;
    int min  = finish % 60;
    printf("%02d:%02d\n", hour, min);
}

int main() {

    int N, M, K, Q;
    scanf("%d%d%d%d", &N, &M, &K, &Q);
    
    vector<list<int> > win(N);
    
    list<int> wait_queue;
    vector<Man> customers;
    
    for (int i=0; i<K; i++) {
        int time;
        scanf("%d", &time);
        customers.push_back(Man(time));
        
        wait_queue.push_back(i);
    }

    int time_elasped = 0;
    int last_time = -1;
    while (last_time != time_elasped) {
        while (move_customers(wait_queue, win, M) != 0);
        last_time = time_elasped;
        time_elasped = time_step(customers, win, last_time);
    }

    for (int i=0; i<Q; i++) {
        int qi;
        scanf("%d", &qi);
        Man& man = customers[--qi];
        print(man.finish, man.need);
    }
    

	system("pause");
	return 0;
}

