#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Stu {
public:
	char id[8];
	char name[10];
	char grade;
};

bool cmp_id(const Stu* a, const Stu* b) {
	return strcmp(a->id, b->id) < 0;
}

bool cmp_name(const Stu* a, const Stu* b) {
	int res = strcmp(a->name, b->name);
	if (res > 0) {
		return false;
	} else if (res < 0) {
		return true;
	}
	return cmp_id(a, b);
}

bool cmp_grade(const Stu* a, const Stu* b) {
	if (a->grade > b->grade) {
		return false;
	} else if (a->grade < b->grade) {
		return true;
	}
	return cmp_id(a, b);
}

int main() {
	int N, C;
	scanf("%d%d", &N, &C);
	vector<Stu*> stus(N, NULL);

	for (int i=0; i<N; i++) {
		Stu* cur = stus[i] = new Stu();
		scanf("%s%s%d", cur->id, cur->name, &(cur->grade));
	}
	
	// TODO: use function ptr array
	if (C==1) {
		sort(stus.begin(), stus.end(), cmp_id);
	} else if (C==2) {
		sort(stus.begin(), stus.end(), cmp_name);
	} else {
		sort(stus.begin(), stus.end(), cmp_grade);
	}
	
	for (int i=0; i<N; i++) {
		printf("%s %s %d\n", stus[i]->id, stus[i]->name, stus[i]->grade);
	}
	return 0;
}

