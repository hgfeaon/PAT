#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n = 0;
    cin>>n;
    getchar();
    vector<string> strs;
    for (int i=0; i<n; i++) {
        string line;
        getline(cin, line, '\n');
        strs.push_back(line);
    }
    
    int i;
    for (i=0; i<256; i++) {
        char ch = '\0';
        int j;
        for (j=0; j<n; j++) {
            int len = strs[j].size();
            if (i >= len) break;
            if (j == 0) {
                ch = strs[j][len - i - 1];
                continue;
            }
            if (ch != strs[j][len - i - 1]) break;
        }
        if (j != n) break;
    }
    if (i == 0) {
        cout<<"nai"<<endl;
    } else {
        cout<<strs[0].substr(strs[0].size() - i)<<endl;
    }
	return 0;
}

