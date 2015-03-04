#include <cstdio>
#include <cstdlib>

using namespace std;

long long gcd(long long a, long long b) {
	long long r;
	while (r = (a % b)) {
		a = b;
		b = r;
	}
	return b;
}

int main() {

	int N;
	scanf("%d", &N);
	long long sa = 0, sb = 1, a, b;
	
	for (int i=0; i<N; i++) {
		scanf("%lld/%lld", &a, &b);
		long long newb = b * sb / gcd(b, sb);
		long long sf =  newb / sb;
		long long cf =  newb / b;
		sa = sa * sf + a * cf;
		sb = newb;
		long long c = gcd(sa < 0 ? -sa : sa, sb);
		sa = sa/c;
		sb = sb/c;
	}
	
	if (sa < 0) {
		printf("-");
		sa = -sa;
	}
	long long r = sa % sb;v
	long long q = sa / sb;
	if (r == 0) {
		printf("%lld\n", q);
	} else {
		if (q != 0) {
			printf("%lld ", q);
		}
		printf("%lld/%lld\n", r, sb);
	}
	
	return 0;
}

