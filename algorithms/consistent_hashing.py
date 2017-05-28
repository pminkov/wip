"""
Consistent hashing, as described in:

https://www.toptal.com/big-data/consistent-hashing
"""
import datetime
import time
import hashlib
import random

DEBUG = 0

class Server:
  last_server_id = 0
  virtual_copies = 50

  def __init__(self):
    Server.last_server_id += 1
    self.id = Server.last_server_id
    self.hashes = []

    # Each server has N virtual copies.
    for wi in range(0, Server.virtual_copies):
      part_id = '{}_{}'.format(self.id, wi)
      self.hashes.append(Cluster.hash(part_id))

    self.values = {}

  def dump(self):
    print '-' * 80
    print 'ID:', self.id
    print 'Hashes:', sorted(self.hashes)
    for (k, v) in self.values.items():
      print k, v

  def store(self, key_hash, value):
    self.values[key_hash] = value

  def get(self, key_hash):
    if key_hash in self.values:
      return self.values[key_hash]

    return None

  def _should_move(self, begin_hash, end_hash, key_hash):
    if begin_hash < end_hash:
      return begin_hash <= key_hash and key_hash < end_hash
    else:
      return begin_hash <= key_hash or key_hash < end_hash

  def move_values(self, to_server, begin_hash, end_hash):
    keys = self.values.keys()
    for k in keys:
      if self._should_move(begin_hash, end_hash, k):
        to_server.store(k, self.values[k])
        del self.values[k]

    if DEBUG:
      pass
      

class Cluster:
  mod = 1 << 16

  def __init__(self):
    self.servers = []
    self.hash_to_server_id = {}
    self.server_id_to_server = {}
    pass

  def dump(self):
    print 'Dumping cluster======='
    for s in self.servers:
      s.dump()

  def check(self):
    is_ok = True
    for s in self.servers:
      for key_hash in s.values.keys():
        # Find if we're in the right server.
        best_hash = -1
        max_hash = -1
        max_server = None
        which_server = None
        for ts in self.servers:
          for hash in ts.hashes:
            if hash <= key_hash and hash > best_hash:
              best_hash = hash
              which_server = ts

            if hash > max_hash:
              max_hash = hash
              max_server = ts
        
        if best_hash == -1:
          (best_hash, which_server) = (max_hash, max_server)

        if s != which_server:
          is_ok = False
          print 'BAD: {} is in server {} and needs to be in server {}, after server hash {}'. \
            format(key_hash, s.id, which_server.id, best_hash)

    return is_ok

    
  @staticmethod
  def hash(value):
    hv = hashlib.md5(str(value))
    hex = hv.hexdigest()
    as_int = int(hex, 16)
    return as_int % Cluster.mod

  def _key_to_server(self, key):
    key_hash = Cluster.hash(key)

    virtual_copy_hash = -1
    max_hash = -1

    # Which virtual server copy corresponds to the key's hash value.
    for (hash, server_id) in self.hash_to_server_id.items():
      if hash <= key_hash:
        if hash > virtual_copy_hash:
          virtual_copy_hash = hash
      if hash > max_hash:
        max_hash = hash

    if virtual_copy_hash == -1:
      virtual_copy_hash = max_hash
    
    if DEBUG:
      print 'key_hash={}, virtual_copy_hash={}'.format(key_hash, virtual_copy_hash)

    server_id = self.hash_to_server_id[virtual_copy_hash]
    server = self.server_id_to_server[server_id]

    return (key_hash, server)

  def get(self, key):
    (key_hash, server) = self._key_to_server(key)

    return server.get(key_hash)


  def set(self, key, value):
    if DEBUG:
      print 'Set({}, {})'.format(key, value)

    (key_hash, server) = self._key_to_server(key)

    server.store(key_hash, value)

  def in_range(self, begin, end, what):
    if begin < end:
      return begin < what and what < end
    else:
      return begin < what or what < end
    

  def add_server(self):
    new_server = Server()
    serving_hashes = sorted(self.hash_to_server_id.keys())

    # Set new server in internal structures.
    self.servers.append(new_server)

    for h in new_server.hashes:
      if h not in self.hash_to_server_id:
        self.hash_to_server_id[h] = new_server.id

    self.server_id_to_server[new_server.id] = new_server

    if len(serving_hashes) == 0:
      # Empty cluster, first server in.
      return

    # Now, see which servers are we going to copy from to the new server.
    new_server_hashes = sorted(new_server.hashes)

    if DEBUG:
      print '-' * 80
      print 'ADDING a server'
      print 'Current hashes: {}'.format(serving_hashes)
      print 'New server hashes: {}'.format(new_server_hashes)

    for i in range(0, len(serving_hashes)):
      begin_hash = serving_hashes[i]
      end_hash = serving_hashes[(i + 1) % len(serving_hashes)]

      copy_hashes = []
      for new_hash in new_server_hashes:
        if self.in_range(begin_hash, end_hash, new_hash):
          copy_hashes.append(new_hash)

      if len(copy_hashes) > 0:
        if DEBUG:
          print 'Moving data from range [{}, {}] to {}'.format(begin_hash, end_hash, copy_hashes)
        copy_hashes.append(end_hash)

        def sort_value(hash):
          if begin_hash < end_hash:
            return hash
          else:
            ret = hash
            if hash <= end_hash:
              ret += Cluster.mod
            return ret

        copy_hashes = sorted(copy_hashes, key=sort_value)
        
        if DEBUG:
          print 'Copy points: {}'.format(copy_hashes)

        for ci in range(len(copy_hashes) - 1):
          begin_copy = copy_hashes[ci]
          end_copy = copy_hashes[ci + 1]

          origin_server_id = self.hash_to_server_id[begin_hash]
          origin_server = self.server_id_to_server[origin_server_id]

          if DEBUG:
            print '   Performing move from server({}) - range [{}, {})'.format( \
              origin_server.id, begin_copy, end_copy)
          origin_server.move_values(new_server, begin_copy, end_copy)
            


class RandomWords:
  def __init__(self):
    word_file = "/usr/share/dict/words"
    self.words = open(word_file).read().splitlines()

  def random_phrase(self):
    return random.choice(self.words) + "_" + random.choice(self.words)

def  simple_test():
  random.seed(5)
  rw = RandomWords()

  cluster = Cluster()
  cluster.add_server()

  for i in range(0, 10):
    cluster.set(random.randint(1, 1 << 30), rw.random_phrase())

  cluster.add_server()
  cluster.check()

  cluster.dump()
  cluster.add_server()

  cluster.dump()

  for s in cluster.servers:
    print s.id, len(s.values)

  assert cluster.check()

def big_test():
  random.seed(5)
  rw = RandomWords()

  cluster = Cluster()
  cluster.add_server()

  N = 10
  for i in range(N):
    cluster.set(random.randint(1, 1 << 30), rw.random_phrase())

  for i in range(8):
    cluster.add_server()
    print i
    assert cluster.check()

  for s in cluster.servers:
    print s.id, len(s.values)



if __name__ == '__main__':
  #simple_test()
  big_test()




