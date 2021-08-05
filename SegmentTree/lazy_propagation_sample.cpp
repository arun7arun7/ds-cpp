
class SegmentTree {
private:
    struct Node {
        ll val;
        ll push_val;
        
        Node(ll val) : val(val), push_val(0) {}
    };

    vector<Node*> st;
    int n, size;

    void build(int cur, int beg, int end, vector<int>& arr) {
        if (beg == end) {
            st[cur] = new Node(arr[beg]);
            return;
        }
        int mid = (beg + end) / 2;
        build(2*cur, beg, mid, arr);
        build(2*cur+1, mid+1, end, arr);
        st[cur] = new Node(st[2*cur]->val + st[2*cur+1]->val);
    }
    
    void push(int cur, int beg, int end) {
		st[2*cur]->val += st[cur]->push_val;
		st[2*cur+1]->val += st[cur]->push_val;
		st[2*cur]->push_val += st[cur]->push_val;
		st[2*cur+1]->push_val += st[cur]->push_val;
		st[cur]->push_val = 0;
	}

    void update(int cur, int beg, int end, int& l, int& r, int& delta) {
        if (beg > r || end < l) {
			return;
		}
		if (beg >= l && end <= r) {
			st[cur]->val += delta;
			st[cur]->push_val += delta;
			return;
		}
		push(cur, beg, end);
		int mid = (beg + end) / 2;
		update(2*cur, beg, mid, l, r, delta);
		update(2*cur+1, mid+1, end, l, r, delta);
        st[cur]->val = st[2*cur]->val + st[2*cur+1]->val;
    }
    
    ll query(int cur, int beg, int end, int& l, int& r) {
        if (beg > r || end < l) {
            return 0;
        }
        if (beg >= l && end <= r) {
            return st[cur]->val;
        }
        push(cur, beg, end);
        int mid = (beg + end) / 2;
        return (query(2*cur, beg, mid, l, r) + query(2*cur+1, mid+1, end, l, r));
    }

public:
    SegmentTree(vector<int>& arr, int n) {
        this->n = n;
        int x = ceil(log2(n));
        size = 2*pow(2,x) + 5;
        st.reserve(size);
        build(1, 0, n-1, arr);
    }

    void update(int l, int r, int delta) {
        update(1, 0, n-1, l, r, delta);
    }

    ll query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }

};
