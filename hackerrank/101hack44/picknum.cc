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

const int MAXN = 200;

int counter[MAXN];

int main(){
  int n;
  cin >> n;
  for(int a_i = 0;a_i < n;a_i++) {
    int a;
    cin >> a;
    counter[a]++;
  }

  int maxc = -1;
  for (int i = 0; i < MAXN - 1; i++) {
    int c = counter[i] + counter[i + 1];
    if (c > maxc) maxc = c;
  }
  cout << maxc << endl;
  return 0;
}

