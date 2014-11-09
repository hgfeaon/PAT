#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

void print(vector<int> &v) {
    int len = v.size();
    for (int i=0; i<len; i++) {
        printf(" %d", v[i]);
    }
    printf("\n");
}

int main() {
    int NC, NP;
    scanf("%d", &NC);
    vector<int> C(NC);

    for (int i=0; i<NC; i++) {
        scanf("%d", &C[i]);
    }
    
    scanf("%d", &NP);
    vector<int> P(NP);
    for (int i=0; i<NP; i++) {
        scanf("%d", &P[i]);
    }
    
    sort(C.begin(), C.end(), greater<int>());
    sort(P.begin(), P.end(), greater<int>());
    
    int clen = C.size();
    int plen = P.size();
    
    int ci = 0;
    int pi = 0;
    int dc, dp;
    long long sum = 0;

    while (ci < clen && pi < plen && (dc=C[ci]) > 0 && (dp=P[pi]) > 0) {
        sum += dc * dp;
        ci++, pi++;
    }
    
    ci = clen - 1;
    pi = plen - 1;
    
    while (ci >= 0 && pi >= 0 && (dc=C[ci]) < 0 && (dp=P[pi]) < 0) {
        sum += dc * dp;
        ci--, pi--;
    }
    printf("%lld", sum);
	return 0;
}

