#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

class Stu {
public:
	int idx;
	int egrade;
	int igrade;
	double fgrade;
	int rank;
	int choice[6];
};

class School {
public:
	int quota;
	vector<int> accept;	
};

bool mycmp(const Stu* a, const Stu* b) {
	if (a->fgrade > b->fgrade) {
		return true;
	} else if (a->fgrade < b->fgrade){
		return false;
	}
	
	if (a->egrade > b->egrade) {
		return true;
	} else if (a->egrade < b->egrade) {
		return false;
	}
	
	return false;
}

void do_admission(Stu* stu, vector<Stu*>& stus, vector<School*>& schools, int K) {
	for (int i=0; i<K; i++) {
		School* school = schools[stu->choice[i]];
		if (school->quota == 0) {
			// skip no quota schools
			continue;
		}
		if (school->quota > school->accept.size()) {
			// school quota available, accept
			school->accept.push_back(stu->idx);
			break;
		}
		if (stus[school->accept.back()]->rank == stu->rank) {
			// school quota used up, but if last accepted rank is 
			// equal to current stu rank, accept it any way 
			school->accept.push_back(stu->idx);
			break;
		}
	}
}

int main() {
	int N, M, K;
	scanf("%d%d%d", &N, &M, &K);
	
	vector<School*> schools(M, NULL);
	vector<Stu*> stus(N, NULL);
	
	for (int i=0; i<M; i++) {
		School* tmp = new School();
		schools[i] = tmp;
		tmp->accept.clear();
		scanf("%d", &(tmp->quota));
	}
	
	for (int i=0; i<N; i++) {
		Stu* tmp = new Stu();
		tmp->idx = i;
		tmp->rank= 0;
		scanf("%d%d", &(tmp->egrade), &(tmp->igrade));
		tmp->fgrade = (tmp->egrade + tmp->igrade) / 2.0;
		for (int j=0; j<K; j++) {
			scanf("%d", tmp->choice + j);
		}
		stus[i] = tmp;
	}
	
	sort(stus.begin(), stus.end(), mycmp);
	
	int last_rank = 0;
	double last_fgrade = -1;
	int last_egrade = -1;
	
	for (int i=0; i<N; i++) {
		Stu& cur = *stus[i];
		if (cur.fgrade != last_fgrade || cur.egrade != last_egrade) {
			last_egrade = cur.egrade;
			last_fgrade = cur.fgrade;
			cur.rank = i + 1;
		} else {
			cur.rank = last_rank;
		}
		last_rank = cur.rank;
		
		do_admission(stus[i], stus, schools, K);	
	}
	
	for (int i=0; i<M; i++) {
		School* school = schools[i];
		int len = school->accept.size();

		sort(school->accept.begin(), school->accept.end());
		
		if (len > 0) {
			printf("%d", school->accept[0]);
		}
		for (int j=1; j<len; j++) {
			printf(" %d", school->accept[j]);
		}
		if (i != M-1) {
			printf("\n");
		}
	}
	return 0;
}

