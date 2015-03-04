#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

bool mycmp(const string& a, const string& b) {
	string ta = a + b;
	string tb = b + a;
	
	int len = ta.length();
	
	for (int i=0; i<len; i++) {
		if (ta[i] > tb[i]) {
			return false;
		} else if (ta[i] < tb[i]){
			return true;
		}
	}
	return true;
}

bool print_no_leading_zero(string &n) {
	int len = n.length();
	bool full_zero = true;
	int i;
	for (i=0; i<len; i++) {
		if (n[i] != '0') {
			full_zero = false;
			break;
		}
	}
	while (i<len) {
		cout<<n[i++];
	}
	return full_zero;
}

int main() {
	string is;
	int N = 0;
	cin>>N;
	
	vector<string> segs(N);
	for (int i=0; i<N; i++) {
		cin>>segs[i];
	}
	
	int len = segs.size();

	sort(segs.begin(), segs.end(), mycmp);
	
	bool zero = true;
	if (len > 0) {
		for (int i=0; i<len; i++) {
			if (zero) {
				zero = print_no_leading_zero(segs[i]);
			} else {
				cout<<segs[i];
			}
		}
		
	} 
	if (len < 1 || zero) {
		cout<<0;
	}
	cout<<endl;
	return 0;
}

