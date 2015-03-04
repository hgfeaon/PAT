#include <cstdio>
#include <cstdlib>

using namespace std;

char line[1001];
char line2[2003];

int syslen(char str[], int start) {
	int len = 1;
	int p = start - 1;
	int q = start + 1;
	while (p >=0 && str[q] != '\0' && str[p] == str[q]) {
		p--, q++;
		len += 2;
	}
	return len;
}

int main() {
	scanf("%[^\n]s", line);
	
	int p = 0, q = 0;
	line2[p++] = ' ';
	line2[p++] = line[q++];
	while (line[q] != '\0') {
		line2[p++] = ' '; // dummy char used as seperator
		line2[p++] = line[q++];
	}
	line2[p++] = ' ';
	line2[p] = '\0';
	int max_len = 0;
	for (int i=0; i<p; i++) {
		int cur_len = syslen(line2, i);
		if (cur_len > max_len) max_len = cur_len;
	}
	printf("%d", max_len/2);
	return 0;
}

