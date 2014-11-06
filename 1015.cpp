#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

void init_primes(vector<char>& primes) {
    int len = primes.size();
    for (int i=0; i<len && i<2; i++) primes[i] = false;
    if (len < 3) return;
    primes[2] = true;
    
    for (int i=2; i<len; i++) {
        if (!primes[i]) continue;
        int v = i * 2;
        while (v < len) {
            primes[v] = false;
            v += i;
        }
    }
    
}

int inv_value(int n, int radix) {
    int base = 1;
    int v = 0;
    int r = 0;
    vector<int> rs;
    while (n) {
        r = n % radix;
        n = n / radix;
        rs.push_back(r);
    }
    for (int i=rs.size() - 1; i>=0; i--) {
        v += rs[i] * base;
        base *= radix;
    }
    return v;
}

int main() {
    const int MAX_N = 100000;
    vector<char> primes(MAX_N + 1, true);
    init_primes(primes);
    
    int num, radix;

    for (;;) {
        scanf("%d", &num);
        if (num < 0) break;
        scanf("%d", &radix);
        
        if (!primes[num]) {
            printf("No\n");
            continue;
        }
        int iv = inv_value(num, radix);
        if (!primes[iv]) {
            printf("No\n");
        } else {
            printf("Yes\n");
        }
    }
    
	return 0;
}

