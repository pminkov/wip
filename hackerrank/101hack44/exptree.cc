#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef unsigned long long i64;

i64 fact(i64 n) {
  if (n == 1) return 1;
  else return n * fact(n - 1);
}

// N nodes, K leaves.
i64 dp(i64 n, i64 k) { 
  if (n == 1) {
    return k == 1;
  } else {
    i64 a = dp(n - 1, k) * k;
    i64 b = dp(n - 1, k - 1) * (n - k);
    return a + b;
  }
}

const i64 MAXN = 100001;

i64 table[2][MAXN];

const i64 MOD = 1000000007LL;

int main() {
  i64 N;
  cin >> N;
  table[1][1] = 1;

  for (i64 n = 2; n <= N; n++) {
    for (i64 k = 1; k <= n; k++) {
      table[n % 2][k] = table[(n - 1) % 2][k] * k + table[(n - 1) % 2][k - 1] * (n - k);
      table[n % 2][k] = table[n % 2][k] % MOD;
    }
  }

  i64 ans = 0;
  i64 sum = 0;
  i64 total = 0;
  for (i64 k = 1; k <= N; k++) {
    //cout << N << " " << k << " -> " << table[N % 2][k] << endl;
    ans += table[N % 2][k];
    sum += k * (table[N % 2][k] % MOD);
    sum %= MOD;
  }
  sum *= N;
  sum %= MOD;
  cout << sum << endl;
}

