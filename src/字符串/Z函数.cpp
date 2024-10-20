#include <bits/stdc++.h>
using namespace std;
const int N=401010;
const int qwq=20003030;
const int inf=0x3f3f3f3f;

int n;
char s[N];
int nxt[N];

void qiu() {
    nxt[0] = n;
    for(int i=1,j=0;i<=n;i++) {
        if(j+nxt[j]>i) nxt[i] = min(nxt[i-j], j+nxt[j]-i);
        while(i+nxt[i]<n && s[nxt[i]]==s[i+nxt[i]]) nxt[i]++;
        if(i+nxt[i]>j+nxt[j]) j = i;
    }
    for(int i=0;i<n;i++) cout<<nxt[i]<<" ";
}

int main() {
    scanf("%s",s); n = strlen(s);
    qiu();
    return 0;
}

/*

abaaaba
7 0 1 1 3 0 1

*/
