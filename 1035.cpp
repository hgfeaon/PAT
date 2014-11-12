#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

class Item {
public:
	char uid[12];
	char pwd[12];
};

char tbl[256];

void init_tbl() {
	for (int i=0; i<256; i++) {
		tbl[i] = i;
	}
	tbl['1'] = '@';
	tbl['0'] = '%';
	tbl['l'] = 'L';
	tbl['O'] = 'o';
}

int main() {
	int N;
	scanf("%d", &N);
	vector<Item> ids(N);
	vector<int> changed;
	
	init_tbl();
	
	int len = ids.size();
	for (int i=0; i<len; i++) {
		scanf("%s%s", ids[i].uid, ids[i].pwd);
		bool updated = false;
		int k = 0;
		char ch = '\0';
		while ((ch = ids[i].pwd[k]) != '\0') {
			if (ch != tbl[ch]) {
				ids[i].pwd[k] = tbl[ch];
				updated = true;
			}
			k++;
		}
		if (updated) {
			changed.push_back(i);
		}
	}
	
	int clen = changed.size();
	
	if (clen == 0) {
		if (N != 1) {
			printf("There are %d accounts and no account is modified\n", N);
		} else {
			printf("There is 1 account and no account is modified\n");
		}
	} else {
		printf("%d\n", clen);
		for (int i=0; i<clen; i++) {
			printf("%s %s\n", ids[changed[i]].uid, ids[changed[i]].pwd);
		}
	}
	
	return 0;
}

