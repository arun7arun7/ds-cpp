class Dsu {
	int n;
	vector<int> parent, size;
public:
	Dsu(int n) {
		this->n = n;
		parent.resize(n);
		size.assign(n, 1);
		for (int i = 0; i < n; i++) {
			parent[i] = i;
		}
	}
	
	void union_sets(int a, int b) {
		a = find_sets(a);
		b = find_sets(b);
		if (a != b) {
			if (size[a] < size[b]) {
				swap(a, b);
			}
			parent[b] = a;
			size[a] += size[b];
		}
	}
	
	int find_sets(int v) {
		if (v == parent[v]) {
			return v;
		}
		return parent[v] = find_sets(parent[v]);
	}
	
	int size_of_component(int v) {
		return size[find_sets(v)];
	}
	
};
