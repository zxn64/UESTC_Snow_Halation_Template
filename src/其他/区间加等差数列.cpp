void add(int l,int r,db a0,db d) {
    if(l>r) return ;
    db mo = a0 + (r-l) * d;
    cha2[l] += a0;
    cha2[l+1] -= a0-d;
    cha2[r+1] -= mo+d;
    cha2[r+2] += mo;
}