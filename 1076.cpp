#include <cstdio>
#include <cstdlib>

#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class User {
public:
    vector<int> fellowers;
    bool visited;
    User(): visited(false){}
};


int query(int idx, vector<User>& users, int L) {
    int level = L;
    unordered_set<int> walked;
    queue<int> level_queue;
    
    walked.insert(idx);
    level_queue.push(idx);
    
    int last_size = level_queue.size();

    while (!level_queue.empty() && level > 0) {
        while(last_size-- > 0) {
            int uid = level_queue.front();
            
            User& user = users[uid];
            level_queue.pop();
            int len = user.fellowers.size();
            for (int i=0; i<len; i++) {
                int u = user.fellowers[i];
                // already visited
                if (walked.count(u)) continue;
                // not visited
                //printf("visit %d\n", u);
                walked.insert(u);
                level_queue.push(u);
            }
        }
        
        last_size = level_queue.size();
        level--;
    }
    
    return walked.size() - 1;
}



int main() {
    int N = 0, L = 0;
    scanf("%d%d", &N, &L);
    
    vector<User> users(N + 1);
    
    for (int i=1; i<=N; i++) {
        int n = 0;
        scanf("%d", &n);
        for (int j=0; j<n; j++) {
            int uidx = 0;
            scanf("%d", &uidx);
            users[uidx].fellowers.push_back(i);
        }
    }

    int K = 0;
    scanf("%d", &K);
    for (int i=0; i<K; i++) {
        int uidx = 0;
        scanf("%d", &uidx);
        int cnt = query(uidx, users, L);
        printf("%d\n", cnt);
    }
	return 0;
}

