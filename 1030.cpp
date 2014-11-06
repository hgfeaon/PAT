#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>

#define CMB(ID1, ID2) (((ID1)<<9) | (ID2))

using namespace std;

class City {
public:
    vector<int> adj;
    int dist;
    City(int d = INT_MAX): dist(d){}
};

typedef pair<int, int> P;

// sparse table
unordered_map<int, int> dist;
unordered_map<int, int> cost;

void print_cities(vector<City> &cities) {
    int len = cities.size();
    
    for (int i=0; i<len; i++) {
        printf("%d\n", i);
        int adj_len = cities[i].adj.size();
        for (int j=0; j<adj_len; j++) {
            int cid = CMB(i, cities[i].adj[j]);
            printf("\t%d %d %d", cities[i].adj[j], dist[cid], cost[cid]);
        }
        printf("\n");
    }
}

void dfs(vector<int> &final, vector<int>& path, int path_cost, int &final_cost, vector<City>& cities, int idx) {
        if (cities[idx].dist == 0) {
            // we reach the start point
            if (path_cost < final_cost) {
                final_cost = path_cost;
                final = path;
                final.push_back(idx);
            }
            return;
        }
        City& cur_city = cities[idx];
        int adj_len = cur_city.adj.size();
        
        for (int i=0; i<adj_len; i++) {
            int adj_idx = cur_city.adj[i];
            int pdist = cities[adj_idx].dist + dist[CMB(idx, adj_idx)];
            if (pdist == cur_city.dist) {
                // adj city on the shortest path
                path.push_back(idx);
                path_cost += cost[CMB(idx, adj_idx)];
                // follow it
                dfs(final, path, path_cost, final_cost, cities, adj_idx);
                
                path_cost -= cost[CMB(idx, adj_idx)];
                path.pop_back();
            }
        }
}

int main() {
    int N, M, S, D;
    scanf("%d%d%d%d", &N, &M, &S, &D);

    vector<City> cities(N);

    int c1, c2, d, c;
    
    for (int i=0; i<M; i++) {
        scanf("%d%d%d%d", &c1, &c2, &d, &c);
        dist.insert(make_pair(CMB(c1, c2), d));
        dist.insert(make_pair(CMB(c2, c1), d));
        cost.insert(make_pair(CMB(c1, c2), c));
        cost.insert(make_pair(CMB(c2, c1), c));
        cities[c1].adj.push_back(c2);
        cities[c2].adj.push_back(c1);
    }
    
    cities[S].dist = 0;
    
    //print_cities(cities);
    
    priority_queue<P, vector<P>, greater<P> > nodes;
    
    nodes.push(make_pair(0, S));
    
    bool updated = true;
    while (updated) {
        updated = false;
        P node = nodes.top();
        nodes.pop();
        int cur_idx = node.second;
        int cur_dst = node.first;
        if (cur_dst > cities[cur_idx].dist) {
            // there is another shorter path to the current selected city
            // so the node info is out of date, just drop it
            updated = true;
            continue;
        }
        
        City& cur_city = cities[cur_idx];
        int alen = cur_city.adj.size();
        
        // traverse adj cities of the current city
        for (int i=0; i<alen; i++) {
            int adj_idx = cur_city.adj[i];
            City& adj_city = cities[adj_idx];
            
            int new_dist = cur_city.dist + dist[CMB(cur_idx, adj_idx)];
            if (new_dist < adj_city.dist) {
                adj_city.dist = new_dist;
                nodes.push(make_pair(new_dist, adj_idx));
                updated = true;
            }
        }
    }
    
    vector<int> final, path;
    int path_cost = 0, final_cost = INT_MAX;
    dfs(final, path, path_cost, final_cost, cities, D);
    
    int flen = final.size();
    if (flen < 1) {
        return 0;
    }
    reverse(final.begin(), final.end());
    
    printf("%d", final[0]);
    for (int i=1; i<flen; i++) {
        printf(" %d", final[i]);
    }
    printf(" %d %d", cities[D].dist, final_cost);
	return 0;
}

