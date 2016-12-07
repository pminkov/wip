#include <cassert>
#include <iostream>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  int ans = 0;

  if (n % 2 == 0 && m % 2 == 0) {
    ans = (n * m) / 4;
  } else if (n % 2 == 1 && m % 2 == 1) {
    ans = (n - 1) * (m - 1) / 4;
    ans += 1;
    n -= 2;
    m -= 2;
    if (n > 0) {
      ans += (n + 1) / 2;
    }
    if (m > 0) {
      ans += (m + 1) / 2;
    }
  } else {
    if (n % 2 == 1) {
      int tmp = n;
      n = m;
      m = tmp;
    }

    assert(n % 2 == 0);
    assert(m % 2 == 1);

    ans = (n * (m - 1)) / 4;
    ans += (n + 1) / 2;
  }

  cout << ans << endl;
}
