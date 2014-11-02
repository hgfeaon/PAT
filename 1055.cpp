#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define AGE_MAX 200

class People {
public:
	char name[9];
	int worth;
	int age;
	int idx;
	People(const char* _name, int _worth = 0, int _age = 0) {
		strcpy(name, _name);
		worth 	= _worth;
		age 	= _age;
		idx 	= 0; 
	}
};

bool people_compare(const People* a, const People* b) {
	if (a->worth > b->worth) {
		return true;
	} else if (a->worth < b->worth) {
		return false;
	}
	if (a->age < b->age) {
		return true;
	} else if (a->age > b->age) {
		return false;
	}
	
	return strcmp(a->name, b->name) < 0;
}

class mycmp {
public:
	bool operator() (const People* a, const People* b) {
		return !people_compare(a, b);
	}
};



int main() {
	int N = 0, K = 0;
	scanf("%d%d", &N, &K);
	
	vector<vector<People*> > peoples(AGE_MAX + 1);
	
	char name[10] = {'\0'};
	int worth = 0, age = 0;
	
	for (int i=0; i<N; i++) {
		scanf("%s%d%d", name, &age, &worth);
		peoples[age].push_back(new People(name, worth, age));
	}
	
	for (int i=0; i<=AGE_MAX; i++) {
		vector<People*>& list = peoples[i];
		if (!list.size()) continue;
		// sort people in each age list
		sort(list.begin(), list.end(), people_compare);
		
		for (int j=0; j<list.size(); j++) {
			list[j]->idx = j;
		}
	}
	
	for (int i=0; i<K; i++) {
		int M = 0, Amin = 0, Amax = 0;
		scanf("%d%d%d", &M, &Amin, &Amax);
		
		priority_queue<People*, vector<People*>, mycmp> age_leader;
		
		for(int j = Amin; j <= Amax; j++) {
			if (peoples[j].empty()) continue;
			age_leader.push(peoples[j].front());
		}
		printf("Case #%d:\n", i + 1);
		int m = 0;
		while (!age_leader.empty() && m < M) {
			m++;
			People* leader = age_leader.top();
			age_leader.pop();
			
			printf("%s %d %d\n", leader->name, leader->age, leader->worth);
			if (leader->idx + 1 >= peoples[leader->age].size()) continue;
			age_leader.push(peoples[leader->age][leader->idx + 1]);
		}
		if (m == 0) {
			printf("None\n");
		}
	}
	
	return 0;
}

