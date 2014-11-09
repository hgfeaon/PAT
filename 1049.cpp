#include <cstdio>
#include <cstdlib>

using namespace std;

#define COL 10
#define ROW 10

int tbl[ROW][COL] = {0};

void print(int *tbl) {
    for (int i=0; i<ROW; i++) {
        for (int j=0; j<COL; j++) {
            printf("%11d", tbl[i * COL + j]);
        }
        printf("\n");
    }
}

int ones_aux(int num, int digits, int tens) {
    if (digits < 1 || tens < 1) return 0;
    int first = num / tens;
    int sum = 0;

    for (int i=0; i<first; i++) {
        sum += tbl[digits-1][i];
    }

    if (first == 1) {
        sum += num % tens + 1;
    }
    int subsum = ones_aux(num % tens, digits - 1, tens / 10);
    return sum + subsum;
}

int ones(int num) {
    int digits = 1;
    int tmp = num;
    int tens = 1;
    
    while (tmp) {
        tmp /= 10;
        if (tmp) {
            tens *= 10;
            digits++;
        }
    }

    return ones_aux(num, digits, tens);
}

int main() {
    int tens = 1;
    int sum = 0;
    for (int i=0; i<ROW; i++) {
        for (int j=0; j<COL; j++) {
            if (j == 0) {
                tbl[i][j] = sum;
                continue;
            }
            if (j == 1) {
                tbl[i][j] = tens * 1;
            }
            tbl[i][j] += tbl[i][0];
            sum += tbl[i][j];
        }
        tens *=10;
    }
    print((int*)tbl);
    int n;
    scanf("%d", &n);
    printf("%d\n", ones(n));
    
	system("pause");
	return 0;
}

