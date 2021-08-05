#include <bits/stdc++.h>

using namespace std;

template <typename T>
void readArray(vector<T>& arr, int s) {
    for (int i = 0; i < s; i++) {
        cin >> arr[i];
    }
    return arr;
}

template <typename T>
void printArray(vector<T>& arr, char delimitter) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << delimitter;
    }
    cout << endl;
}

template<typename Map> typename Map::iterator
greatest_less(Map & m, typename Map::key_type const& k) {
    typename Map::iterator it = m.lower_bound(k);
    if(it != m.begin()) {
        return --it;
    }
    return m.end();
}

template<typename Map> typename Map::iterator
greatest_less_equality_consideration(Map & m, typename Map::key_type const& k) {
    typename Map::iterator it = m.upper_bound(k);
    if(it != m.begin()) {
        return --it;
    }
    return m.end();
}

typedef long long int ll;

const ll INF = 1e18;

class SegmentTree {
private:
    struct Node {
        set<int> s;

        Node(const set<int> &s) : s(s) {}
    };

    vector<Node*> st;
    int n, size;

    void build(int cur, int beg, int end, vector<int>& arr) {
        if (beg == end) {
            set<int> s;
            s.insert(arr[beg]);
            st[cur] = new Node(s);
            return;
        }
        int mid = (beg + end) / 2;
        build(2*cur, beg, mid, arr);
        build(2*cur+1, mid+1, end, arr);
        set<int> s;
        merge(st[2*cur]->s.begin(), st[2 * cur]->s.end(), st[2 * cur + 1]->s.begin(), st[2 * cur + 1]->s.end(), inserter(s, s.end()));
        st[cur] = new Node(s);
    }

    void update(int cur, int beg, int end, int& ind, int& ele) {
        if (beg == end) {
            st[cur]->s.insert(ele);
            return;
        }
        int mid = (beg + end) / 2;
        if (ind <= mid) {
            update(2*cur, beg, mid, ind, ele);
        }
        else {
            update(2*cur+1, mid+1, end, ind, ele);
        }
        st[cur]->s.insert(ele);
    }

public:
    const int int_inf = 1e9 + 5;
    SegmentTree(vector<int>& arr, int n) {
        this->n = n;
        int x = ceil(log2(n));
        size = 2*pow(2,x) + 5;
        st.reserve(size);
        build(1, 0, n-1, arr);
    }

    void update(int ind, int ele) {
        update(1, 0, n-1, ind, ele);
    }

    ll compute(int l, int r, int k) {
        ll f_min = query1(1, 0, n-1, l, r, k);
        ll f_max = query2(1, 0, n-1, l, r, k);
        return f_max - f_min;
    }

    ll query1(int cur, int beg, int end, int& l, int& r, int& k) {
        if (beg > r || end < l) {
            return INF;
        }
        if (beg >= l && end <= r) {
            auto pInt = greatest_less_equality_consideration(st[cur]->s, k);
            // int* pInt = st[cur].s.findPredecessorWithEqualityConsideration(k);
            ll res = INF;
            if (pInt != st[cur]->s.end()) {
                res = min(res, ((ll)(k - *pInt) * (k - *pInt)));
            }
            auto sInt = st[cur]->s.lower_bound(k);
            // int* sInt = st[cur].s.findSuccessorWithEqualityConsideration(k);
            if (sInt != st[cur]->s.end()) {
                res = min(res, ((ll)(k - *sInt) * (k - *sInt)));
            }
            return res;
        }
        int mid = (beg + end) / 2;
        return min(query1(2*cur, beg, mid, l, r, k), query1(2*cur+1, mid+1, end, l, r, k));
    }

    ll query2(int cur, int beg, int end, int& l, int& r, int& k) {
        if (beg > r || end < l) {
            return -INF;
        }
        if (beg >= l && end <= r) {
            auto pInt = greatest_less_equality_consideration(st[cur]->s, int_inf);
            // int* pInt = st[cur].s.findPredecessorWithEqualityConsideration(int_inf);
            ll res = -INF;
            if (pInt != st[cur]->s.end()) {
                res = max(res, ((ll)(k - *pInt) * (k - *pInt)));
            }
            auto sInt = st[cur]->s.lower_bound(-int_inf);
            // int* sInt = st[cur].s.findSuccessorWithEqualityConsideration(-int_inf);
            if (sInt != st[cur]->s.end()) {
                res = max(res, ((ll)(k - *sInt) * (k - *sInt)));
            }
            return res;
        }
        int mid = (beg + end) / 2;
        return max(query2(2*cur, beg, mid, l, r, k), query2(2*cur+1, mid+1, end, l, r, k));
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,q;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        int x,y;
        cin >> x >> y;
        arr[i] = abs(x+y);
    }

    SegmentTree segmentTree(arr, n);
    cin >> q;
    // vector<ll> res;
    for (int i = 0; i < q; ++i) {
        char ch;
        cin >> ch;
        if (ch == '+') {
            int i,x,y;
            cin >> i >> x >> y;
            segmentTree.update(i-1, abs(x+y));
        }
        else {
            int l,r,k;
            cin >> l >> r >> k;
            ll ans = segmentTree.compute(l-1, r-1, k);
            cout << ans << '\n';
        }
    }
    // printArray(res, '\n');
    return 0;
}