#include <bits/stdc++.h>
#define ll long long

using namespace std;
const ll N=201010;

ll rrand(ll L,ll R) {
	return (rand() * rand() + rand()) % (R-L+1) + L;
}

ll T = 10, n ;

int main() {
	freopen("data.in","w",stdout);
	srand(time(NULL)^getpid());
	mt19937_64 rng(random_device{}());
	// val[i] = rng();
	cout<<T<<"\n";
	while(T--) {

	}
	return 0;
}