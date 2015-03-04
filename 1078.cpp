#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

bool is_prime(unsigned int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    for (int i=2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void print(int M, int i, int num) {
    if (i != 0) {
        printf(" ");
    }
    if (num < 0) {
        printf("-");
    } else {
        printf("%d", num);
    }
    
    if (i == M - 1) {
        printf("\n");
    }
}

int main() {

    unsigned int M, N;
    cin>>M>>N;

    if (!is_prime(M)) {
        while (!is_prime(++M));
    }

    bool* hashtable = new bool[M];
    for (int i=0; i<M; i++) {
        hashtable[0] = false;
    }
    
    for (int i=0; i<N; i++) {
        int num;
        cin>>num;
        int addr = num % M;
        unsigned int taddr;
        bool found = false;
        for (unsigned int j = 0; j<M; j++) {
            taddr = (addr + j * j) % M;
            if (!hashtable[taddr]) {
                hashtable[taddr] = true;
                found = true;
                break;
            }
        }
        if (found) {
            print(M, i, taddr);
        } else {
            print(M, i, -1);
        }
    }

	system("pause");
	return 0;
}

