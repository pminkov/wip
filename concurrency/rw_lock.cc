#include "pthread_utils.h"

#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <iostream>
using namespace std;

class RwLock {
  public:
    int readers;
    pthread_mutex_t write_lock, read_lock;

    RwLock() {
      readers = 0;
      Pthread_mutex_init(&write_lock);
      Pthread_mutex_init(&read_lock);
    }

    void begin_write() {
      Pthread_mutex_lock(&write_lock);
    }

    void end_write() {
      Pthread_mutex_unlock(&write_lock);
    }

    void begin_read() {
      Pthread_mutex_lock(&read_lock);
      if (readers == 0) {
        Pthread_mutex_lock(&write_lock);
      }
      readers++;
      Pthread_mutex_unlock(&read_lock);
    }

    void end_read() {
      Pthread_mutex_lock(&read_lock);
      readers--;
      if (readers == 0) {
        Pthread_mutex_unlock(&write_lock);
      }
      Pthread_mutex_unlock(&read_lock);
    }
};


template <class K, class V>
class MtMap {
  private:
    map<K, V> kv;
    RwLock rw_lock;

  public:
    MtMap() {
    }

    void insert(const K &key, const V &value) {
      rw_lock.begin_write();
      kv[key] = value;
      rw_lock.end_write();
    }

    bool get(const K &key, V *value) {
      rw_lock.begin_read();
      map<string, string>::iterator it = kv.find(key);

      bool ret_val = false;
      if (it != kv.end()) {
        *value = it->second;
        ret_val = true;
      }
      rw_lock.end_read();
      return ret_val;
    }
};


int main() {
  MtMap<string, string> map;

  map.insert("petko", "minkov");
  map.insert("john", "smith");

  vector<string> checks;
  checks.push_back("petko");
  checks.push_back("john");
  checks.push_back("hello");

  for (int i = 0; i < checks.size(); i++) {
    string s;
    bool res = map.get(checks[i], &s);

    if (res) {
      cout << "Found (" << checks[i] << ", " << s << ")" << endl;
    } else {
      cout << "Not found (" << checks[i] << ")" << endl;
    }
  }
}
