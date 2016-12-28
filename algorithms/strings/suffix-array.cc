#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef pair<int, int> LexPair;

#define DEBUG

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
  Suffix array is built with an algorithm that assigns lexicographic order value to 
  1-grams, 2-grams, 4-grams, etc.

  So, first we assign that to 1-grams, which are basically the values of the letters. 
  Example:

  b a n a n a
  2 1 3 1 3 1

  We then create 2-grams.

  ba (2,1)
  an (1,3)
  na (3,1)
  an (1,3)
  na (3,1)
  a_ (1,0)

  The order is:
  ba 3 
  an 2
  na 4
  an 2
  na 4 
  a_ 1

  Now, we want to produce lexicographic order values for 4-grams.
  Each 4-gram is made of two 2-grams and we know their order. So no need to compare 4 characters.
  So for "ba", we'll combine with "na" - 3 and 4.

  bana (3,4)
  anan (2,2)
  nana (4,4)
  ana_ (2,1)
  na__ (4,0)
  a___ (1,0)

  And the order is:
  bana 4
  anan 3
  nana 6
  ana_ 2
  na__ 5
  a___ 1

  And one last one for 8-grams.

  banana__ (4,5)
  anana___ (3,1)
  nana____ (6,0)
  ana_____ (2,0)
  na______ (5,0)
  a_______ (1,0)

  And the order is:
  banana 4
  anana  3 
  nana   6
  ana    2
  na     5
  a      1

  And that's it. We can use this array to produce our suffix array.



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

  A similar version is explained here:
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

  /*
  One application of suffix arrays: finding the nubmber of distinct substrings of a string.
  */
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
