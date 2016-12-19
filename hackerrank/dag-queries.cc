#include <cmath>
#include <cassert>
#include <set>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 100001;

int n, m, q;
vector<int> g[MAXN];

int visited[MAXN];
int visited_c = 0;

int value[MAXN];

vector<int> cached[MAXN];

void cache_traverse(int start) {
  queue<int> q;
  visited_c++;

  q.push(start);
  visited[ start ] = visited_c;

  while (!q.empty()) {
    int vert = q.front();
    cached[ start ].push_back(vert);
    q.pop();

    for (int i = 0; i < g[vert].size(); i++) {
      int new_vert = g[vert][i];
      if (visited[ new_vert ] != visited_c) {
        visited[ new_vert ] = visited_c;
        q.push(new_vert);
      }
    }
  }
}

inline void apply_value(int qt, int vert, int x) {
  if (qt == 1) value[vert] = x;
  else if (value[vert] > x) value[vert] = x;
}

void traverse(int start, int qt, int x) {
  queue<int> q;
  visited_c++;

  q.push(start);
  visited[ start ] = visited_c;

  while (!q.empty()) {
    int vert = q.front();
    q.pop();

    if (cached[vert].size()) {
      for (int i = 0; i < cached[vert].size(); i++) {
        int vv = cached[vert][i];

        apply_value(qt, vv, x);
      }
    } else {
      apply_value(qt, vert, x);

      for (int i = 0; i < g[vert].size(); i++) {
        int new_vert = g[vert][i];
        if (visited[ new_vert ] != visited_c) {
          visited[ new_vert ] = visited_c;
          q.push(new_vert);
        }
      }
    }
  }
}

void read_data() {
  cin >> n >> m >> q;
  int u, v;
  for (int i = 0; i < m; i++) {
    cin >> u >> v;
    g[u].push_back(v);
  }

  for (int i = 0; i < n; i++) {
    sort(g[i].begin(), g[i].end());
    g[i].erase( unique( g[i].begin(), g[i].end() ), g[i].end() );
  }
}


int main() {
  read_data();
  int sqn = sqrt(n);
  for (int i = 1; i <= n; i++) {
    int prob = rand() % n;
    if (prob < sqn) {
      // Selected.
      //cout << "cache " << i << endl;
      cache_traverse(i);
    }
  }

  int qt, u, x;
  for (int i = 0; i < q; i++) {
    cin >> qt;
    if (qt == 1 || qt == 2) {
      cin >> u >> x;
      traverse(u, qt, x);
    } else {
      cin >> u;
      cout << value[u] << endl;
    }
  }

  return 0;
}

