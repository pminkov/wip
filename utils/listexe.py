import os

def is_exe(fname):
  return os.access(fname, os.X_OK)

if __name__ == '__main__':
  for (dirpath, dirnames, filenames) in os.walk('.'):
    if '.git' in dirpath:
      continue

    for filename in filenames:
      full_name = os.path.join(dirpath, filename)
      if is_exe(full_name):
        print full_name
        
