#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;
char tbl[] = {	'0', '1', '2', '3', 
				'4', '5', '6', '7',
				'8', '9', 'A', 'B', 'C'};
void d213(int d, int &m, int &l) {
	l = d % 13;
	m = d / 13;
}

void print13(int m, int l) {
	printf("%c%c", tbl[m], tbl[l]);
}
int main() {
	int d = 0;
	int m, l;
	printf("#");
	for (int i=0; i<3; i++) {
		scanf("%d", &d);
		d213(d, m, l);
		print13(m, l);
	}
	return 0;
}

