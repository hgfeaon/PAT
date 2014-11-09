#include <cstdio>
#include <cstdlib>

using namespace std;

class Stu {
	public:
		char name[12];
		char id[12];
};

int main() {
	int N = 0;
	// because all the grades are distinct & grade in range of [0, 100]
	// use simplified bucket sort here
	Stu* stu[101] = {0};
	int grade;
	scanf("%d", &N);
	for (int i=0; i<N; i++) {
		Stu* tmp = new Stu();
		scanf("%s%s%d", tmp->name, tmp->id, &grade);
		stu[grade] = tmp;
	}
	
	int lo, hi;
	scanf("%d%d", &lo, &hi);
	if (lo > hi) {
		int tmp = lo;
		lo = hi;
		hi = tmp;
	}
	bool has = false;
	for (int i=hi; i>=lo; i--) {
		if (stu[i] == NULL) continue;
		has = true;
		printf("%s %s\n", stu[i]->name, stu[i]->id);
	}
	if (!has) {
		printf("NONE");
	}
	return 0;
}

