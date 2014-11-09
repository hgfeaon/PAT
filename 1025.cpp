#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

class Man {
public:
    char id[14];
    int location;
    int score;
    int local_rank;
};

class RankCmp{
public:
    bool operator () (const Man* a, const Man* b) {
        if (a->score > b->score) {
            return true;
        } else if (a->score < b->score) {
            return false;
        }

        return strcmp(a->id, b->id) < 0;
    }
};

void do_local_rank(vector<Man*> &v) {
    int len = v.size();
    if (len < 1) return;
    
    int last_score = v[0]->score;
    v[0]->local_rank = 1;
    
    for (int i=1; i<len; i++) {
        Man& cur = *v[i];
        if (cur.score != last_score) {
            cur.local_rank = i + 1;
            last_score = cur.score;
        } else {
            cur.local_rank = v[i - 1]->local_rank;
        }
    }
}

void print(vector<Man*> &v) {
    int len = v.size();
    for (int i=0; i<len; i++) {
        printf("%s %d %d\n", v[i]->id, v[i]->score, v[i]->local_rank);
    }
}

int main() {
    int N, K, total = 0;
    scanf("%d", &N);
    vector<vector<Man*> > locations(N);
    Man tmp;

    RankCmp rankcmp;
    
    for (int i=0; i<N; i++) {
        scanf("%d", &K);
        for (int j=0; j<K; j++) {
            total++;
            scanf("%s%d", tmp.id, &(tmp.score));
            tmp.location = i + 1;
            locations[i].push_back(new Man(tmp));
        }
        sort(locations[i].begin(), locations[i].end(), rankcmp);
        do_local_rank(locations[i]);
    }
    
    printf("%d\n", total);

    vector<Man*> all;
    
    for (int i=0; i<N; i++) {
        all.insert(all.end(), locations[i].begin(), locations[i].end());
    }
    
    sort(all.begin(), all.end(), rankcmp);
    
    int last_rank = 0, last_score = -1;
    for (int i=0; i<total; i++) {
        Man& cur = *all[i];
        if (cur.score != last_score) {
            last_score = cur.score;
            last_rank = i + 1;
        }
        printf("%s %d %d %d\n", cur.id, last_rank, cur.location, cur.local_rank);
    }
	return 0;
}

