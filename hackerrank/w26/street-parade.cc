#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

const int MAXN = 1000000;

int n;
int a[MAXN];
int m, hmin, hmax;


//int verify_solution(int sp) {
//}

bool good_segment(int start_at) {
  if (start_at < 0) return true;
  else {
    int diff = a[start_at + 1] - a[start_at];
    return hmin <= diff && diff <= hmax;
  }
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  cin >> m >> hmin >> hmax;

  int t = 0;
  int bad_segments = 0;
  for (int s = 0; s < n; s++) {
    bad_segments -= !good_segment(s - 1);
    while (t + 1 < n && a[t + 1] - a[s] <= m) {
      bad_segments += !good_segment(t);
      t++;
    }

    if (bad_segments) {
      continue;
    }


    // How much space we can use to the left and to the right.
    int p = m, q = m;

    if (s > 0) p = a[s] - a[s - 1];
    if (t + 1 < n) q = a[t + 1] - a[t];

    /*
    cout << "-----------------------";
    cout << "s=" << s << endl;
    cout << "p="<< p << endl;
    cout << "q=" << q << endl;
    */

    // x----p----x-----len----x----q---x
    int len = a[t] - a[s];
    int r = m - len;
    //cout << "r=" << r << endl;

    // Try to spend time only before s.
    if (r == 0) {
      cout << a[s] << endl;
      break;
    } else if (p >= r && r >= hmin && r <= hmax) {
      cout << a[s] - r;
      break;
    } else if (q <= r && r >= hmin && r <= hmax) {
      // Only after t.
      cout << a[s];
      break;
    } else {
      /*
      We need to spend p' time before s and q' time after t.
      We have the following system:

      p' + q' = r   (q' = r - p')
      p' >= hmin
      p' <= min(hmax, p) = pmax
      q' >= hmin
      q' <= min(hmax, q) = qmax

      Then:
      p' + q' = r
      p' >= hmin
      p' <= pmax
      r - p' >= hmin
      r - p' <= qmax

      Then:
      p' >= hmin
      p' <= pmax
      p' <= r - hmin
      p' >= r - qmax

      Then:
      p' >= max(hmin, r - qmax)
      p' <= min(pmax, r - hmin)

      Phew. Let's code it:
      */

      int p_lower = max(hmin, r - min(hmax, q));
      int p_upper = min(min(hmax, p), r - hmin);
      //cout << p_lower << " " << p_upper << endl;
      if (p_lower <= p_upper) {
        cout << a[s] - p_lower;
        break;
      }
    }
  }
}

