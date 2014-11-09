#include <cstdio>
#include <cstdlib>

using namespace std;

int main() {
    bool tbl[256] = {0};
    char line[10009];
    int len = 0;
    char ch;
    while (true) {
        scanf("%c", &ch);
        if (ch == '\n') break;
        line[len++] = ch;
    }
    line[len] = '\0';

    while (true) {
        scanf("%c", &ch);
        if (ch == '\n') break;
        tbl[ch] = true;
    }
    
    int wpos = 0, rpos = 0;
    while (rpos < len) {
        ch = line[rpos++];
        if (tbl[ch]) {
            continue;
        }
        line[wpos++] = ch;
    }
    line[wpos] = '\0';
    printf("%s", line);
	return 0;
}

