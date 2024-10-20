#include <bits/stdc++.h>
using namespace std;
const int N=2001010;
const int qwq=1003030;
const int inf=0x3f3f3f3f;

int n;
char s[N];
int nxt[N];

void kmp() {
    for(int i=2,j=0;i<=n;i++) {
        while(j && s[i]!=s[j+1]) {
            // if(j+1<i && nxt[j+1]*2>(j+1) )           // log
                // j=(j-1)%(j-nxt[j])+1;
            // else 
                j = nxt[j];
        }
        if(s[i]==s[j+1]) j++;
        nxt[i] = j;

        // zu[i] = nxt[i];
        // if(nxt[i] && (i-nxt[i])==(nxt[i]-nxt[nxt[i]])) zu[i] = zu[nxt[i]];
    }
}

int main() {
    scanf("%s",s+1); n = strlen(s+1);
    kmp();
    for(int i=1;i<=n;i++) cout<<nxt[i]<<" ";
    return 0;
}

/*

abaaabab
0 0 1 1 1 2 3 2

*/