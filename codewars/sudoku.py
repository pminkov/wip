import test
import math

class Sudoku(object):
  def __init__(self, grid):
    self.grid = grid

  def is_valid(self):
    g = self.grid
    n = len(g)

    sn = int(math.sqrt(n))
    if sn * sn != n:
      return False

    for i in range(0, n):
      if len(g[i]) != n:
        return False

    for i in range(0, n):
      for j in range(0, n):
        num = g[i][j]
        if type(num) != int: return False
  
        if num < 1 or num > n:
          return False

    for i in range(0, n):
      x = set()
      y = set()
      for j in range(0, n):
        x.add(g[i][j])
        y.add(g[j][i])
      if len(x) != n or len(y) != n: return False

    for i in range(0, sn):
      for j in range(0, sn):
        si = i * sn
        sj = j * sn

        x = set()
        for ii in range(si, si + sn):
          for jj in range(sj, sj + sn):
            x.add(g[ii][jj])

        if len(x) != n: return False

    return True
            
        

        



# Valid Sudoku
goodSudoku1 = Sudoku([
  [7,8,4, 1,5,9, 3,2,6],
  [5,3,9, 6,7,2, 8,4,1],
  [6,1,2, 4,3,8, 7,5,9],

  [9,2,8, 7,1,5, 4,6,3],
  [3,5,7, 8,4,6, 1,9,2],
  [4,6,1, 9,2,3, 5,8,7],
  
  [8,7,6, 3,9,4, 2,1,5],
  [2,4,3, 5,6,1, 9,7,8],
  [1,9,5, 2,8,7, 6,3,4]
])

goodSudoku2 = Sudoku([
  [1,4, 2,3],
  [3,2, 4,1],

  [4,1, 3,2],
  [2,3, 1,4]
])

# Invalid Sudoku
badSudoku1 = Sudoku([
  [0,2,3, 4,5,6, 7,8,9],
  [1,2,3, 4,5,6, 7,8,9],
  [1,2,3, 4,5,6, 7,8,9],
  
  [1,2,3, 4,5,6, 7,8,9],
  [1,2,3, 4,5,6, 7,8,9],
  [1,2,3, 4,5,6, 7,8,9],
  
  [1,2,3, 4,5,6, 7,8,9],
  [1,2,3, 4,5,6, 7,8,9],
  [1,2,3, 4,5,6, 7,8,9]
])

badSudoku2 = Sudoku([
  [1,2,3,4,5],
  [1,2,3,4],
  [1,2,3,4],  
  [1]
])

test.assert_equals(goodSudoku1.is_valid(), True, 'testing valid 9x9')
test.assert_equals(goodSudoku2.is_valid(), True, 'testing valid 4x4')

test.assert_equals(badSudoku1.is_valid(), False, 'Values in wrong order')
test.assert_equals(badSudoku2.is_valid(), False, '4x5 (invalid dimension)')
