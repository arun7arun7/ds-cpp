#include <bits/stdc++.h>

using namespace std;

template <typename T>
vector<T> readArray(vector<T>& arr, int s) {
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
const int inf = 1e9+5;
const ll INF = 1e18;

class SegmentTree {
private:
    struct Node {
        int val;

        Node(int val) : val(val) {}
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
        st[cur] = new Node(max(st[2*cur]->val, st[2*cur+1]->val));
    }

    void update(int cur, int beg, int end, int& ind, int& ele) {
        if (beg == end) {
            st[cur]->val = ele;
            return;
        }
        int mid = (beg + end) / 2;
        if (ind <= mid) {
            update(2*cur, beg, mid, ind, ele);
        }
        else {
            update(2*cur+1, mid+1, end, ind, ele);
        }
        st[cur] = new Node(max(st[2*cur]->val, st[2*cur+1]->val));
    }

public:
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

    int query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }

    int query(int cur, int beg, int end, int& l, int& r) {
        if (beg > r || end < l) {
            return -inf;
        }
        if (beg >= l && end <= r) {
            return st[cur]->val;
        }
        int mid = (beg + end) / 2;
        return max(query(2*cur, beg, mid, l, r), query(2*cur+1, mid+1, end, l, r));
    }

};






int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n+2), px(n+2);
    a[0] = 0;
    px[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        px[i] = px[i-1] ^ a[i];
    }
    a[n+1] = inf;
    px[n+1] = px[n] ^ a[n+1];


    map<int,int> mp1, mp2;
    for (int i = 0; i < n+2; ++i) {
        mp1[a[i] ^ px[i]];
    }
    for (int i = 0; i < n+2; ++i) {
        mp2[px[i]];
    }

    int ind1 = 0, ind2 = 0;
    for (auto it : mp1) {
        mp1[it.first] = ind1++;
    }
    for (auto it : mp2) {
        mp2[it.first] = ind2++;
    }
    vector<int> arr1(ind1, -inf), arr2(ind2, -inf);
    SegmentTree st1(arr1, arr1.size()), st2(arr2, arr2.size());

    int ans = inf;
    for (int i = 0; i <= n; ++i) {
        auto it1 = mp1.upper_bound(px[i]);
        if (it1 != mp1.end()) {
            int i1 = it1->second;
            int max_j = st1.query(i1, ind1-1);
            if (max_j != -inf) {
                ans = min(ans, i-max_j);
            }
        }
        st1.update(mp1[a[i]^px[i]], i);

        auto it2 = mp2.upper_bound(a[i+1] ^ px[i]);
        if (it2 != mp2.end()) {
            int i2 = it2->second;
            int max_j = st2.query(i2, ind2-1);
            if (max_j != -inf) {
                ans = min(ans, i-max_j);
            }
        }
        st2.update(mp2[px[i]], i);
    }

    if (ans == inf) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }
    return 0;
}