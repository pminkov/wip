#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef pair<int, int> LexPair;

//#define DEBUG

#ifdef DEBUG
  #define DD(x) x;
#else
  #define DD(...)
#endif

class SuffixArray {
public:
  vector<int> ngram_order;
  vector<int> lcp;
  vector<int> sa;
  vector<pair<LexPair, int> > sort_helper;

  int N;

  SuffixArray(const string &s_param) {
    s = s_param;
    N = s.size();
  }

  /*
  Suffix array is built with algorithm that sorts 1-grams, 2-grams, 4-grams, etc.

  Described here:
    https://www.cs.helsinki.fi/u/tpkarkka/opetus/11s/spa/lecture10.pdf

  And here:
    http://stackoverflow.com/questions/17761704/suffix-array-algorithm

  */
  void build() {
    assert(sa.size() == 0);

    int N = s.length();

    ngram_order.resize(N);
    sa.resize(N);
    sort_helper.resize(N);

    for (int i = 0; i < N; i++) {
      ngram_order[i] = s[i];
    }

    for (int gap = 1; gap < N; gap *= 2) {
      DD(cout << "gap = " << gap << endl);
      for (int i = 0; i < N; i++) {
        int lex0 = ngram_order[i];
        int lex1 = i + gap < N ? ngram_order[i + gap] : 0;

        sort_helper[i] = make_pair(LexPair(lex0, lex1), i);
        DD(cout << "(" << lex0 << "," << lex1 << ") " << " ");
      }
      DD(cout << endl);
      sort_and_label();
      DD(print_ngram_order());
    }

    for (int i = 0; i < N; i++) {
      sa[ ngram_order[i] - 1 ] = i;
    }
  }

  /*
  We use this algorithm:
    https://www.cs.helsinki.fi/u/tpkarkka/opetus/11s/spa/lecture10.pdf

  Also explained here:
    http://stackoverflow.com/questions/26428636/how-does-this-code-for-obtaining-lcp-from-a-suffix-array-work
  */
  void compute_lcp() {
    assert(lcp.size() == 0);

    lcp.resize(N);

    vector<int> inverse(N, 0);
    for (int i = 0; i < N; i++) {
      inverse[ sa[i] ] = i;
    }

    int l = 0;
    for (int i = 0; i < N; i++) {
      // The string starting at position "i" is k-th in the suffix array.
      int k = inverse[i];

      if (k >= 1) {
        // We take the previous string in the suffix array.
        int j = sa[k - 1];
        while (s[i + l] == s[j + l]) l++;
        lcp[k] = l;
        if (l > 0) l--;
      }
    }

    // lcp[k] is the LCP of S[sa[k]:] and S[sa[k - 1]:].
  }

  int distinct_substrings() {
    int ans = N - sa[0];

    DD(cout << "Ans=" << ans << endl);
    for (int i = 1; i < N; i++) {
      DD(cout << i << ": " << lcp[i] << endl);
      ans += N - sa[i] - lcp[i];
    }
    return ans;
  }

  void print() {
    cout << "S = " << s << endl;
    for (int i = 0; i < N; i++) {
      cout << sa[i] << " : " << s.substr(sa[i]) << endl;
    }
  }

private:
  void print_ngram_order() {
    cout << "ngram: ";
    for (int i = 0; i < N; i++) {
      cout << ngram_order[i] << " ";
    }
    cout << endl;
  }

  void sort_and_label() {
    sort(sort_helper.begin(), sort_helper.end());

    int counter = 0;
    LexPair last_value(-1, -1);

    for (int i = 0; i < N; i++) {
      LexPair value = sort_helper[i].first;
      if (value != last_value) {
        counter++;
      }
      int pos = sort_helper[i].second;
      ngram_order[pos] = counter;

      last_value = value;
    }
  }

  string s;
};

void test() {
  {
    string s = "banana";
    SuffixArray sa(s);

    sa.build();
    sa.compute_lcp();
    assert(15 == sa.distinct_substrings());
  }

  {
    string s = "x";
    SuffixArray sa(s);
    sa.build();
    assert(sa.sa.size() == 1);
  }
}


int main() {
  test();
}
