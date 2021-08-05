#include <bits/stdc++.h>
#define ONLINE_JUDGE

using namespace std;

typedef long long int ll;

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

#define fo(i, k, n) for(int i=k; k<n?i<n:i>n; k<n?++i:--i)
#define flush() cout << flush;
#define pb push_back


template <typename T> void read(T& t) { cin >> t;}
template<typename T, typename... Args> void read(T& t, Args&... args) { cin >> t; read(args...);}
template <typename T> void print(T t) { cout << t;}
template<typename T, typename... Args> void print(T t, Args... args) { cout << t ; print(args...);}
template<int D, typename T> struct vec : public vector<vec<D - 1, T>> { static_assert(D >= 1, "Vector dimension must be greater than zero!");  template<typename... Args> vec(int n = 0, Args... args) : vector<vec<D - 1, T>>(n, vec<D - 1, T>(args...)) { } }; template<typename T> struct vec<1, T> : public vector<T> { vec(int n = 0, T val = T()) : vector<T>(n, val) { }};

class SegmentTree {
private:
    struct Node {
        ll val;
        ll push_val;
        int type;
        
        Node(ll val) : val(val), type(0), push_val(0) {}
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
        if(st[cur]->type == 0) {
            return;
        }
        int mid = (beg + end) / 2;
        handle(2*cur, beg, mid, st[cur]->type, st[cur]->push_val);
        handle(2*cur+1, mid+1, end, st[cur]->type, st[cur]->push_val);
        st[cur]->type = 0;
        st[cur]->push_val = 0;
	}

    void handle(int cur, int beg, int end, int type, ll val) {
        if(st[cur]->type == 0) {
            if(type == 1) {
                st[cur]->push_val += val;
                st[cur]->val += (end - beg + 1) * val;
            }
            if(type == 2) {
                st[cur]->push_val = val;
                st[cur]->val = (end - beg + 1) * val;
            }
            st[cur]->type = type;
        }
        else if(st[cur]->type == 1) {
            if(type == 1) {
                st[cur]->push_val += val;
                st[cur]->val += (end - beg + 1) * val;
            }
            if(type == 2) {
                st[cur]->push_val = val;
                st[cur]->val = (end - beg + 1) * val;
            }
            st[cur]->type = type;
        }
        else if(st[cur]->type == 2) {
            if(type == 1) {
                st[cur]->push_val += val;
                st[cur]->val = (end - beg + 1) * st[cur]->push_val;
            }
            if(type == 2) {
                st[cur]->push_val = val;
                st[cur]->val = (end - beg + 1) * st[cur]->push_val;
            }
        }
    }

    void update(int cur, int beg, int end, int& l, int& r, int type, ll& val) {
        if (beg > r || end < l) {
			return;
		}
		if (beg >= l && end <= r) {
            handle(cur, beg, end, type, val);
			return;
		}
		push(cur, beg, end);
		int mid = (beg + end) / 2;
		update(2*cur, beg, mid, l, r, type, val);
		update(2*cur+1, mid+1, end, l, r, type, val);
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

    void update(int l, int r, int type, ll delta) {
        update(1, 0, n-1, l, r, type, delta);
    }

    ll query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }

};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,q;
    read(n, q);
    vec<1, int> arr(n);
    fo(i, 0, n) {
        read(arr[i]);
    }
    SegmentTree st(arr, n);
    fo(i, 0, q) {
        int c;
        read(c);
        if(c == 1) {
            int a, b, x;
            read(a, b, x);
            --a;--b;
            debug(a, b, x);
            st.update(a, b, 1, x);
        }
        else if(c == 2) {
            int a, b, x;
            read(a, b, x);
            --a;--b;
            st.update(a, b, 2, x);
        }
        else {
            int a, b;
            read(a, b);
            --a;--b;
            ll res = st.query(a, b);
            print(res, "\n");
        }
    }
    return 0;
}
