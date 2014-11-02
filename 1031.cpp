#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

char line[82];
char space[82];

int main() {
	scanf("%s", line);
	int len = strlen(line);
	int side_size = (len + 2) / 3 - 1;
	int last_size = len - side_size * 2;
	int space_size= last_size - 2;

	for (int i=0; i<space_size; i++) {
		space[i] = ' ';
	}
	
	const char* p = line;
	const char* q = line + len - 1;
	for (int i=0; i<side_size; i++) {
		printf("%c%s%c\n", *p++, space, *q--);
	}
	for (int i=0; i<last_size; i++) {
		printf("%c", *p++);
	}
	
	return 0;
}

