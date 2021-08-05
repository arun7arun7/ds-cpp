int n,sz;
vector<vector<int>> st;
vector<int> parent, depth;

void process() {
	sz = (int)log2(n) + 1;
	st.assign(n, vector<int>(sz, -1));
	for (int i = 0; i < n; i++) {
		st[i][0] = parent[i];
	}
	for (int j = 1; j < sz; j++) {
		for (int i = 0; i < n; i++) {
			if (st[i][j-1] != -1) {
				st[i][j] = st[st[i][j-1]][j-1];
			}
		}
	}
}

int kth_ancesstor(int x, int k) {
	int bit = 0;
	while (bit < sz && x != -1){
		if (k & (1 << bit)) {
			x = st[x][bit];
		}
		bit++;
	}
	return x;
}

int lca(int a, int b) {
	if (depth[a] < depth[b]) {
		swap(a,b);
	}
	int dist = depth[a] - depth[b];
	a = kth_ancesstor(a, dist);
	if (a == b) {
		return a;
	}
	int bit = sz-1;
	while (bit >= 0) {
		if (st[a][bit] != st[b][bit]) {
			a = st[a][bit];
			b = st[b][bit];
		}
		bit--;
	}
	return parent[a];
}
