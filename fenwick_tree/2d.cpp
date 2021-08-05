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

class Bit2D {
    vec<2, ll> bit;
    int n, m;

public:

    Bit2D(vec<2, int>& arr) {
        n = arr.size();
        m = arr[0].size();
        bit.assign(n, vec<1, ll>(m, 0));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                increase(i, j, arr[i][j]);
            }
        }
    }

    ll sum(int x, int y) {
        ll res = 0;
        for(int i = x; i >= 0 ; i = (i & (i+1))-1) {
            for(int j = y; j >= 0; j = (j & (j+1))-1) {
                res += bit[i][j];
            }
        }
        return res;
    }

    void increase(int x, int y, ll delta) {
        for(int i = x; i < n; i |= (i+1)) {
            for(int j = y; j < m; j |= (j+1)) {
                bit[i][j] += delta;
            }
        }
    }

    ll sum(int x1, int y1, int x2, int y2) {
        return sum(x2, y2) - sum(x2, y1-1) - sum(x1-1, y2) + sum(x1-1, y1-1);
    }

};