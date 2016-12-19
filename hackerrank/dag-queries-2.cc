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

bool is_traversed[MAXN];
set<int> visibles[MAXN];


void traverse(int start) {
  if (visibles[start].size()) {
    return;
  }

  queue<int> q;
  visited_c++;

  q.push(start);
  visited[ start ] = visited_c;

  while (!q.empty()) {
    int vert = q.front();
    visibles[ start ].insert(vert);
    q.pop();

    for (int i = 0; i < g[vert].size(); i++) {
      int new_vert = g[vert][i];
      if (visited[ new_vert ] != visited_c) {
        visited[ new_vert ] = visited_c;

        if (visibles[ start ].count(new_vert)) {
          continue;
        }

        if (visibles[ new_vert ].size()) {
          visibles[ start ].insert(visibles[ new_vert ].begin(), visibles[ new_vert ].end());
        } else {
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

struct Query {
  int qt, u, x;

  bool affects(int v) {
    if (qt == 1 || qt == 2) {
      int u = this->u;
      traverse(u);
      return visibles[u].count(v);
    } else {
      return false;
    }
  }
};

Query queries[MAXN];



int main() {
  read_data();

  int qt, u, x;
  vector<int> interesting;
  for (int i = 0; i < q; i++) {
    cin >> queries[i].qt;
    if (queries[i].qt <= 2) {
      cin >> queries[i].u >> queries[i].x;
    } else {
      cin >> u;
      //cout << "u=" << u << endl;
      int first_interesting = 0;
      interesting.clear();
      for (int j = i - 1; j >= 0; j--) {
        if (queries[j].affects(u)) {
          interesting.push_back(j);
          if (queries[j].qt == 1) {
            //cout << "Back to " << j << endl;
            break;
          }
        }
      }

      int cur_val = 0;

      for (int j = interesting.size() - 1; j >= 0; j--) {
        int qi = interesting[j];
        assert(queries[qi].qt == 1 || queries[qi].qt == 2);
        if (queries[qi].qt == 1) {
          cur_val = queries[qi].x;
        } else if (queries[qi].qt == 2) {
          if (cur_val > queries[qi].x) {
            cur_val = queries[qi].x;
          }
        }
      }
      cout  << cur_val << endl;
    }
  }

/*
  for (int i = 1; i <= n; i++) {
    cout << i << ":  ";
    for (set<int>::iterator ii = visibles[i].begin(); ii != visibles[i].end(); ii++) {
      cout << *ii << " ";
    }
    cout << endl;
  }
*/

  return 0;
}

