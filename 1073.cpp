#include <cstdio>
#include <cstdlib>

using namespace std;


int str2num(const char* str) {
    int v = 0;
    int i = 0;
    while (str[i] != '\0') {
        v = v * 10 + str[i] - '0';
        i++;
    }
    
    return v;
}

int main() {
    int esign= 1;
    int exp = 0;
    char int_part = '0';
    char fra_part[10009];
    char ch;
    // read sign
    scanf("%c", &ch);
    if (ch == '-') {
        printf("%c", ch);
    }
    // read int part number, 1digit
    scanf("%c", &int_part);
    
    // skip dot
    scanf("%c", &ch);
    
    // read fra part
    int fra_len = 0;
    while (true) {
        scanf("%c", &ch);
        if (ch == 'E') break;
        fra_part[fra_len++] = ch;
    }
    fra_part[fra_len] = '\0';
    
    // read exp sign
    scanf("%c", &ch);
    if (ch == '-') esign = -1;
    
    char buf[10000];
    scanf("%s", buf);
    exp = str2num(buf);
    
    if (esign >= 0 || exp == 0) {
        printf("%c", int_part);
        if (exp < fra_len) {
            for (int i=0; i<exp; i++) {
                printf("%c", fra_part[i]);
            }
            printf(".");
            for (int i=exp; i<fra_len; i++) {
                printf("%c", fra_part[i]);
            }
        } else {
            for (int i=0; i<fra_len; i++) {
                printf("%c", fra_part[i]);
            }
            for (int i=fra_len; i<exp; i++) {
                printf("0");
            }
        }
    } else {
        printf("0.");
        for (int i=1; i<exp; i++) {
            printf("0");
        }
        printf("%c", int_part);
        for (int i=0; i<fra_len; i++) {
            printf("%c", fra_part[i]);
        }
    }
    
	return 0;
}

