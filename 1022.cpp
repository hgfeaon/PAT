#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

unordered_map<string, vector<int> > idx_title;
unordered_map<string, vector<int> > idx_author;
unordered_map<string, vector<int> > idx_keyword;
unordered_map<string, vector<int> > idx_publisher;
unordered_map<string, vector<int> > idx_year;

unordered_map<string, vector<int> >* idx[6] = {NULL, &idx_title, &idx_author, &idx_keyword, &idx_publisher, &idx_year};

void idx_add_book(unordered_map<string, vector<int> >& idx, const string& key, int book_id) {
	auto iter = idx.find(key);
	if (iter == idx.end()) {
		iter = idx.insert(make_pair(key, vector<int>())).first;
	}
	iter->second.push_back(book_id);
}

int main() {
	
	int N, M;
	scanf("%d", &N);

	char ibuf[100] = {0};
	int bid = 0;
	for (int i=0; i<N; i++) {
		scanf("%d", &bid);
		getchar();
		// read title
		scanf("%[^\n]", ibuf);
		idx_add_book(idx_title, string(ibuf), bid);
		getchar();
		// read author
		scanf("%[^\n]", ibuf);
		idx_add_book(idx_author, string(ibuf), bid);
		getchar();
		// read keywords
		for (;;) {
			scanf("%[^ \n]", ibuf);
			idx_add_book(idx_keyword, string(ibuf), bid);
			if (getchar() == '\n') {
				break;
			}
		}
		// read publisher
		scanf("%[^\n]", ibuf);
		idx_add_book(idx_publisher, string(ibuf), bid);
		getchar();
		// read year
		scanf("%[^\n]", ibuf);
		idx_add_book(idx_year, string(ibuf), bid);
		getchar();
	}

	scanf("%d", &M);
	string buf;
	for (int i=0; i<M; i++) {
		int idx_type = 0;
		scanf("%d", &idx_type);
		getchar();
		getchar();
		if (idx_type < 1 || idx_type > 5) {
			break;
		}
		getline(cin, buf);
		printf("%d: %s\n", idx_type, buf.c_str());
		auto dict = idx[idx_type];
		if (dict == NULL) {
			break;
		}
		auto iter = dict->find(buf);
		if (iter == dict->end()) {
			printf("Not Found\n");
			continue;
		}
		auto v = iter->second;
		sort(v.begin(), v.end());
		int len = v.size();
		for (int i=0; i<len; i++) {
			printf("%07d\n", v[i]);
		}
	}

	return 0;
}

