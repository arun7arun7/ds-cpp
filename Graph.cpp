//
// Created by arun07 on 01-11-2020.
//
#include <bits/stdc++.h>

using namespace std;
class Graph {
    int n;
    vector<vector<int>> neighbors;

    Graph(int n) {
        this->n = n;
        neighbors.assign(n, vector<int>);
    }

    void addEdge(int a, int b) {
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }
};
