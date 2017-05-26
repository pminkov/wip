import datetime
import time
import hashlib
import random

DEBUG = 1

class Server:
  last_server_id = 0
  width = 10

  def __init__(self):
    Server.last_server_id += 1
    self.id = Server.last_server_id
    self.hashes = []

    # Each server has "width" virtual copies.
    for wi in range(0, Server.width):
      part_id = '{}_{}'.format(self.id, wi)
      self.hashes.append(Cluster.hash(part_id))

    self.values = {}

  def store(self, key_hash, value):
    self.values[key_hash] = value

  def get(self, key_hash):
    if key_hash in self.values:
      return self.values[key_hash]

    return None

  def move_values(self, cutoff_hash_key, to_server):
    keys = self.values.keys()
    for k in keys:
      if k >= cutoff_hash_key:
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

  def add_server(self):
    new_server = Server()
    current_hashes = sorted(self.hash_to_server_id.keys())

    # Set new server in internal structures.
    self.servers.append(new_server)

    for h in new_server.hashes:
      if h not in self.hash_to_server_id:
        self.hash_to_server_id[h] = new_server.id

    self.server_id_to_server[new_server.id] = new_server

    # Now, see which servers are we going to copy from to the new server.
    new_server_hashes = sorted(new_server.hashes)

    if len(current_hashes) == 0:
      # Empty cluster, first server in.
      return

    move_from = -1
    for h in new_server_hashes:
      while move_from + 1 < len(current_hashes) and current_hashes[move_from + 1] <= h:
        move_from += 1

      if move_from == -1:
        real_move_from = len(current_hashes) - 1
      else:
        real_move_from = move_from

      if current_hashes[real_move_from] != h:
        move_from_server_id = self.hash_to_server_id[ current_hashes[real_move_from] ]
        move_from_server = self.server_id_to_server[ move_from_server_id ]
        move_from_server.move_values(h, new_server)
        if DEBUG:
          print 'New server hash: {}. Moving from server hash {}'.format( \
            h, current_hashes[real_move_from])
          
      

class RandomWords:
  def __init__(self):
    word_file = "/usr/share/dict/words"
    self.words = open(word_file).read().splitlines()

  def random_phrase(self):
    return random.choice(self.words) + "_" + random.choice(self.words)

if __name__ == '__main__':
  random.seed(None)
  rw = RandomWords()
  cluster = Cluster()
  
  cluster.add_server()
  cluster.add_server()
  cluster.add_server()

  cluster.set(random.randint(1,1000), rw.random_phrase())


  cluster.set(5, "five")

  print cluster.get(5)

  cluster.set(1000, "hiliada")

  print cluster.get(1000)
