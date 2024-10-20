#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int N=5050505;

char s[N];
int n;
int ans;

int main() {
	scanf("%s",s+1); n = strlen(s+1);
	for(int i=1;i<=n;) {
		int j=i, k=i+1;
		while(k<=n && s[j]<=s[k]) {
			if(s[j]<s[k]) j = i;
			else j++;
			k++;
		}
		while(i<=j) {
			ans ^= i+k-j-1;
			i += k-j;
		}
	}
	cout<<ans;
	return 0;
}

/*

bbababaabaaabaaaab

*/

