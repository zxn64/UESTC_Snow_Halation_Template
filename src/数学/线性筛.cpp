// p[]
for(int i=2; i<=h; i++) {
	if(!vis[i]) p[++cnt] = i;
	for(int j=1; j<=cnt && i*p[j]<=h; j++) {
		vis[ i*p[j] ] = 1;
		if(i%p[j]==0) break;
	}
}

// phi[]
for(int i=2; i<=h; i++) {
	if(!vis[i]) {
		p[++cnt] = i;
		phi[i] = i-1;
	}
	for(int j=1; j<=cnt && i*p[j]<=h; j++) {
		vis[ i*p[j] ] = 1;
		if(i%p[j]==0) {
			phi[ i*p[j] ] = phi[i] * p[j];
			break;
		}
		phi[ i*p[j] ] = phi[i] * (p[j]-1);
	}
}

// d[]    number of factors
d[1] = 1;
for(int i=2; i<=n; i++) {
    if(!vis[i]) {
        p[++cnt] = i;
        d[i] = 2; g[i] = 1;
    }
    for(int j=1; j<=cnt && i*p[j]<=n; j++) {
        vis[ i*p[j] ] = 1;
        if(i%p[j]==0) {
            d[ i*p[j] ] = d[i] / (g[i]+1) * (g[i]+2);
            g[ i*p[j] ] = g[i] + 1;
            break;
        }
        d[ i*p[j] ] = d[i] * 2;
        g[ i*p[j] ] = 1;
    }
}

// f[]    sum of factors
f[1] = 1;
for(int i=2; i<=n; i++) {
	if(!vis[i]) {
		p[++cnt] = i;
		f[i] = i+1; g[i] = 1;
	}
	for(int j=1; j<=cnt && i*p[j]<=n; j++) {
		vis[ i*p[j] ] = 1;
		if(i%p[j]==0) {
			f[ i*p[j] ] = f[i] * p[j] + g[i];
			g[ i*p[j] ] = g[i];
			break;
		}
		f[ i*p[j] ] = f[i] * (p[j]+1);
		g[ i*p[j] ] = f[i];
	}
}

// mu[]
mu[1] = 1;
for(int i=2; i<=n; i++) {
	if(!vis[i]) {
		p[++cnt] = i;
		mu[i] = -1;
	}
	for(int j=1; j<=cnt && i*p[j]<=n; j++) {
		vis[ i*p[j] ] = 1;
		if(i%p[j]==0) break;    //mu[i*p[j]]=0；就没必要写了。
		mu[ i*p[j] ] = -mu[i];
	}
}