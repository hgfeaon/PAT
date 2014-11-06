#include <cstdio>
#include <climits>
#include <cstdlib>
#include <vector>
#include <list>

using namespace std;

list<int>::iterator group_pick(list<int> &player, list<int>::iterator &cur, int group_size, vector<int> &W) {
    int wmax = INT_MIN;
    list<int>::iterator ret = player.end();
    int cnt = group_size;
    //printf("check group:\n\t");
    while (cur != player.end() && cnt > 0) {
        --cnt;
        //printf(" %d(%d)", *cur, W[*cur]);
        if (W[*cur] >= wmax) {
            wmax = W[*cur];
            ret = cur;
        }
        cur++;
    }
    //printf("\n");
    return ret;
}

int main() {

    int N = 0, G = 0;
    scanf("%d%d", &N, &G);
    
    if (N < 1) return 0;
    
    vector<int> W(N,  0);
    vector<int> R(N, 0);
    vector<int> L;
    list<int> P;
    
    for (int i=0; i<N; i++) {
        scanf("%d", &W[i]);
    }
    for (int i=0; i<N; i++) {
        int t = 0;
        scanf("%d", &t);
        P.push_back(t);
    }
    
    int level = 0;
    int level_cnt = 0;
    
    list<int> tmp;
    auto cur = P.begin();
    // number of elements in P should be larger than 1 to perform reduce processing
    while (G > 1 && ++(cur = P.begin()) != P.end()) {
        tmp.clear();
        auto cur = P.begin();
        while (cur != P.end()) {
            list<int>::iterator fat = group_pick(P, cur, G, W);
            //printf("pick %d\n", *fat);
            tmp.splice(tmp.end(), tmp, fat);
        }
        
        swap(tmp, P);
        auto iter = tmp.begin();
        while (iter != tmp.end()) {
            R[*(iter++)] = level;
            level_cnt++;
        }
        L.push_back(level_cnt);
        level_cnt = 0;
        level++;
    }
    // now there must be only one element in P, the final winner
    L.push_back(1);
    R[P.front()] = level;
    int sum = 0;
    for (int i=L.size() - 1; i>=0; i--) {
        //printf("level cnt: %d\n", L[i]);
        int next_sum = sum + L[i];
        L[i] = sum + 1;
        sum  = next_sum;
    }

    int len = R.size();
    printf("%d", L[R[0]]);
    for (int i=1; i<len; i++) {
        printf(" %d", L[R[i]]);
    }
	return 0;
}

