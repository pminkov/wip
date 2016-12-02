#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <set>
using namespace std;

typedef long long LL;

const int MIL = 1000000;

int n;
LL k;

vector<int> seq;

/*
  This can be small, because for every number we want to check,
  we only need to check if num-2 and num-last_even exists.
*/ 
int count_ways[100 * MIL];

/*
  The last even number in the sequence.
*/
int get_last_even(int n) {
  return 2 + 2 * (2 * n + 1);
}


/*
  Proove a few hypothesis about the sequence.
*/
void property_proof(int n) {
  vector<int> s;
  s.push_back(2);
  s.push_back(2 * n + 1);

  int last_even = 2;
  int max_ways = 0;
  int total_even = 1;
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
      if (i % 2 == 0) {
        total_even++;
        last_even = i;
      }


      s.push_back(i);
    }

    if (i % 2 == 1) {
      max_ways = max(ways, max_ways);
    }
  }

  cout << "N=" << n << endl;
  cout << "Last even=" << last_even << endl;
  cout << "Max ways for odd numbers=" << max_ways << endl;
  cout << "Total number of even numbers=" << total_even << endl;

  assert(last_even == get_last_even(n));
}


void add_to_seq(int num) {
  if (num > get_last_even(n)) {
    // Numbers after the last even number can only be produced
    // by summing with 2 or the last even number.
    count_ways[ num + 2 ]++;
    count_ways[ num + get_last_even(n) ]++;
  } else {
    for (int i = 0; i < seq.size(); i++) {
      count_ways[ num + seq[i] ]++;
    }
  }

  seq.push_back(num);
}


int gen_next_num() {
  int step = 1;
  if (seq.back() > get_last_even(n)) step = 2;
  for (int i = seq.back() + step; ; i += step) {
    if (count_ways[i] == 1) {
      add_to_seq(i);
      return i;
    }
  }
}


/*
  How many numbers to generate before trying to find
  a pattern in the sequence.
*/
LL SIM = 5 * MIL;


/*
  Check if two subsequences, both of length "len" are the same.
*/
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
  /*cin >> n;
  property_proof(n);
  return 0;
  */
  cin >> n >> k;

  //k = 100 * MIL;

  add_to_seq(2);
  add_to_seq(2*n + 1);

  for (int i = 3; i <= min(k, SIM); i++) {
    gen_next_num();
  }

  if (k <= SIM) {
    cout << seq.back() << endl;
  } else {
    assert(seq.size() == SIM);

    // Find pattern.
    for (int pattern_len = 10; pattern_len <= SIM / 2; pattern_len++) {
      int cstart = seq.size() - pattern_len;
      int pstart = seq.size() - 2 * pattern_len;

      if (equal_subseq(cstart, pstart, pattern_len)) {
        // Find where the pattern starts. This is not necessary for the solution,
        // but I was curious to know it.
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
