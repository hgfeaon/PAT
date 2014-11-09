#include <cstdio>
#include <cstdlib>

using namespace std;

class Number {
public:
	int a;
	int b;
	int c;
	Number(int _a = 0, int _b = 0, int _c = 0): a(_a), b(_b), c(_c){}
	Number operator+(const Number& n) {
		Number tmp;
		tmp.a = a + n.a;
		tmp.b = tmp.a / 29;
		tmp.a = tmp.a % 29;
		
		tmp.b += b + n.b;
		tmp.c = tmp.b / 17;
		tmp.b = tmp.b % 17;
		
		tmp.c += c + n.c;
		tmp.c = tmp.c;
		return tmp;
	}
	void print() {
		printf("%d.%d.%d", c, b, a);
	}
};

int main() {
	Number n1, n2;
	scanf("%d.%d.%d", &n1.c, &n1.b, &n1.a);
	scanf("%d.%d.%d", &n2.c, &n2.b, &n2.a);

	Number n3 = n1 + n2;
	n3.print();
	return 0;
}

