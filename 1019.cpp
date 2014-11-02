#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;

void print(int d[], int s, int e, const char* msg) {
	printf("%s\n", msg);
	if (s == e) {
		printf("0");
		return;
	}
	printf("%d", d[s]);
	for (int i=s+1; i<e; i++) {
		printf(" %d", d[i]);
	}
}

int main() {
	int n = 0, b = 0;
	scanf("%d%d", &n, &b);
	int ds[32] = {0};
	
	int e = 31;
	while(n) {
		ds[e--] = n % b;
		n /= b;
	}
	
	int p = e + 1, q = 31;
	while (p < q) {
		if (ds[p] != ds[q]) break;
		p++, q--;
	}
	if (p < q) {
		print(ds, e + 1, 32, "No");
	} else {
		print(ds, e + 1, 32, "Yes");
	}
	return 0;
}

