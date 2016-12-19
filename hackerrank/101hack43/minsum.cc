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


int main(){
  int n;
  int k;
  cin >> n >> k;
  vector<int> a(n);
  for(int a_i = 0;a_i < n;a_i++){
     cin >> a[a_i];
  }
  sort(a.begin(), a.end());

  long long ts = 0, mints;

  for (int i = 0; i < k; i++) {
    for (int j = 0; j < k; j++) {
      ts += (a[i] - a[j]) * (a[i] - a[j]);
    }
  }

  mints = ts;
  // 1-5j9j
  for (int i = k; i < n; i++) {
    // Add i.
    int cc = 0;
    // Total = i - (i - k + 1) + 1 = k
    for (int j = i - k + 1; j <= i; j++) {
      cc++;
      ts += (a[i] - a[j]) * (a[i] - a[j]);
    }
    assert(cc == k);
    // k = 2.
    // i = 5.
    // 4, 5.
    // 5 - 2 = 3.
    // Remove i - k.
    // [3, 5)
    //  
    cc = 0;
    // Total = i - (i - k) = k
    for (int j = i - k; j < i; j++) {
      cc++;
      ts -= (a[i - k] - a[j]) * (a[i - k] - a[j]);
    }
    assert(cc == k);

    if (ts < mints) mints = ts;
  }
  cout << mints << endl;
  return 0;
}

