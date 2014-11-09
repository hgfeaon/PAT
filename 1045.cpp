#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

int max(int a, int b) {return a>b?a:b;}

int main() {
    int N, M, L, tmp;
    scanf("%d", &N);
    
    scanf("%d", &M);
    if (M < 1) return 0;
    vector<char> MColors(M);
    
    for (int i=0; i<M; i++) {
        scanf("%d", &tmp);
        MColors[i] = tmp;
    }
    
    scanf("%d", &L);
    if (L < 1) return 0;
    vector<char> LColors(L);
    
    for (int i=0; i<L; i++) {
        scanf("%d", &tmp);
        LColors[i] = tmp;
    }

    int cols = M + 1;
    vector<int> curr_row(cols, 0);
    vector<int> next_row(cols, 0);
    
    for (int i = L-1; i >=0; i--) {
        for (int j = M - 1; j>=0; j--) {
            if (MColors[j] == LColors[i]) {
                curr_row[j] = next_row[j] + 1;
            } else {
                curr_row[j] = max(next_row[j], curr_row[j + 1]);
            }
        }
        swap(curr_row, next_row);
    }
    printf("%d\n", next_row[0]);
	return 0;
}

