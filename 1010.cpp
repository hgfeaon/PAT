#include <cstdio> 
#include <cstdlib>
#include <cstring>

using namespace std;

char char2num[128];

int remove_leading_zero(char* str) {
	if (str[0] == '\0') return 0;
	int ri = 0, wi = 0;
	while (str[ri] == '0') ri++;
	int len = 0;
	while ((str[wi++] = str[ri++]) != '\0') len++;
	if (len == 0) {
		str[0] == '0';
		str[++len] = '\0';
	}
	return len;
}

long long value(const char* str, int len, int radix) {
	long long ret = 0;
	long long r = 1;
	for (int i=len - 1; i>=0; i--) {
		int digit = char2num[str[i]];
		// we should check the number validation
		if (digit >= radix) return -1;
		ret += r * digit;
		r *= radix;
	}
	return ret;
}

int main() {
	// init char2num lookup table
	for (int i=0; i<10; i++) char2num['0' + i] = i;
	for (int i='a'; i<='z'; i++) char2num[i] = i - 'a' + 10;
	
	char num1[11] = {'\0'};
	char num2[11] = {'\0'};
	char *pnum1 = num1, *pnum2 = num2;
	int tag = 0, bradix = 0;
	
	scanf("%s%s%d%d", num1, num2, &tag, &bradix);
	
	// we always assure that bradix is the radix of pnum1
	// and pnum2 is which we should guess its radix
	if (tag != 1) {
		pnum1 = num2;
		pnum2 = num1;
	}
	
	long long n1 = value(pnum1, strlen(pnum1), bradix);
	long long n2 = 0;
	int n2len = remove_leading_zero(pnum2);
	
	// the only case that will have multi solution
	if (n2len == 1 && n1 <= 35) {
		// smallest possible radix, the digit +1
		printf("%ld\n", n1 + 1);
		return 0;
	}
		
	// trival case
	int lo = 1 - 1;
	int hi = 36 + 1;
	long long v = -1;
	int mid = -1;
	while (lo + 1 < hi) {
		mid = (lo + hi) / 2;
		
		v = value(pnum2, n2len, mid);
		
		if (v < 0) {
			// current radix could not represent it, radix too small
			lo = mid;
		} else if (v > n1) {
			// radix chose too big
			hi = mid;
		} else if (v < n1) {
			// radix chose too small
			lo = mid;
		} else {
			// we found it
			break;
		}
	}
	if (v == n1) {
		printf("%d\n", mid);
	} else {
		printf("Impossible");
	}

	return 0;
}

