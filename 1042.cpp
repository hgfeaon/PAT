#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

char tbl[5] = {'S', 'H', 'C', 'D', 'J'};

void shuffle(vector<char> &card, vector<char> &rnd) {
	int rlen= rnd.size();
	vector<char> tmp(card.size(), 0);
	for (int i=0; i<rlen; i++) {
		tmp[rnd[i]] = card[i];
	}
	card = tmp;
}

void print_card(char card) {
	printf("%c%d", tbl[card/13], card % 13 + 1);
} 

int main() {
	int times = 0, r = 0;
	vector<char> rnd(54, 0);
	vector<char> card(54, 0);
	for (int i=0; i<54; i++) {
		card[i] = i;
	}
	scanf("%d", &times);
	for (int i=0; i<54; i++) {
		scanf("%d", &r);
		rnd[i] = r - 1;
	}
	for (int i=0; i<times; i++) {
		shuffle(card, rnd);
	}
	print_card(card[0]);
	for (int i=1; i<54; i++) {
		printf(" ");
		print_card(card[i]);
	}
	return 0;
}

