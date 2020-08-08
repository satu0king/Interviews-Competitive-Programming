// https://codeforces.com/blog/entry/71146
// https://leetcode.com/problems/critical-connections-in-a-network/submissions/
// https://pastebin.com/7MWuxdLQ
// https://pastebin.com/ATwq4mJa
// https://codeforces.com/blog/entry/68138 (best)

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

vector<int> articulationPoints;
vector<vector<int>> bridges;

vector<vector<int>> g;
// Earliest ancestor I can reach by using a back edge either directly 
// or by going down the tree and finding a back edge
vector<int> lowestAncestorTime; 
vector<int> discoveryTime;
int currentTime = 0;

void dfs(int u, int parent = -1) {
  if (discoveryTime[u])
    return; // Already processed

  discoveryTime[u] = lowestAncestorTime[u] = ++currentTime;

  bool isArticulationVertex = false;
  int children = 0;
  for (int v : g[u]) {
    if (v == parent)
      continue;
    if (!discoveryTime[v]) { // Is Child
      children++;
      dfs(v, u);
      lowestAncestorTime[u] = min(lowestAncestorTime[u], lowestAncestorTime[v]);
      if (lowestAncestorTime[v] > discoveryTime[u]) {
        // Cannot reach me or above in alternate ways, so this is a bridge
        vector<int> t = {u, v};
        sort(t.begin(), t.end());
        bridges.push_back(t);
      }

      if (lowestAncestorTime[v] >= discoveryTime[u]) {
        // Cannot reach above me in alternate ways, so this is an articulation vertex
        // Except if I am a leaf node
        isArticulationVertex = true;
      }
    } else {
      lowestAncestorTime[u] = min(lowestAncestorTime[u], discoveryTime[v]);
    }
  }
  if (isArticulationVertex) {
    if (parent != -1 || children > 1)
      articulationPoints.push_back(u);
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  g.resize(n);
  lowestAncestorTime.resize(n);
  discoveryTime.resize(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(0);
}
