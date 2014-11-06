#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

void print(vector<char> &num) {
    int len = num.size();
    bool value_begin = false;
    for (int i=0; i<len; i++) {
        if (!value_begin && num[i] == 0) continue; // skip leading zeros;
        value_begin = true;
        printf("%d", num[i]);
    }
    if (!value_begin) {         // totally zero
        printf("0");
    }
}

vector<char> num2vec(long long num) {
    vector<char> ret;

    while (num) {
        ret.push_back(num % 10);
        num /= 10;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

vector<char> add(vector<char> &a, vector<char> &b) {
    vector<char> ret;
    int alen = a.size();
    int blen = b.size();
    int carry= 0;
    while (alen > 0 && blen > 0) {
        int d = carry + a[--alen] + b[--blen];
        carry = d / 10;
        d = d % 10;
        ret.push_back(d);
    }
    
    while (alen > 0) {
        int d = carry + a[--alen];
        carry = d / 10;
        d = d % 10;
        ret.push_back(d);
    }
    while (blen > 0) {
        int d = carry + b[--blen];
        carry = d / 10;
        d = d % 10;
        ret.push_back(d);
    }
    if (carry) ret.push_back(1);
    reverse(ret.begin(), ret.end());
    return ret;
}

vector<char> pal(vector<char> &num) {
    vector<char> ret = num;
    reverse(ret.begin(), ret.end());
    return ret;
}

bool is_pal(vector<char> &num) {
    int len = num.size();
    int p = 0, q = len - 1;
    while (p < q) {
        if (num[p] != num[q]) break;
        ++p, --q;
    }
    return p >= q;
}

int main() {
    long long n = 0, k = 0, i = 0;
    scanf("%ld%ld", &n, &k);
    vector<char> num = num2vec(n);
    for (i=0; i<k; i++) {
        if (is_pal(num)) {
            break;
        }
        vector<char> pnum = pal(num);
        vector<char> tnum = add(pnum, num);
        swap(num, tnum);
    }
    print(num);
    printf("\n%d", i);
	return 0;
}

