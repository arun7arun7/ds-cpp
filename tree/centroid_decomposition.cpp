#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

int n, k;
vector<vector<int>> neighbors;
vector<int> subtree_size, parent;
vector<bool> blocked;

void dfs2(int cur, int p, int dep, vector<int>& depth_sum) {
    depth_sum[dep] += 1;
    for (int neighbor : neighbors[cur]) {
        if (neighbor != p && !blocked[neighbor]) {
            dfs2(neighbor, cur, dep+1, depth_sum);
        }
    }
}

void dfs3(int cur, int p, int dep, vector<int>& depth_sum, ll& val, int& comp_size) {
    if (k-dep >= 0 && k-dep <= comp_size) {
        val += depth_sum[k-dep];
    }
    for (int neighbor : neighbors[cur]) {
        if (neighbor != p && !blocked[neighbor]) {
            dfs3(neighbor, cur, dep+1, depth_sum, val, comp_size);
        }
    }
}

ll solve_tree(int root, int comp_size) {
    vector<int> depth_sum(comp_size+1, 0);

    ll res = 0;
    for (int neighbor : neighbors[root]) {
        if (!blocked[neighbor]) {
            /*
            queue<pair<int,int>> q;
            q.push({neighbor, 1});
            ll val = 0;
            while (q.size() > 0) {
                int cur_node = q.front().first, cur_depth = q.front().second;
                if (k-cur_depth >= 0 && k-cur_depth <= comp_size) {
                    val += depth_sum[k - cur_depth];   
                }
                q.pop();
                for (int neighbor2 : neighbors[cur_node]) {
                    if (neighbor2 != cur_node && !blocked[neighbor2]) {
                        q.push({neighbor2, cur_depth+1});
                    }
                }
            }
            res += val;
            */
            ll val = 0;
            dfs3(neighbor, neighbor, 1, depth_sum, val, comp_size);
            res += val;
            dfs2(neighbor, neighbor, 1, depth_sum);            
        }
    }
    if (comp_size >= k) {
        res += depth_sum[k];
    }
    return res;
}

void dfs(int cur, int p) {
    subtree_size[cur] = 1;
    parent[cur] = p;
    for (int neighbor : neighbors[cur]) {
        if (neighbor != p && !blocked[neighbor]) {
            dfs(neighbor, cur);
            subtree_size[cur] += subtree_size[neighbor];
        }
    }
}

ll go(int entry_point) {
    dfs(entry_point, entry_point);

    queue<int> q;
    q.push(entry_point);
    int centroid = entry_point, best_size = subtree_size[entry_point];
    while (q.size() > 0) {
        int cur = q.front(), max_size = 0;
        q.pop();
        for (int neighbor : neighbors[cur]) {
            if (neighbor != parent[cur] && !blocked[neighbor]) {
                q.push(neighbor);
                max_size = max(max_size, subtree_size[neighbor]);
            }
        }
        max_size = max(max_size, subtree_size[entry_point] - subtree_size[cur]);
        if (max_size < best_size) {
            best_size = max_size;
            centroid = cur;
        }
    }

    blocked[centroid] = true;
    ll res = solve_tree(centroid, subtree_size[entry_point]);

    for (int neighbor : neighbors[centroid]) {
        if (!blocked[neighbor]) {
            res += go(neighbor);
        }
    }
    return res;
}