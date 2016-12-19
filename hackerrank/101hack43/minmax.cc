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
  cin >> n;
  vector<int> a(n);
  for(int a_i = 0;a_i < n;a_i++){
     cin >> a[a_i];
  }

  sort(a.begin(), a.end());

  int xa = a[n-1] - a[0];
  int xb = a[n-2] - a[0];
  int xc = a[n-1] - a[1];

  int r = min(xa, min(xb,xc));
  cout << r << endl;
  return 0;
}

