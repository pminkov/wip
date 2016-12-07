#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;

const int MAXN = 3 * 100000;

vector<int> divisors[MAXN + 1];
int n;

int used[MAXN];

int main() {
  n = MAXN;
  cin >> n;
  clock_t start;
  start = clock();

  for (int i = 2; i <= n; i++) {
    int c = i;
    while (c <= n) {
      divisors[c].push_back(i);
      c += i;
    }
  }

  int ans = 0;

  for (int a = 1; a <= n / 2; a++) {
    for (int mult = 1; mult * a < n; mult++) {
      int pa = a * mult;
      int pb = n - pa;

      for (int i = divisors[pb].size() - 1; i >= 0; i--) {
        int b = divisors[pb][i];
        if (a < b) {
          if (used[b] != a) {
            used[b] = a;
            ans++;
          }
        }
      }
    }
  }

  cout << ans << endl;
}
