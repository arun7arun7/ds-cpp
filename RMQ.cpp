#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

class RMQ {
private:
    int n,k;
    vector<vector<int>> st;
public:
    RMQ(int n, vector<int>& a) {
        this->n = n;

        k = (int )log2(n)+1;
        st.assign(n, vector<int>(k));
        for (int i = 0; i < n; ++i) {
            st[i][0] = a[i];
        }
        for (int j = 1; j < k; j++) {
            int l = 1 << j;
            int prev = 1 << (j-1);
            for (int i = 0; i < n; ++i) {
                if (i+l-1 < n) {
                    st[i][j] = min(st[i][j-1], st[i+prev][j-1]);
                }
            }
        }
    }

    int getMin(int l, int r) {
        int j = log2(r-l+1);
        return min(st[l][j], st[r-(1<<j)+1][j]);
    }
};

