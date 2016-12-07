#include <iostream>
using namespace std;

bool is_prime(int x) {
  for (int i = 2; i * i <= x; i++) {
    if (x % i == 0) return false;
  }
  return true;
}

int main() {
  int n, m;
  cin >> n >> m;
  int ret = 0;
  for (int i = n; i <= m - 2; i++) {
    if (is_prime(i) && is_prime(i + 2))
      ret ++;
  }
  cout << ret << endl;
}
