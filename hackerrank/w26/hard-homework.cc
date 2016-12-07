#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main() {
  int n;
  cin >> n;

  double maxr = -5;
  int mx, my, mz;

  for (int x = 1; x <= n - 2; x++)
    for (int y = x; y + x <= n - 1; y++) {

      int z = n - x - y;
      double r = sin(x) + sin(y) + sin(z);
      if (r > maxr) {
        maxr = r;
        mx=x;
        my=y;
        mz=z;
      }
    }
  
  printf("%.9f\n", maxr);
  printf("%d %d %d\n", mx,my,mz);
}
