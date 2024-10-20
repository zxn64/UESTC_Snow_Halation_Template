int X,Y;

int _exgcd(int A,int B) {
    if(!B) { X = Y = 0; return A; }
    int res = _exgcd(B,A%B);
    X = Y; Y = (res - A*X) / B;
    return res;
}

int exgcd(int A,int B) {
    if(!B) { X=1; Y=0; return A; }
    int res = exgcd(B,A%B);
    int t = X; X = Y; Y = t-A/B*Y;
    return res;
}

int main() {
    int a,b;
    cin>>a>>b;
    int d = exgcd(a,b);
    cout<<a<<"*"<<X<<" + "<<b<<"*"<<Y<<" = "<<d<<"\n";
    return 0;
}
