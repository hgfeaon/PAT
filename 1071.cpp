#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

char buf[1048577];

bool is_alphanumerical(char &ch) {
	if (ch >= '0' && ch <= '9') return true;
	if (ch >= 'a' && ch <= 'z') return true;
	if (ch >= 'A' && ch <= 'Z') {
		ch += 'a' - 'A';
		return true;  
	}
	return false;
}

int main() {

	char ch;
	
	bool inword = false;
	int wpos = 0;
	int max_count = -1;
	
	unordered_map<string, int> count;
	vector<string> maxs;

	while(ch = getchar()) {
		bool isan = is_alphanumerical(ch);
		if (isan) {
			if (!inword) {
				// new word begin
				wpos 	= 0;
				inword 	= true;
			}
			// append character
			buf[wpos++] = ch;
		} else {
			if (inword) {
				// current word end
				buf[wpos] = '\0';
				string word(buf);
				auto iter = count.find(word);
				if (iter == count.end()) {
					iter = count.insert(make_pair(word, 0)).first;
				}
				if (++(iter->second) > max_count) {
					max_count = iter->second;
					maxs.clear();
					maxs.push_back(word);
				} else if (iter->second == max_count) {
					maxs.push_back(word);
				}
				inword = false;
			}
		}
		if (ch == '\n') {
			break;
		}
	}
	
	sort(maxs.begin(), maxs.end());
	int mcount = count.find(maxs[0])->second;
	printf("%s %d", maxs[0].c_str(), mcount);
	return 0;
}

