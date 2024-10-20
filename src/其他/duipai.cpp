#include <bits/stdc++.h>
using namespace std;

int main() {
    int Case = 1;
    while(1) {
        printf("The result of No. %d Case is:  ", ++Case);
        system("make");       //windows不加"./"，linux下需要在可执行文件的文件名前加"./"
        system("A");
        system("A2");
        if(system("fc A.out A2.out")) {  //linux 环境用  system("diff *** ***");
            printf("qwq");
            return 0;
        }
        else printf("No different\n");
    }
    return 0;
}