#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <set>
using namespace std;

//#define DEBUG 1
typedef long long LL;

const int MIL = 1000000;

LL n, k;

vector<int> seq;
int cc[30* MIL];

const int WN = 50000;

vector<pair<int, int> > ways[WN];

int get_last_even(int n) {
  return 2 + 2 * (2 * n + 1);
}

void property_proof(int n) {
  vector<int> s;
  s.push_back(2);
  s.push_back(2 * n + 1);

  int last_even = 2;
  for (int i = s.back() + 1; i <= 1000; i++) {
    int ways = 0;
    
    for (int n1 = 0; n1 < s.size(); n1++) {
      for (int n2 = n1 + 1; n2 < s.size(); n2++) {
        if (s[n1] + s[n2] == i) {
          ways++;
        }
      }
    }

    if (ways == 1) {
      if (i % 2 == 0) last_even = i;

      s.push_back(i);
    }
  }

  cout << "N=" << n << endl;
  cout << "Last even=" << last_even << endl;

  assert(last_even == get_last_even(n));
}

void manual_push(int num) {
  for (int i = 0; i < seq.size(); i++) {
    if (seq[i] > get_last_even(n)) break;

    cc[ num + seq[i] ]++;

    #ifdef DEBUG
    int s = num + seq[i];

    if (s % 2 == 1 && s < WN) {
      ways[s].push_back(make_pair(num, seq[i]));
    }
    #endif
  }
  seq.push_back(num);
}

int next_num() {
  int step = 1;
  if (seq.back() > get_last_even(n)) step = 2;
  for (int i = seq.back() + step; ; i += step) {
    if (cc[i] == 1) {
      manual_push(i);
      return i;
    }
  }
}

LL SIM = 5 * MIL;

bool equal_subseq(int s1, int s2, int len) {
  for (int i = 0; i < len; i++) {
    int n1 = seq[s1 + i] - seq[s1 + i - 1];
    int n2 = seq[s2 + i] - seq[s2 + i - 1];
    if (n1 != n2) {
      return false;
    }
  }
  return true;
}

int main() {
/*
  cin >> n;
  property_proof(n);
  return 0;
  */
  cin >> n >> k;



  //k = 100 * MIL;

  manual_push(2);
  manual_push(2*n + 1);

  int diff = 0;
  int prev = seq.back();
  int rr = 0;
  for (int i = 3; i <= min(k, SIM); i++) {
    rr = next_num();
    diff = rr - prev; 
    prev = rr;
    //cout << "[" << i << "] " << diff << " " << rr << endl;
    #ifdef DEBUG
    if (i % 1000 == 0)  cout  << i << " " << rr << endl;
    #endif
  }

  
  #ifdef DEBUG
  vector<int> counts(1000, 0);

  for (int i = 0; i < WN; i++) {
    cout <<  i << " ways:" << cc[i] << " " ;
    for (int j = 0; j < ways[i].size();j++) {
      cout << "(" << ways[i][j].first << ", " << ways[i][j].second << ") ";

      if (cc[i] == 1) {
        assert(ways[i][j].second < 1000);
        counts[ ways[i][j].second ]++;
      }
    }

    cout << endl;
  }

  cout << "Counts:\n";
  for (int i = 0; i < 1000; i++) {
    if (counts[i] > 0) {
      cout << i << " " << counts[i] << endl;
    }
  }
  cout << "----\n";

  #endif

  if (k <= SIM) {
    cout << rr << endl;
  } else {
    assert(seq.size() == SIM);

    // Find pattern.
    for (int pattern_len = 10; pattern_len <= SIM / 2; pattern_len++) {
      // seq.size = 50
      // 48 => 48, 49.
      // 46 => 46, 47.
      int cstart = seq.size() - pattern_len;
      int pstart = seq.size() - 2 * pattern_len;

      if (equal_subseq(cstart, pstart, pattern_len)) {
        // Find where the pattern starts.
        while (pstart - pattern_len > 0) {
          if (equal_subseq(cstart, pstart - pattern_len, pattern_len)) {
            pstart = pstart - pattern_len;
          } else {
            break;
          }
        }

        //cout << "Pattern of length " << pattern_len << endl;
        //cout << "Starting at " << pstart << endl;

        LL seq_diff = seq[cstart + pattern_len - 1] - seq[cstart - 1];

        LL need_more = k - SIM - 1;
        LL my_diff = seq[cstart + (need_more) % pattern_len] - seq[cstart - 1];
        cout << LL(seq.back()) + (need_more / pattern_len) * seq_diff + my_diff << endl;
        break;
      }
    }
  }
}
