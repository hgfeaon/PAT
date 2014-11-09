#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

class Man {
public:
    char id[10];
    int talent;
    int virtue;
};


bool mycmp(const Man& a, const Man& b) {
    int ta = a.virtue + a.talent;
    int tb = b.virtue + b.talent;
    if (ta > tb) {
        return true;
    } else if (ta < tb) {
        return false;
    }
    // virtue + talent are equal, so compare virtue
    if (a.virtue > b.virtue) {
        return true;
    } else if (a.virtue < b.virtue) {
        return false;
    }
    // virtue is equal, so compare id
    return strcmp(a.id, b.id) < 0;
}

void sort_print(vector<Man> &v) {
    sort(v.begin(), v.end(), mycmp);
    int len = v.size();
    for (int i=0; i<len; i++) {
        printf("%s %d %d\n", v[i].id, v[i].virtue, v[i].talent);
    }
}

int main() {
    int N, L, H;
    scanf("%d%d%d", &N, &L, &H);
    vector<Man> sage;
    vector<Man> noble;
    vector<Man> fool;
    vector<Man> small;

    Man tmp;
    int count = 0;
    for (int i=0; i<N; i++) {
        scanf("%s%d%d", tmp.id, &(tmp.virtue), &(tmp.talent));
        if (tmp.virtue < L || tmp.talent < L) {
            // discard
            continue;
        }
        count++;
        if (tmp.virtue >= H && tmp.talent >= H) {
            sage.push_back(tmp);
        } else if (tmp.virtue >= H) {
            noble.push_back(tmp);
        } else if (tmp.virtue >= tmp.talent) {
            fool.push_back(tmp);
        } else {
            small.push_back(tmp);
        }
    }
    
    printf("%d\n", count);
        
    sort_print(sage);
    sort_print(noble);
    sort_print(fool);
    sort_print(small);

	return 0;
}

