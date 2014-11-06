#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

bool double_num(vector<char> &num) {
    int carry = 0;
    int i = num.size() - 1;
    while (i>=0) {
        int d = num[i] * 2 + carry;
        carry = d / 10;
        num[i]= d % 10;
        i--;
    }
    return carry < 1;
}

void stat_count(vector<char>& num, int* cnt) {
    for (int i=num.size() - 1; i>=0; i--) {
        cnt[num[i]]++;
    }
}

bool is_same_digits(vector<char>& num, int* cnt) {
    int cur_cnt[10] = {0};

    stat_count(num, cur_cnt);
    
    for (int i=0; i<10; i++) {
        if (cnt[i] != cur_cnt[i]) return false;
    }
    return true;
}

void print(vector<char> &num) {
    int len = num.size();
    for (int i=0; i<len; i++) {
        printf("%d", num[i]);
    }
    printf("\n");
}

int main() {
    const int MAX_DIGITS = 20;

    vector<char> num;

    char buf[MAX_DIGITS + 1];

    int count[10] = {0};
    
    scanf("%s", buf);
    
    for (int i=0; buf[i] != '\0'; i++) {
        if (num.empty() && buf[i] == '0') continue; // skip leading zeros
        num.push_back(buf[i] - '0');
    }
    if (num.empty()) num.push_back(0);
    
    // stat original number digit count
    stat_count(num, count);
    
    bool found = false;
    bool no_carry = double_num(num);
    
    bool is_same = is_same_digits(num, count);
    if (is_same) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    if (!no_carry) printf("1");
    print(num);
	return 0;
}

