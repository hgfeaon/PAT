#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Stu {
    public:
        char name[12];
        char id[12];
        int grade;
        char gender;
};

bool my_cmp(const Stu* a, const Stu* b) {
    return a->grade < b->grade;
}

void print (vector<Stu*> &stu) {
    int len = stu.size();
    for (int i=0; i<len; i++) {
        printf("%s %d\n", stu[i]->name, stu[i]->grade);
    }
}

int main() {
    vector<Stu*> male;
    vector<Stu*> female;
    int n = 0;
    scanf("%d", &n);
    
    for (int i=0; i<n; i++) {
        Stu* p = new Stu();
        scanf("%s %c %s %d", p->name, &(p->gender), p->id, &(p->grade));
        
        if (p->gender == 'M') {
            male.push_back(p);
        } else {
            female.push_back(p);
        }
    }
    sort(male.begin(), male.end(), my_cmp);
    sort(female.begin(), female.end(), my_cmp);

    Stu* best = NULL;
    Stu* worst= NULL;
    
    if (female.empty()) {
        printf("Absent\n");
    } else {
        best = female[female.size() - 1];
        printf("%s %s\n", best->name, best->id);
    }
    if (male.empty()) {
        printf("Absent\n");
    } else {
        worst = male[0];
        printf("%s %s\n", worst->name, worst->id);
    }
    if (worst == NULL || best == NULL) {
        printf("NA\n");
    } else {
        printf("%d", best->grade - worst->grade);
    }
	return 0;
}

