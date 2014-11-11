#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N = 0;
	double D = 0;
	scanf("%d%lf", &N, &D);
	vector<pair<double, double> > base(N);
	vector<double> amount(N);
	vector<double> price(N);
	double tmp;
	for (int i=0; i<N; i++) {
		scanf("%lf", &amount[i]);
	}
	for (int i=0; i<N; i++) {
		scanf("%lf", &price[i]);
		base[i].first = amount[i] / price[i];
		base[i].second= i;
	}
	
	sort(base.begin(), base.end());
	
	double cur = 0;
	double mon = 0;
	int i = 0;

	while(cur < D && i < N) {
		int idx = base[i].second;
		double use = amount[idx];
		if ((use + cur) >= D) use = D - cur;
		mon += use / amount[idx] * price[idx];
		cur += use;
		i++;
	}
	printf("%.2lf", mon);
	return 0;
}

